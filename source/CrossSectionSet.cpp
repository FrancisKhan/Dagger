#include "CrossSectionSet.h"
#include "numeric_tools.h"
#include "additionalPrintFuncs.h"

#include <algorithm>
#include <iomanip>

void CrossSectionSet::getXS2(double t, double b)
{
    //std::cout << std::scientific << std::endl;
    std::cout << std::setprecision(10) << std::endl;

    //std::cout << "t: " << t << " b: " << b << std::endl;

    std::pair<double, double> temps = Numerics::getInterval(t, m_temperatures);
    //std::cout << "T lower: " << temps.first << " T higher: " << temps.second << std::endl;

    std::pair<double, double> bs = Numerics::getInterval(b, m_backgroundXSs);
    //std::cout << "B lower: " << bs.first << " B higher: " << bs.second << std::endl;

    // CrossSection Q11 = getXS(temps.first, bs.first);
    // CrossSection Q12 = getXS(temps.first, bs.second);
    // CrossSection Q21 = getXS(temps.second, bs.first);
    // CrossSection Q22 = getXS(temps.second, bs.second);

    double Q11 = getXS(temps.first, bs.first).getValues().back();
    double Q12 = getXS(temps.first, bs.second).getValues().back();
    double Q21 = getXS(temps.second, bs.first).getValues().back();
    double Q22 = getXS(temps.second, bs.second).getValues().back();

    // std::cout << "Q11: " << Q11 << std::endl;
    // std::cout << "Q12: " << Q12 << std::endl;
    // std::cout << "Q21: " << Q21 << std::endl;
    // std::cout << "Q22: " << Q22 << std::endl;

    double funcxy1 = Numerics::linLinInterpolation(t, temps.first, temps.second, Q11, Q12);
    double funcxy2 = Numerics::linLinInterpolation(t, temps.first, temps.second, Q21, Q22);

    // std::cout << "funcxy1: " << funcxy1 << std::endl;
    // std::cout << "funcxy2: " << funcxy2 << std::endl;

    double funcxy = Numerics::linLinInterpolation(b, bs.first, bs.second, funcxy1, funcxy2);

    //std::cout << "funcxy: " << funcxy << std::endl;
}

CrossSection CrossSectionSet::getXS(double t, double b)
{
    std::vector<CrossSection>::iterator it = std::find_if(m_XSSet.begin(), m_XSSet.end(), 
    [t, b] (CrossSection &c) 
    {return Numerics::is_equal(c.getTemperature(), t) && Numerics::is_equal(c.getBackgroundXS(), b);});

    if (it != m_XSSet.end())
        return *it;
    else
        return CrossSection {};
}

void CrossSectionSet::calcXSs() 
{
    using namespace Numerics;

    for(unsigned i = 0; i < getSize(); i++)
    {
        double sigma0 = getXS(i).getBackgroundXS();
        double temp   = getXS(i).getTemperature();

        if(Numerics::not_equal(sigma0, Numerics::DINF))
        {
            std::vector<double> infValues = getXS(temp, Numerics::DINF).getValues();
            std::vector<double> dilValues = getXS(i).getValues();
            std::vector<double> newValues = infValues + dilValues;

            //debugCalcXS(newValues, infValues, dilValues, temp, sigma0);

            CrossSection xs(temp, sigma0, newValues);
            setXS(i, xs);
        }
    }
}

void CrossSectionSet::debugCalcXS(std::vector<double> &newValues, std::vector<double> &infValues,
        std::vector<double> &dilValues, double temp, double sigma0) 
{
    auto it = std::find_if(newValues.begin(), newValues.end(), 
              [] (auto &v) {return Numerics::is_lower(v, 0.0);});

    if (it != newValues.end())
    {
        out.print(TraceLevel::CRITICAL, "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
        out.print(TraceLevel::CRITICAL, "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
        out.print(TraceLevel::CRITICAL, "XS kind: {}", get_name(getKind()));
        out.print(TraceLevel::CRITICAL, "Temperature: {}", temp);
        out.print(TraceLevel::CRITICAL, "Background XS: {}", sigma0);

        out.print(TraceLevel::CRITICAL, "\nInfinite XS:");
        PrintFuncs::printVector(infValues, out, TraceLevel::CRITICAL);

        out.print(TraceLevel::CRITICAL, "Diluted XS:");
        PrintFuncs::printVector(dilValues, out, TraceLevel::CRITICAL);

        out.print(TraceLevel::CRITICAL, "New XS:");
        PrintFuncs::printVector(newValues, out, TraceLevel::CRITICAL);

        throw std::runtime_error("ERROR: error in CalcXS");
    }
}