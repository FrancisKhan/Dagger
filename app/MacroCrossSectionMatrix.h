#ifndef MACROCROSSSECTIONMATRIX_H
#define MACROCROSSSECTIONMATRIX_H

#include <vector>
#include <string>

#include "numeric_tools.h"
#include "XSMatrixKind.h"

class MacroCrossSectionMatrix
{
public:
    MacroCrossSectionMatrix() : temperature_(0.0) {}
    
	MacroCrossSectionMatrix(XSMatrixKind xsKind, double temperature, const Eigen::MatrixXd& values) :
    xsKind_(xsKind), temperature_(temperature), values_(values) {}

    void setKind(XSMatrixKind xsKind) {xsKind_ = xsKind;}
    XSMatrixKind getKind() const {return xsKind_;} 
    void setTemperature(double t) {temperature_ = t;}
    double getTemperature() const {return temperature_;} 
    void setValues(const Eigen::MatrixXd &v) {values_ = v;}
    Eigen::MatrixXd getValues() const {return values_;}
    unsigned getSize() const {return values_.rows();}

private:
    XSMatrixKind xsKind_;
    double temperature_;
    Eigen::MatrixXd values_;
};

#endif