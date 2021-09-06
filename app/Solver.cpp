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

    out.print(TraceLevel::CRITICAL, "\n\nAMatrix: \n");
    PrintFuncs::printMatrix(AMatrix, out, TraceLevel::CRITICAL);

    return AMatrix;
}

Eigen::MatrixXd Solver::calcFMatrix()
{
    Eigen::MatrixXd FMatrix = Eigen::MatrixXd::Zero(nEnergyGroups_, nEnergyGroups_);

    std::vector<double> nuSigfXS = Material::getMacroXS(XSKind::NUSIGF, crossSections_).getValues();
    std::vector<double> chi      = Material::getMacroXS(XSKind::CHI, crossSections_).getValues();

    // std::cout << std::scientific << std::endl;
    // std::cout << "nuSigfXS: " << nuSigfXS.size() << std::endl;
    // for(auto i : nuSigfXS)
    //     std::cout << i << std::endl;

    // std::cout << "chi: " << chi.size() << std::endl;
    // for(auto i : chi)
    //     std::cout << i << std::endl;

    // for(unsigned i = 0; i < FMatrix.rows(); i++)
    //     for(unsigned j = 0; j < FMatrix.rows(); j++)
    //         FMatrix(i, j) = chi[i] * nuSigfXS[j];


    out.print(TraceLevel::CRITICAL, "\n\nFMatrix: \n");
    PrintFuncs::printMatrix(FMatrix, out, TraceLevel::CRITICAL);

    return FMatrix;
}