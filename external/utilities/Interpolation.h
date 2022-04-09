#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "numeric_tools.h"
#include <iostream>

using namespace Numerics;

class TwopointInterpolationFunc
{
public:
    TwopointInterpolationFunc() : x0_(0.0), x1_(0.0), y0_(0.0), y1_(0.0) {};
    virtual double operator() (double x) = 0;
    void setIntervals(double x0, double x1, double y0, double y1)
    {
        x0_ = x0;
        x1_ = x1;
        y0_ = y0;
        y1_ = y1;
    }

protected:
    double x0_, x1_, y0_, y1_;
};
                                                                                                                                                                                                   
class LinLin : public TwopointInterpolationFunc
{
public:
    LinLin() {};
    virtual double operator() (double x) 
    {
        double a = (x1_ - x) / (x1_ - x0_);
        double b = (x - x0_) / (x1_ - x0_);
        return (a * y0_ + b * y1_);   
    }
};

class Sqrt : public TwopointInterpolationFunc
{
public:
    Sqrt() {};
    virtual double operator() (double x) 
    {
        double a = (sqrt(x1_) - sqrt(x)) / (sqrt(x1_) - sqrt(x0_));
        double b = (sqrt(x) - sqrt(x0_)) / (sqrt(x1_) - sqrt(x0_));
        return (a * y0_ + b * y1_);   
    }
};

class LogLin : public TwopointInterpolationFunc
{
public:
    LogLin() {};
    virtual double operator() (double x) 
    {
        return (y0_ + (log(x) - log(x0_)) * (y1_ - y0_) / (log(x1_) - log(x0_)));
    }
};

class MultipointInterpolationFunc
{
public:
    MultipointInterpolationFunc() {};

    virtual double operator() (double x) = 0;
    void setIntervals(std::vector<double>& x0, std::vector<double>& y0)
    {
        x0_ = x0;
        y0_ = y0;
    }

protected:
    std::vector<double> x0_;
    std::vector<double> y0_;
};

class Lagrange : public MultipointInterpolationFunc
{
public:
    Lagrange() {};
    virtual double operator() (double x) 
    {
        double result = 0.0;
        for(size_t j = 0; j < y0_.size(); j++)
            result += y0_[j] * l(x, j);

        return result;
    }

private:
    double l(double x, unsigned j)
    {
        std::vector<double> x_m(x0_.size(), 0.0);
        std::transform(x0_.begin(), x0_.end(), x_m.begin(), [](auto i){return -i;});
        std::vector<double> numerator = prod_poly_i(x_m, j);

        std::vector<double> denominator(x0_.size(), 1.0);
        for(size_t m = 0; m < x0_.size(); m++)
            if(m != j) denominator[m] = (x0_[j] - x0_[m]);

        double denominatorProd = std::accumulate(denominator.begin(), 
                                 denominator.end(), 1.0, std::multiplies<double>());

        return evalPolFunction(numerator, x) / denominatorProd;
    }
};

#endif