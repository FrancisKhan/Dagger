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

    Material(double t, const std::vector<std::string> &n, const std::vector<double> &d, 
             std::vector < std::shared_ptr<Nuclide> >& l) : 
             temperature_(t), nuclides_(n), densities_(d), libNuclides_(l) {}

    Material() : temperature_(0.0), nuclides_(std::vector<std::string> {}),
                 densities_(std::vector<double> {}) {}
    
    void setTemperature(double t) {temperature_ = t;}
    double getTemperature() const {return temperature_;} 
    void setNuclides(const std::vector<std::string>& nuclides) {nuclides_ = nuclides;}
    std::vector<std::string> getNuclides() const {return nuclides_;}
    void setDensities(const std::vector<double>& densities) {densities_ = densities;}
    std::vector<double> getDensities() const {return densities_;}
    void setLibNuclides(const std::vector < std::shared_ptr<Nuclide> >& libNuclides) {libNuclides_ = libNuclides;}
    std::vector < std::shared_ptr<Nuclide> > setLibNuclides() const {return libNuclides_;}

    std::map<std::string, double> calculateBackgroundXS();
    void calculateMacroXS();

private:
    double temperature_;
    std::vector<std::string> nuclides_;
    std::vector<double> densities_;

    std::vector<MacroXSType> m_crossSections;
    std::vector<MacroXSMatrixType> m_crossSectionMatrices;

    std::vector < std::shared_ptr<Nuclide> > libNuclides_;
};

#endif