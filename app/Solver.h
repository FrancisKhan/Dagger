#ifndef SOLVER_H
#define SOLVER_H

#include "numeric_tools.h"
#include "Material.h"

class Solver
{
public:
    Solver(const std::vector<Material::MacroXSType>& xs, const std::vector<Material::MacroXSMatrixType>& xsMat) :
    crossSections_(xs), crossSectionMatrices_(xsMat), nEnergyGroups_(crossSections_.front().second.getSize()) {;}
    
    Eigen::MatrixXd calcAMatrix();
  

private:
    std::vector<Material::MacroXSType> crossSections_;
    std::vector<Material::MacroXSMatrixType> crossSectionMatrices_;

    unsigned nEnergyGroups_;
};

#endif