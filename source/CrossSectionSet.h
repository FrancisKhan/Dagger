#ifndef CROSSSECTIONSET_H
#define CROSSSECTIONSET_H

#include "Interpolation.h"
#include "CrossSection.h"
#include "XSKind.h"

#include <vector>

class CrossSectionSet
{
public:
    CrossSectionSet() {}
	CrossSectionSet(XSKind xsKind) : m_kind(xsKind) {}

    void addXS(CrossSection &xs) {m_XSSet.push_back(xs);}
    void setXS(unsigned i, CrossSection &xs) {m_XSSet[i] = xs;}
    CrossSection getXS(unsigned i) {return m_XSSet.at(i);}
    CrossSection getXS(double t, double b);
    void getXS2(double t, double b);
    double getXS3(double t, InterpolationFunc* func);
    unsigned getSize() {return m_XSSet.size();}
    XSKind getKind() {return m_kind;}
    void setKind(XSKind xsKind) {m_kind = xsKind;}
    void setTemperatures(std::vector<double>& temperatures) {m_temperatures = temperatures;}
    std::vector<double> getTemperatures() {return m_temperatures;}
    void setBackgroundXSs(std::vector<double>& backgroundXSs) {m_backgroundXSs = backgroundXSs;}
    std::vector<double> getBackgroundXSs() {return m_backgroundXSs;}
    void calcXSs();

    void debugCalcXS(std::vector<double> &newValues, std::vector<double> &infValues,
    std::vector<double> &dilValues, double temp, double sigma0);

    template <typename InterpolFunc>
    double getXS3(double x, InterpolFunc func)
    {    
        func.setIntervals(3.0, 5.0, 10.0, 15.0);
        return func(x);
    }

private:
    XSKind m_kind;
    std::vector<CrossSection> m_XSSet;
    std::vector<double> m_temperatures;
    std::vector<double> m_backgroundXSs;
};

#endif