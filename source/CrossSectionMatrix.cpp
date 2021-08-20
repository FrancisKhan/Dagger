#include "CrossSectionMatrix.h"

CrossSection CrossSectionMatrix::condenseToXS() const
{
    std::vector<double> newValues = Numerics::eigenVecTOStdVec(m_values.rowwise().sum());
    CrossSection xs(m_temperature, m_backgroundXS, newValues);
    return xs;
}