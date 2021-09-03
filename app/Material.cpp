#include "Material.h"

#include <map>

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

void Material::calculateMacroXSs()
{
    std::map<std::string, double> backgroundXSMap = calculateBackgroundXS();

    std::vector<double> values(libNuclides_.front()->getEnergyGroupsNumber(), 0.0);
    CrossSection xs(getTemperature(), 0.0, values);

    for(const auto& xsKind : XSKind())
    {
        for(const auto& nuc : libNuclides_)        
        {
            double backgroundXS = backgroundXSMap.find(nuc->getName())->second;
            xs += nuc->getXSSet(xsKind).getXS(temperature_, Sqrt(), backgroundXS, LogLin());
        }

        MacroCrossSection macroXS(xsKind, getTemperature(), xs.getValues());
        m_crossSections.push_back(std::pair<XSKind, MacroCrossSection>(xsKind, macroXS));
        xs.deleteXS();
    }
}

void Material::calculateMacroXSMatrices()
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
        m_crossSectionMatrices.push_back(std::pair<XSMatrixKind, MacroCrossSectionMatrix>(xsKind, macroXSMat));
        xsMat.setToZero(nEnergyGroups, nEnergyGroups);
    }

    for(auto i : backgroundXSMap)
        std::cout << i.first << " " << i.second << std::endl; 
}