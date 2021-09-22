#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include <string>
#include <map>

#include "MacroCrossSectionMatrix.h"
#include "MacroCrossSection.h"
#include "Nuclide.h"
#include "XSMatrixKind.h"
#include "XSKind.h"

class Material
{
public:

    typedef std::pair<XSKind, MacroCrossSection> MacroXSType;
    typedef std::pair<XSMatrixKind, MacroCrossSectionMatrix> MacroXSMatrixType;
    typedef std::map<std::string, CrossSection> XSMapType;

    Material(double t, const std::vector<std::string> &n, const std::vector<double> &d, 
             std::vector < std::shared_ptr<Nuclide> >& l);

    Material() : temperature_(0.0), nuclides_(std::vector<std::string> {}),
                 densities_(std::vector<double> {}) {;}
    
    void setTemperature(double t) {temperature_ = t;}
    double getTemperature() const {return temperature_;} 
    void setNuclides(const std::vector<std::string>& nuclides) {nuclides_ = nuclides;}
    std::vector<std::string> getNuclides() const {return nuclides_;}
    void setDensities(const std::vector<double>& densities) {densities_ = densities;}
    std::vector<double> getDensities() const {return densities_;}
    void setLibNuclides(const std::vector < std::shared_ptr<Nuclide> >& libNuclides) {libNuclides_ = libNuclides;}
    std::vector < std::shared_ptr<Nuclide> > setLibNuclides() const {return libNuclides_;}

    MacroCrossSection getMacroXS(XSKind kind);
    MacroCrossSectionMatrix getMacroXSMatrix(XSMatrixKind kind);

    static MacroCrossSection getMacroXS(XSKind kind, const std::vector<MacroXSType>& crossSections);
    
    static MacroCrossSectionMatrix getMacroXSMatrix(XSMatrixKind kind, 
                                    const std::vector<MacroXSMatrixType>& crossSectionMatrices);

    std::map<std::string, double> calculateBackgroundXS();
    std::vector<MacroXSType> calculateMacroXSs();
    std::vector<MacroXSMatrixType> calculateMacroXSMatrices();
    XSMapType calculateOtherGroupConstants(XSKind xsKind);
    std::map<XSKind, XSMapType> calculateOtherGroupConstants();

private:
    double temperature_;
    std::vector<std::string> nuclides_;
    std::vector<double> densities_;

    std::vector<MacroXSType> crossSections_;
    std::vector<MacroXSMatrixType> crossSectionMatrices_;

    std::vector < std::shared_ptr<Nuclide> > libNuclides_;

    std::map<std::string, double> backgroundXSMap_;
};

#endif