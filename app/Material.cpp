#include "Material.h"
#include "numeric_tools.h"
#include "additionalPrintFuncs.h"

#include <map>

using namespace Numerics;

Material::Material(double t, const std::vector<std::string> &n, const std::vector<double> &d, 
                   std::vector < std::shared_ptr<Nuclide> >& l) : 
                   temperature_(t), nuclides_(n), densities_(d), libNuclides_(l) 
                   {
                       backgroundXSMap_ = calculateBackgroundXS();
                   }  

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

    // std::cout << std::scientific << std::endl;
    // for(auto it = backgroundXSMap.begin(); it != backgroundXSMap.end(); it++)
    //     std::cout << "sigmaXS: " << it->first << " " << it->second << std::endl;
    
    return backgroundXSMap;
}

std::vector<Material::MacroXSType> Material::calculateMacroXSs()
{
    std::vector<double> values(libNuclides_.front()->getEnergyGroupsNumber(), 0.0);
    CrossSection xs(getTemperature(), 0.0, values);

    for(const auto& xsKind : XSKind())
    {
        if(xsKind != XSKind::CHI && xsKind != XSKind::NU && xsKind != XSKind::NUSIGF)
        {
            for(size_t i = 0; i < libNuclides_.size(); i++)        
            {
                double backgroundXS = backgroundXSMap_.find(libNuclides_[i]->getName())->second;
                xs += densities_[i] * libNuclides_[i]->getXSSet(xsKind).getXS(temperature_, Sqrt(), backgroundXS, LogLin());

                // if(xsKind == XSKind::NTOT0)
                // {
                //     std::vector<double> xs2 = libNuclides_[i]->getXSSet(xsKind).getXS(temperature_, Sqrt(), backgroundXS, LogLin()).getValues();
                //     std::cout << std::scientific << std::endl;
                //     std::cout << "Nuclide: " << libNuclides_[i]->getName() << " xs: " << get_name(xsKind) << std::endl;
                //     for(auto i : xs2)
                //         std::cout << i << std::endl;
                // }
            }
        }

        MacroCrossSection macroXS(xsKind, getTemperature(), xs.getValues());
        crossSections_.push_back(std::pair<XSKind, MacroCrossSection>(xsKind, macroXS));
        xs.setToZero();
       
        // if(xsKind == XSKind::ABS || xsKind == XSKind::SCATT00 || xsKind == XSKind::NG)
        // {
        //     std::cout << std::scientific << std::endl;
        //     std::cout << "\nxs: " << get_name(xsKind) << std::endl;
        //     for(auto i : macroXS.getValues())
        //     std::cout << i << std::endl;
        // }
    }

    return crossSections_;
}

std::map<std::string, CrossSection> Material::calculateOtherGroupConstants(XSKind xsKind)
{
    std::map<std::string, CrossSection> resultMap;

    for(size_t i = 0; i < libNuclides_.size(); i++)        
    {
        if(libNuclides_[i]->isFissionable())
        {
            double backgroundXS = backgroundXSMap_.find(libNuclides_[i]->getName())->second;
            CrossSection xs(getTemperature(), backgroundXS, std::vector<double> {});
            xs = libNuclides_[i]->getXSSet(xsKind).getXS(temperature_, Sqrt(), backgroundXS, LogLin());

            if(xsKind == XSKind::NUSIGF)
                xs = densities_[i] * xs;

            resultMap.insert(std::pair<std::string, CrossSection>(libNuclides_[i]->getName(), xs));

            // std::cout << std::scientific << std::endl;
            // std::cout << "Nuclide: " << libNuclides_[i]->getName() << " xs: " << get_name(xsKind) << std::endl;
            // for(auto i : xs.getValues())
            //     std::cout << i << std::endl;
        }
    }

    return resultMap;
}

std::map< XSKind, std::map<std::string, CrossSection> > Material::calculateOtherGroupConstants()
{
    std::map< XSKind, std::map<std::string, CrossSection> > resultMap;

    resultMap.insert(std::pair<XSKind, std::map<std::string, CrossSection> >(XSKind::NU, calculateOtherGroupConstants(XSKind::NU)));
    resultMap.insert(std::pair<XSKind, std::map<std::string, CrossSection> >(XSKind::CHI, calculateOtherGroupConstants(XSKind::CHI)));
    resultMap.insert(std::pair<XSKind, std::map<std::string, CrossSection> >(XSKind::NUSIGF, calculateOtherGroupConstants(XSKind::NUSIGF)));

    return resultMap;
}

std::vector<Material::MacroXSMatrixType> Material::calculateMacroXSMatrices()
{
    unsigned nEnergyGroups = libNuclides_.front()->getEnergyGroupsNumber();
    Eigen::MatrixXd values = Eigen::MatrixXd::Zero(nEnergyGroups, nEnergyGroups);
    CrossSectionMatrix xsMat(getTemperature(), 0.0, values);

    for(const auto& xsKind : XSMatrixKind())
    {
        for(size_t i = 0; i < libNuclides_.size(); i++)         
        {
            double backgroundXS = backgroundXSMap_.find(libNuclides_[i]->getName())->second;
            xsMat += densities_[i] * libNuclides_[i]->getXSMatrixSet(xsKind).getXSMatrix(temperature_, Sqrt(), backgroundXS, LogLin());

            // if(xsKind == XSMatrixKind::SCAT00)
            // {
            //     Eigen::MatrixXd xsMat2 = libNuclides_[i]->getXSMatrixSet(xsKind).getXSMatrix(temperature_, Sqrt(), backgroundXS, LogLin()).getValues();            
            //     std::string str = "Nuclide: " + libNuclides_[i]->getName() + " xs: " + get_name(xsKind);
            //     out.print(TraceLevel::CRITICAL, str);
            //     PrintFuncs::printMatrix(xsMat2, out, TraceLevel::CRITICAL);
            // }
        }
        
        // if(xsKind == XSMatrixKind::SCAT00)
        // {
        //     std::string str = "xs matrix: " + get_name(xsKind);
        //     out.print(TraceLevel::CRITICAL, str);
        //     PrintFuncs::printMatrix(xsMat.getValues(), out, TraceLevel::CRITICAL);
        // }

        // if(xsKind == XSMatrixKind::SCAT00)
        // {
        //     std::cout << "xs vector: " << get_name(xsKind) << std::endl;
        //     for(auto i : xsMat.condenseToXS().getValues())
        //         std::cout << i << std::endl;
        // }        

        MacroCrossSectionMatrix macroXSMat(xsKind, getTemperature(), xsMat.getValues());
        crossSectionMatrices_.push_back(std::pair<XSMatrixKind, MacroCrossSectionMatrix>(xsKind, macroXSMat));
        xsMat.setToZero();
    }

    return crossSectionMatrices_;
}