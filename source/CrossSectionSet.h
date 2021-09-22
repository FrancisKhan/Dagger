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
	CrossSectionSet(XSKind xsKind) : kind_(xsKind) {}

    void addXS(const CrossSection &xs) {XSSet_.push_back(xs);}
    void setXS(unsigned i, const CrossSection &xs) {XSSet_[i] = xs;}
    CrossSection getXSNoInterp(unsigned i) {return XSSet_.at(i);}
    CrossSection getXSNoInterp(double t, double b) const;
    unsigned getSize() {return XSSet_.size();}
    XSKind getKind() {return kind_;}
    void setKind(XSKind xsKind) {kind_ = xsKind;}
    std::vector<double> getTemperatures() const;
    std::vector<double> getBackgroundXSs() const;
    void calcXSs();
    void deleteXSs() {XSSet_.clear();}
    bool isEmpty() const;
    size_t getNumberOfEnergyGroups() const {return XSSet_.front().getSize();}

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

        if(getBackgroundXSs().size() > 1)
        {
            std::vector<double> Q11s = getXSNoInterp(temps.first,  backXSs.first).getValues();
            std::vector<double> Q12s = getXSNoInterp(temps.first,  backXSs.second).getValues();
            std::vector<double> Q21s = getXSNoInterp(temps.second, backXSs.first).getValues();
            std::vector<double> Q22s = getXSNoInterp(temps.second, backXSs.second).getValues();

            for(size_t i = 0; i < Q11s.size(); i++)
            {
                funcT.setIntervals(temps.first, temps.second, Q11s[i], Q21s[i]);
                double funcxy1 = funcT(t);

                funcT.setIntervals(temps.first, temps.second, Q12s[i], Q22s[i]);
                double funcxy2 = funcT(t); 

                funcB.setIntervals(backXSs.first, backXSs.second, funcxy1, funcxy2);
                result.push_back(funcB(b));
            }
        }
        else // non-resonant isotopes have only the infinite background XS
        {
            std::vector<double> Q1s = getXSNoInterp(temps.first,  backXSs.second).getValues();
            std::vector<double> Q2s = getXSNoInterp(temps.second, backXSs.second).getValues();

            for(size_t i = 0; i < Q1s.size(); i++)
            {
                funcT.setIntervals(temps.first, temps.second, Q1s[i], Q2s[i]);
                result.push_back(funcT(t));
            }
        }

        CrossSection xs(t, b, result);
        return xs;
    }

private:
    XSKind kind_;
    std::vector<CrossSection> XSSet_;
};

inline CrossSectionSet operator+(const double lhs, const CrossSectionSet& rhs)
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
            std::transform(rhsVec.begin(), rhsVec.end(), resultVec.begin(), [lhs](auto k){return lhs + k;});

            CrossSection crossSection(temperatures[i], dilutions[j], resultVec);
            result.addXS(crossSection);
        }
    }

    return result;
}

inline CrossSectionSet operator-(const double lhs, const CrossSectionSet& rhs)
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
            std::transform(rhsVec.begin(), rhsVec.end(), resultVec.begin(), [lhs](auto k){return lhs - k;});

            CrossSection crossSection(temperatures[i], dilutions[j], resultVec);
            result.addXS(crossSection);
        }
    }

    return result;
}

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