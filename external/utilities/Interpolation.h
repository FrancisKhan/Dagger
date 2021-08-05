#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <cmath>

class InterpolationFunc 
{
public:
    double x0_, x1_, y0_, y1_;

    InterpolationFunc() : x0_(0.0), x1_(0.0), y0_(0.0), y1_(0.0) {};
    virtual double operator() (double x) = 0;
    void setIntervals(double x0, double x1, double y0, double y1)
    {
        x0_ = x0;
        x1_ = x1;
        y0_ = y0;
        y1_ = y1;
    }
};
                                                                                                                                                                                                   
class LinLin : public InterpolationFunc
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

class Sqrt : public InterpolationFunc
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

class LogLin : public InterpolationFunc
{
public:
    LogLin() {};
    virtual double operator() (double x) 
    {
        return (y0_ + (log(x) - log(x0_)) * (y1_ - y0_) / (log(x1_) - log(x0_)));
    }
};

#endif