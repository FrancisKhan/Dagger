#include "CrossSection.h"

void CrossSection::setToZero() 
{
    size_t size = values_.size();
    values_.clear();
    values_.resize(size, 0.0);
}

bool CrossSection::hasOnlyZeroes() const
{
    if(std::all_of(values_.begin(), values_.end(), [](const double i)
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
    for(size_t i = 0; i < values_.size(); i++)
        values_[i] += rhs.getValues()[i];

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
   for(size_t i = 0; i < values_.size(); i++)
        values_[i] -= rhs.getValues()[i];

    return *this;
}

CrossSection& operator*=(CrossSection& lhs, double rhs)
{
    for(size_t i = 0; i < lhs.values_.size(); i++)
        lhs.values_[i] *= rhs;

    return lhs;
}
