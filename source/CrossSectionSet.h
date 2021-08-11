#ifndef CROSSSECTIONSET_H
#define CROSSSECTIONSET_H

#include "Interpolation.h"
#include "numeric_tools.h"
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
    CrossSection getXSNoInterp(unsigned i) {return m_XSSet.at(i);}
    CrossSection getXSNoInterp(double t, double b);
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

    template <typename InterpolFuncT, typename InterpolFuncB>
    CrossSection getXS(double t, InterpolFuncT funcT, double b, InterpolFuncB funcB)
    {   
        std::vector<double> result;

        std::pair<double, double> temps   = Numerics::getInterval(t, m_temperatures);
        std::pair<double, double> backXSs = Numerics::getInterval(b, m_backgroundXSs);

        std::vector<double> Q11s = getXSNoInterp(temps.first,  backXSs.first).getValues();
        std::vector<double> Q12s = getXSNoInterp(temps.first,  backXSs.second).getValues();
        std::vector<double> Q21s = getXSNoInterp(temps.second, backXSs.first).getValues();
        std::vector<double> Q22s = getXSNoInterp(temps.second, backXSs.second).getValues();

        for(size_t i = 0; i < Q11s.size(); i++)
        {
            funcT.setIntervals(temps.first, temps.second, Q11s[i], Q12s[i]);
            double funcxy1 = funcT(t);

            funcT.setIntervals(temps.first, temps.second, Q21s[i], Q22s[i]);
            double funcxy2 = funcT(t); 

            funcB.setIntervals(backXSs.first, backXSs.second, funcxy1, funcxy2);
            result.push_back(funcB(b));
        }

        CrossSection xs(t, b, result);
        return xs;
    }


private:
    XSKind m_kind;
    std::vector<CrossSection> m_XSSet;
    std::vector<double> m_temperatures;
    std::vector<double> m_backgroundXSs;
};

#endif