#include "CrossSectionSet.h"
#include "additionalPrintFuncs.h"

#include <algorithm>
#include <iomanip>

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