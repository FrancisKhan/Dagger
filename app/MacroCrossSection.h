#ifndef MACROCROSSSECTION_H
#define MACROCROSSSECTION_H

#include <vector>
#include <string>

#include "XSKind.h"

class MacroCrossSection
{
public:
    MacroCrossSection() : temperature_(0.0), values_(std::vector<double> {}) {}
    
	MacroCrossSection(XSKind xsKind, double temperature, const std::vector<double> &values) :
    xsKind_(xsKind), temperature_(temperature), values_(values) {}

    void setKind(XSKind xsKind) {xsKind_ = xsKind;}
    XSKind getKind() const {return xsKind_;} 
    void setTemperature(double t) {temperature_ = t;}
    double getTemperature() const {return temperature_;} 
    void setValues(const std::vector<double> &v) {values_ = v;}
    std::vector<double> getValues() const {return values_;}
    unsigned getSize() const {return values_.size();}

private:
    XSKind xsKind_;
    double temperature_;
    std::vector<double> values_;
};

#endif