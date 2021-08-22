#include "CrossSection.h"

bool CrossSection::hasOnlyZeroes() const
{
    if(std::all_of(m_values.begin(), m_values.end(), [](const double i)
       {return Numerics::is_equal(i, 0.0);}))
        return true;
    else
        return false;
}
