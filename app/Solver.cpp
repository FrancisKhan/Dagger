#include "Solver.h"
#include "Output.h"
#include "additionalPrintFuncs.h"

Eigen::MatrixXd Solver::calcAMatrix()
{
    Eigen::MatrixXd AMatrix = Eigen::MatrixXd::Zero(nEnergyGroups_, nEnergyGroups_);

    std::vector<double> totXS = Material::getMacroXS(XSKind::NTOT0, crossSections_).getValues();
    Eigen::MatrixXd scattL0Matrix = Material::getMacroXSMatrix(XSMatrixKind::SCAT00, crossSectionMatrices_).getValues(); 

    for(unsigned i = 0; i < AMatrix.rows(); i++)
        AMatrix(i, i) = totXS[i];

    AMatrix -= scattL0Matrix.transpose();

    // out.print(TraceLevel::CRITICAL, "\n\nAMatrix: \n");
    // PrintFuncs::printMatrix(AMatrix, out, TraceLevel::CRITICAL);

    return AMatrix;
}

Eigen::MatrixXd Solver::calcFMatrix()
{
    Eigen::MatrixXd FMatrix = Eigen::MatrixXd::Zero(nEnergyGroups_, nEnergyGroups_);

	std::map<std::string, CrossSection> chiMap    = otherGroupConstants_.find(XSKind::CHI)->second;
	std::map<std::string, CrossSection> nuFissMap = otherGroupConstants_.find(XSKind::NUSIGF)->second;

	for (auto it = chiMap.begin(); it != chiMap.end(); it++)
	{
		std::vector<double> chi      = chiMap.find(it->first)->second.getValues();
		std::vector<double> nuSigfXS = nuFissMap.find(it->first)->second.getValues();

		Eigen::MatrixXd singleFMatrix = Eigen::MatrixXd::Zero(nEnergyGroups_, nEnergyGroups_);

		for(unsigned i = 0; i < FMatrix.rows(); i++)
        	for(unsigned j = 0; j < FMatrix.cols(); j++)
            	singleFMatrix(i, j) = chi[i] * nuSigfXS[j];

		FMatrix += singleFMatrix;
	}

    // std::vector<double> nuSigfXS = Material::getMacroXS(XSKind::NUSIGF, crossSections_).getValues();
    // std::vector<double> chi      = Material::getMacroXS(XSKind::CHI, crossSections_).getValues();

    // for(unsigned i = 0; i < FMatrix.rows(); i++)
    //     for(unsigned j = 0; j < FMatrix.cols(); j++)
    //         FMatrix(i, j) = chi[i] * nuSigfXS[j];

    // out.print(TraceLevel::CRITICAL, "\n\nFMatrix: \n");
    // PrintFuncs::printMatrix(FMatrix, out, TraceLevel::CRITICAL);

    return FMatrix;
}


void Solver::sourceIteration(Eigen::MatrixXd &Mmatrix, Eigen::MatrixXd &Fmatrix)
{
    int max_iter_number = 100;;
	double accuracy = 1.0E-5;

	unsigned size = Mmatrix.rows();
	
	Eigen::VectorXd source1      = Eigen::VectorXd::Zero(size);
	Eigen::VectorXd source2      = Eigen::VectorXd::Ones(size);	
	Eigen::VectorXd neutronFlux1 = Eigen::VectorXd::Ones(size);
	Eigen::VectorXd neutronFlux2 = Eigen::VectorXd::Zero(size);

	double kFactor1 = 1.0;
	double kFactor2 = 0.0;
	
	Eigen::ColPivHouseholderQR<Eigen::MatrixXd> CPHQR;
	CPHQR.compute(Mmatrix);
	
    int h;
	for(h = 0; h < max_iter_number; h++)
	{
		neutronFlux2 = CPHQR.solve(source2);
		
		source1 = Fmatrix * neutronFlux1;
		source2 = Fmatrix * neutronFlux2;
		
		double sum1 = std::inner_product(source1.begin(), source1.end(), source2.begin(), 0.0);
		double sum2 = std::inner_product(source2.begin(), source2.end(), source2.begin(), 0.0);
		
		kFactor2 = kFactor1 * (sum2 / sum1);

		source2 /= kFactor2;
		
		// exit condition
		if (fabs((kFactor2 - kFactor1) / kFactor2) < accuracy) break;
		
		kFactor1     = kFactor2;
		neutronFlux1 = neutronFlux2;
	}

	if(h + 1 > max_iter_number)
	{
		out.print(TraceLevel::CRITICAL, "Number of iteration: {}", h + 1);
		out.print(TraceLevel::CRITICAL, "The calculation did not converge!");
		exit(-1);
	}

	Eigen::VectorXd neutronFlux = neutronFlux2 / neutronFlux2.sum(); 
	double kFactor = kFactor2;

    // std::cout << std::scientific << std::endl;
    // std::cout << "Number of iteration: " << h << std::endl;
    std::cout << "kFactor: " << kFactor << std::endl;
    // std::cout << "Neutron flux: " << std::endl;
    // for(auto i : neutronFlux)
    //     std::cout << i << std::endl;
}