#ifndef CROSSSECTIONMATRIX_H
#define CROSSSECTIONMATRIX_H

#include "numeric_tools.h"
#include "CrossSection.h"

class CrossSectionMatrix
{
public:
    CrossSectionMatrix() : temperature_(0.0), backgroundXS_(0.0) {}
    
	CrossSectionMatrix(double temperature, double backgroundXS, const Eigen::MatrixXd& values) :
    temperature_(temperature), backgroundXS_(backgroundXS), values_(values) {}

    void setTemperature(double t) {temperature_ = t;}
    double getTemperature() const {return temperature_;}
    void setBackgroundXS(double b) {backgroundXS_ = b;}
    double getBackgroundXS() const {return backgroundXS_;}
    void setValues(Eigen::MatrixXd &m) {values_ = m;}
    Eigen::MatrixXd getValues() const {return values_;}
    unsigned getSize() const {return values_.rows();}
    CrossSection condenseToXS() const;
    bool hasOnlyZeroes() const;
    void setToZero();

    CrossSectionMatrix operator+(const CrossSectionMatrix& rhs);
    CrossSectionMatrix operator-(const CrossSectionMatrix& rhs);
    CrossSectionMatrix& operator+=(const CrossSectionMatrix& rhs);
    CrossSectionMatrix& operator-=(const CrossSectionMatrix& rhs);

private:
    double temperature_;
    double backgroundXS_;
    Eigen::MatrixXd values_;
};

inline CrossSectionMatrix operator*(const double lhs, const CrossSectionMatrix& rhs)
{
    Eigen::MatrixXd rhsMat = rhs.getValues();
    Eigen::MatrixXd resultMat = Eigen::MatrixXd::Zero(rhsMat.rows(), rhsMat.cols());

    for(unsigned i = 0; i < rhsMat.rows(); i++)
        for(unsigned j = 0; j < rhsMat.cols(); j++)
            resultMat(i, j) = lhs * rhsMat(i, j);

    CrossSectionMatrix xsMat(rhs.getTemperature(), rhs.getBackgroundXS(), resultMat);
    return xsMat;
}

#endif