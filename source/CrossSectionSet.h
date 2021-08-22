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

    void addXS(const CrossSection &xs) {m_XSSet.push_back(xs);}
    void setXS(unsigned i, CrossSection &xs) {m_XSSet[i] = xs;}
    CrossSection getXSNoInterp(unsigned i) {return m_XSSet.at(i);}
    CrossSection getXSNoInterp(double t, double b) const;
    unsigned getSize() {return m_XSSet.size();}
    XSKind getKind() {return m_kind;}
    void setKind(XSKind xsKind) {m_kind = xsKind;}
    std::vector<double> getTemperatures() const;
    std::vector<double> getBackgroundXSs() const;
    void calcXSs();
    void deleteXSs() {m_XSSet.clear();}
    bool isEmpty() const;

    CrossSectionSet operator/(const CrossSectionSet& rhs);
    CrossSectionSet operator+(const CrossSectionSet& rhs);
    CrossSectionSet operator-(const CrossSectionSet& rhs);
    
    CrossSectionSet operator/(const double rhs);
    CrossSectionSet operator*(const double rhs);

    void debugCalcXS(std::vector<double> &newValues, std::vector<double> &infValues,
    std::vector<double> &dilValues, double temp, double sigma0);

    template <typename InterpolFuncT, typename InterpolFuncB>
    CrossSection getXS(double t, InterpolFuncT funcT, double b, InterpolFuncB funcB)
    {   
        std::vector<double> result;

        std::pair<double, double> temps   = Numerics::getInterval(t, getTemperatures());
        std::pair<double, double> backXSs = Numerics::getInterval(b, getBackgroundXSs());

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
};

inline CrossSectionSet operator*(const double lhs, const CrossSectionSet& rhs)
{
    std::vector<double> temperatures = rhs.getTemperatures();
    std::vector<double> dilutions = rhs.getBackgroundXSs();

    CrossSectionSet result;

    for(size_t i = 0; i < temperatures.size(); i++)
    {
        for(size_t j = 0; j < dilutions.size(); j++)
        {
            std::vector<double> rhsVec = rhs.getXSNoInterp(temperatures[i], dilutions[j]).getValues();
                
            std::vector<double> resultVec(rhsVec.size(), 0.0);
            std::transform(rhsVec.begin(), rhsVec.end(), resultVec.begin(), [lhs](auto k){return k * lhs;});

            CrossSection crossSection(temperatures[i], dilutions[j], resultVec);
            result.addXS(crossSection);
        }
    }

    return result;
}

inline CrossSectionSet operator/(const double lhs, const CrossSectionSet& rhs)
{
    std::vector<double> temperatures = rhs.getTemperatures();
    std::vector<double> dilutions = rhs.getBackgroundXSs();

    CrossSectionSet result;

    for(size_t i = 0; i < temperatures.size(); i++)
    {
        for(size_t j = 0; j < dilutions.size(); j++)
        {
            std::vector<double> rhsVec = rhs.getXSNoInterp(temperatures[i], dilutions[j]).getValues();
                
            std::vector<double> resultVec(rhsVec.size(), 0.0);
            std::transform(rhsVec.begin(), rhsVec.end(), resultVec.begin(), [lhs](auto k){return k / lhs;});

            CrossSection crossSection(temperatures[i], dilutions[j], resultVec);
            result.addXS(crossSection);
        }
    }

    return result;
}

#endif