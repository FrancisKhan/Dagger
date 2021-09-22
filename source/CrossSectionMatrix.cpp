#include "CrossSectionMatrix.h"
#include "numeric_tools.h"

void CrossSectionMatrix::setToZero() 
{
    unsigned rows = values_.rows();
    unsigned cols = values_.cols();
    values_ = Eigen::MatrixXd::Zero(rows, cols);
}

CrossSection CrossSectionMatrix::condenseToXS() const
{
    std::vector<double> newValues = Numerics::eigenVecTOStdVec(values_.rowwise().sum());
    CrossSection xs(temperature_, backgroundXS_, newValues);
    return xs;
}

bool CrossSectionMatrix::hasOnlyZeroes() const
{
    if(Numerics::is_equal(values_.maxCoeff(), 0.0))
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
            values_(i, j) += rhsMat(i, j);

    return *this;
}

CrossSectionMatrix& CrossSectionMatrix::operator-=(const CrossSectionMatrix& rhs)
{
    Eigen::MatrixXd rhsMat = rhs.getValues();

    for(unsigned i = 0; i < rhsMat.rows(); i++)
        for(unsigned j = 0; j < rhsMat.cols(); j++)
            values_(i, j) -= rhsMat(i, j);

    return *this;
}