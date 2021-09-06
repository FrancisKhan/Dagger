#include "CrossSection.h"

void CrossSection::setToZero() 
{
    size_t size = m_values.size();
    m_values.clear();
    m_values.resize(size, 0.0);
}

bool CrossSection::hasOnlyZeroes() const
{
    if(std::all_of(m_values.begin(), m_values.end(), [](const double i)
       {return Numerics::is_equal(i, 0.0);}))
        return true;
    else
        return false;
}

CrossSection CrossSection::operator+(const CrossSection& rhs)
{
    std::vector<double> rhsVec = rhs.getValues();
    std::vector<double> lhsVec = getValues();
                
    std::vector<double> resultVec(rhsVec.size(), 0.0);
    std::transform(lhsVec.begin(), lhsVec.end(), rhsVec.begin(), resultVec.begin(), std::plus<double>());

    CrossSection xs(getTemperature(), getBackgroundXS(), resultVec);

    return xs;
}

CrossSection& CrossSection::operator+=(const CrossSection& rhs)
{
    for(size_t i = 0; i < m_values.size(); i++)
        m_values[i] += rhs.getValues()[i];

    return *this;
}

CrossSection CrossSection::operator-(const CrossSection& rhs)
{
    std::vector<double> rhsVec = rhs.getValues();
    std::vector<double> lhsVec = getValues();
                
    std::vector<double> resultVec(rhsVec.size(), 0.0);
    std::transform(lhsVec.begin(), lhsVec.end(), rhsVec.begin(), resultVec.begin(), std::minus<double>());

    CrossSection xs(getTemperature(), getBackgroundXS(), resultVec);

    return xs;
}

CrossSection& CrossSection::operator-=(const CrossSection& rhs)
{
   for(size_t i = 0; i < m_values.size(); i++)
        m_values[i] -= rhs.getValues()[i];

    return *this;
}
