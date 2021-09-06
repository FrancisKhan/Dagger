#include "Material.h"

#include <map>


MacroCrossSection Material::getMacroXS(XSKind kind, const std::vector<MacroXSType>& crossSections) 
{
    std::vector<MacroXSType>::const_iterator it = std::find_if(crossSections.begin(), crossSections.end(), 
    [kind] (const MacroXSType& p) {return p.first == kind;});

    if (it != crossSections.end()) 
        return it->second;
    else
        return MacroCrossSection {};
}

MacroCrossSection Material::getMacroXS(XSKind kind) 
{
    std::vector<MacroXSType>::iterator it = std::find_if(crossSections_.begin(), crossSections_.end(), 
    [kind] (MacroXSType &p) {return p.first == kind;});

    if (it != crossSections_.end()) 
        return it->second;
    else
        return MacroCrossSection {};
}

MacroCrossSectionMatrix Material::getMacroXSMatrix(XSMatrixKind kind, const std::vector<MacroXSMatrixType>& crossSectionMatrices) 
{
    std::vector<MacroXSMatrixType>::const_iterator it = std::find_if(crossSectionMatrices.begin(), crossSectionMatrices.end(), 
    [kind] (const MacroXSMatrixType& p) {return p.first == kind;});

    if (it != crossSectionMatrices.end()) 
        return it->second;
    else
        return MacroCrossSectionMatrix {};
}

MacroCrossSectionMatrix Material::getMacroXSMatrix(XSMatrixKind kind) 
{
    std::vector<MacroXSMatrixType>::iterator it = std::find_if(crossSectionMatrices_.begin(), crossSectionMatrices_.end(), 
    [kind] (MacroXSMatrixType &p) {return p.first == kind;});

    if (it != crossSectionMatrices_.end()) 
        return it->second;
    else
        return MacroCrossSectionMatrix {};
}

std::map<std::string, double> Material::calculateBackgroundXS()
{
    std::map<std::string, double> backgroundXSMap;

    double backgroundXSSum = 0.0;

    for(size_t i = 0; i < libNuclides_.size(); i++)
    {
        backgroundXSSum += densities_[i] * libNuclides_[i]->getPotXS();
    }

    for(size_t i = 0; i < libNuclides_.size(); i++)
    {
        double backgroundXS = (backgroundXSSum - densities_[i] * libNuclides_[i]->getPotXS()) / densities_[i];
        backgroundXSMap.insert(std::pair<std::string, double>(libNuclides_[i]->getName(), backgroundXS));
    }

    return backgroundXSMap;
}

std::vector<Material::MacroXSType> Material::calculateMacroXSs()
{
    std::map<std::string, double> backgroundXSMap = calculateBackgroundXS();

    std::vector<double> values(libNuclides_.front()->getEnergyGroupsNumber(), 0.0);
    CrossSection xs(getTemperature(), 0.0, values);

    for(const auto& xsKind : XSKind())
    {
        for(const auto& nuc : libNuclides_)        
        {
            double backgroundXS = backgroundXSMap.find(nuc->getName())->second;
            CrossSection aaa = nuc->getXSSet(xsKind).getXS(temperature_, Sqrt(), backgroundXS, LogLin());
            xs += aaa;

            std::cout << std::scientific << std::endl;
            std::cout << "Isotope: " << nuc->getName() << std::endl;
            std::cout << get_name(xsKind) << " " << xs.getValues().size() << std::endl;
            for(auto i : xs.getValues())
                std::cout << i << std::endl;
        }

        MacroCrossSection macroXS(xsKind, getTemperature(), xs.getValues());
        crossSections_.push_back(std::pair<XSKind, MacroCrossSection>(xsKind, macroXS));
        xs.setToZero();
    }

    return crossSections_;
}

std::vector<Material::MacroXSMatrixType> Material::calculateMacroXSMatrices()
{
    std::map<std::string, double> backgroundXSMap = calculateBackgroundXS();

    unsigned nEnergyGroups = libNuclides_.front()->getEnergyGroupsNumber();
    Eigen::MatrixXd values = Eigen::MatrixXd::Zero(nEnergyGroups, nEnergyGroups);
    CrossSectionMatrix xsMat(getTemperature(), 0.0, values);

    for(const auto& xsKind : XSMatrixKind())
    {
        for(const auto& nuc : libNuclides_)        
        {
            double backgroundXS = backgroundXSMap.find(nuc->getName())->second;
            xsMat += nuc->getXSMatrixSet(xsKind).getXSMatrix(temperature_, Sqrt(), backgroundXS, LogLin());
        }

        MacroCrossSectionMatrix macroXSMat(xsKind, getTemperature(), xsMat.getValues());
        crossSectionMatrices_.push_back(std::pair<XSMatrixKind, MacroCrossSectionMatrix>(xsKind, macroXSMat));
        xsMat.setToZero();
    }

    return crossSectionMatrices_;
}