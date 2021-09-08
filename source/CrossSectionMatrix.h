#ifndef CROSSSECTIONMATRIX_H
#define CROSSSECTIONMATRIX_H

#include "numeric_tools.h"
#include "CrossSection.h"

class CrossSectionMatrix
{
public:
    CrossSectionMatrix() : m_temperature(0.0), m_backgroundXS(0.0) {}
    
	CrossSectionMatrix(double temperature, double backgroundXS, const Eigen::MatrixXd& values) :
    m_temperature(temperature), m_backgroundXS(backgroundXS), m_values(values) {}

    void setTemperature(double t) {m_temperature = t;}
    double getTemperature() const {return m_temperature;}
    void setBackgroundXS(double b) {m_backgroundXS = b;}
    double getBackgroundXS() const {return m_backgroundXS;}
    void setValues(Eigen::MatrixXd &m) {m_values = m;}
    Eigen::MatrixXd getValues() const {return m_values;}
    unsigned getSize() const {return m_values.rows();}
    CrossSection condenseToXS() const;
    bool hasOnlyZeroes() const;
    void setToZero();

    CrossSectionMatrix operator+(const CrossSectionMatrix& rhs);
    CrossSectionMatrix operator-(const CrossSectionMatrix& rhs);
    CrossSectionMatrix& operator+=(const CrossSectionMatrix& rhs);
    CrossSectionMatrix& operator-=(const CrossSectionMatrix& rhs);

private:
    double m_temperature;
    double m_backgroundXS;
    Eigen::MatrixXd m_values;
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