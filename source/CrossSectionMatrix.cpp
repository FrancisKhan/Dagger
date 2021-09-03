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

CrossSectionMatrix CrossSectionMatrix::operator+(const CrossSectionMatrix& rhs)
{
    Eigen::MatrixXd rhsMat = rhs.getValues();
    Eigen::MatrixXd lhsMat = getValues();
                
    Eigen::MatrixXd resultMat = Eigen::MatrixXd::Zero(rhsMat.rows(), rhsMat.cols());

    for(unsigned i = 0; i < rhsMat.rows(); i++)
        for(unsigned j = 0; j < rhsMat.cols(); j++)
            resultMat(i, j) = lhsMat(i, j) + rhsMat(i, j);

    CrossSectionMatrix xsMat(getTemperature(), getBackgroundXS(), resultMat);

    return xsMat;
}

CrossSectionMatrix CrossSectionMatrix::operator-(const CrossSectionMatrix& rhs)
{
    Eigen::MatrixXd rhsMat = rhs.getValues();
    Eigen::MatrixXd lhsMat = getValues();
                
    Eigen::MatrixXd resultMat = Eigen::MatrixXd::Zero(rhsMat.rows(), rhsMat.cols());

    for(unsigned i = 0; i < rhsMat.rows(); i++)
        for(unsigned j = 0; j < rhsMat.cols(); j++)
            resultMat(i, j) = lhsMat(i, j) - rhsMat(i, j);

    CrossSectionMatrix xsMat(getTemperature(), getBackgroundXS(), resultMat);

    return xsMat;
}

CrossSectionMatrix& CrossSectionMatrix::operator+=(const CrossSectionMatrix& rhs)
{
    Eigen::MatrixXd rhsMat = rhs.getValues();

    for(unsigned i = 0; i < rhsMat.rows(); i++)
        for(unsigned j = 0; j < rhsMat.cols(); j++)
            m_values(i, j) += rhsMat(i, j);

    return *this;
}

CrossSectionMatrix& CrossSectionMatrix::operator-=(const CrossSectionMatrix& rhs)
{
    Eigen::MatrixXd rhsMat = rhs.getValues();

    for(unsigned i = 0; i < rhsMat.rows(); i++)
        for(unsigned j = 0; j < rhsMat.cols(); j++)
            m_values(i, j) -= rhsMat(i, j);

    return *this;
}