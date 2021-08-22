#include "CrossSectionMatrix.h"
#include "numeric_tools.h"

CrossSection CrossSectionMatrix::condenseToXS() const
{
    std::vector<double> newValues = Numerics::eigenVecTOStdVec(m_values.rowwise().sum());
    CrossSection xs(m_temperature, m_backgroundXS, newValues);
    return xs;
}

bool CrossSectionMatrix::hasOnlyZeroes() const
{
    if(Numerics::is_equal(m_values.maxCoeff(), 0.0))
        return true;
    else
        return false;
}
