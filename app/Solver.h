#ifndef SOLVER_H
#define SOLVER_H

#include "numeric_tools.h"
#include "Material.h"

class Solver
{
public:
    Solver(const std::vector<Material::MacroXSType>& xs, const std::vector<Material::MacroXSMatrixType>& xsMat,
           const std::map< XSKind, std::map<std::string, CrossSection> >& ogc) :
    crossSections_(xs), crossSectionMatrices_(xsMat), 
    nEnergyGroups_(crossSections_.front().second.getSize()), 
    otherGroupConstants_(ogc) {;}
    
    Eigen::MatrixXd calcAMatrix();
    Eigen::MatrixXd calcFMatrix();

    void sourceIteration(const Eigen::MatrixXd &Mmatrix, const Eigen::MatrixXd &Fmatrix, 
                         double accuracy = 1.0E-7, unsigned maxIterNumber = 100);

private:
    std::vector<Material::MacroXSType> crossSections_;
    std::vector<Material::MacroXSMatrixType> crossSectionMatrices_;
    std::map< XSKind, std::map<std::string, CrossSection> > otherGroupConstants_;

    unsigned nEnergyGroups_;
};

#endif