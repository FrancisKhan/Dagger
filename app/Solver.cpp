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

    PrintFuncs::printMatrix(AMatrix, out, TraceLevel::CRITICAL);

    return AMatrix;
}