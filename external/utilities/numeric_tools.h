#ifndef NUMERIC_TOOLS_H
#define NUMERIC_TOOLS_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#include "Output.h"

#include <unsupported/Eigen/CXX11/Tensor>
#include <Eigen/Dense>
#include <functional>
#include <exception>

#include <limits>
#include <vector>

namespace Numerics
{
    const double DINF = std::numeric_limits<double>::max();
    const double DEPS = 10.0 * std::numeric_limits<double>::epsilon();

    typedef Eigen::Tensor<double, 2> Tensor2d;
    typedef Eigen::Tensor<double, 3> Tensor3d;
    typedef Eigen::Tensor<double, 4> Tensor4d;

    template <typename T>
    inline bool is_equal(const T &x, const T &y, double eps = DEPS)
    {
        return fabs(x - y) < eps;
    }

    template <typename T>
    inline bool not_equal(const T &x, const T &y, double eps = DEPS)
    {
    	return !is_equal(x, y, eps);
    }

    template <typename T>
    inline bool is_greater(const T &x, const T &y, double eps = DEPS)
    {
    	return x > y + eps;
    }

    template <typename T>
    inline bool is_greater_equal(const T &x, const T &y, double eps = DEPS)
    {
    	return x > y - eps;
    }

    template <typename T>
    inline bool is_lower(const T &x, const T &y, double eps = DEPS)
    {
    	return x < y - eps;
    }

    template <typename T>
    inline bool is_lower_equal(const T &x, const T &y, double eps = DEPS)
    {
    	return x < y + eps;
    }

    template <typename T>
    inline std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b)
    {
        if(a.size() != b.size())
            throw std::length_error("vectors have different lengths");

        std::vector<T> result;
        result.reserve(a.size());

        std::transform(a.begin(), a.end(), b.begin(), 
                       std::back_inserter(result), std::plus<T>());
        return result;
    }

    template <typename T>
    inline std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b)
    {
        if(a.size() != b.size())
            throw std::length_error("vectors have different lengths");

        std::vector<T> result;
        result.reserve(a.size());

        std::transform(a.begin(), a.end(), b.begin(), 
                       std::back_inserter(result), std::minus<T>());
        return result;
    }

    template <typename T>
    inline std::vector<T> operator*(const std::vector<T>& a, const T m)
    {
        std::vector<T> result;
        result.resize(a.size());

        std::transform(a.begin(), a.end(), result.begin(), [m](auto i){return i * m;});
        return result;
    }

    template <typename T>
    inline std::vector<T> operator/(const std::vector<T>& a, const T d)
    {
        if(is_equal(d, 0.0))
            throw std::overflow_error("division by zero");

        std::vector<T> result;
        result.resize(a.size());

        std::transform(a.begin(), a.end(), result.begin(), [d](auto i){return i / d;});
        return result;
    }

    template <typename T>
    inline std::vector<T>& operator+=(std::vector<T> &a, const std::vector<T>& b)
    {
        if(a.size() != b.size())
            throw std::length_error("vectors have different lengths");

        for (size_t i = 0; i < a.size(); i++)
            a[i] += b[i];

        return a;
    }

    template <typename T>
    inline std::vector<T>& operator-=(std::vector<T> &a, const std::vector<T>& b)
    {
        if(a.size() != b.size())
            throw std::length_error("vectors have different lengths");

       for (size_t i = 0; i < a.size(); i++)
           a[i] -= b[i];

        return a;
    }

    template <typename T>
    inline std::vector<T>& operator*=(std::vector<T> &a, const T m)
    {
    
        for (size_t i = 0; i < a.size(); i++)
           a[i] *= m;

        return a;
    }

    template <typename T>
    inline std::vector<T>& operator/=(std::vector<T> &a, const T d)
    {
        if(is_equal(d, 0.0))
            throw std::overflow_error("division by zero");

        for (size_t i = 0; i < a.size(); i++)
            a[i] /= d;

        return a;
    }

    template<typename T>
    std::vector<T> slice(std::vector<T> const &v, int m, int n) 
    {
       auto first = v.begin() + m;
       auto last = v.begin() + n + 1;
       std::vector<T> vector(first, last);
       return vector;
    }

    template<typename T>
    inline bool areVectorsEqual(std::vector<T> const &v, std::vector<T> const &ref, 
                                double eps = DEPS)
    {   
        bool result = true;

        if(v.size() == ref.size())
        {
            for(size_t i = 0; i < v.size(); i++)
                if(not_equal(v[i], ref[i], eps))
                    result = false;
        }
        else
        {
            result = false; 
        }

        return result;
    }

    template<typename T>
    inline std::pair<T, T> getInterval(T x, const std::vector<T>& vec, double eps = DEPS)
    {
        T lower = 0.0;
        for(const auto& val : vec)
            if(is_greater_equal(x, val, eps)) 
            {
                lower = val;
            }

        T higher = 0.0;
        for(const auto& val : vec)
            if(is_lower_equal(x, val, eps)) 
            {
                higher = val;
                break;
            }
        return std::make_pair(lower, higher);
    }

    inline std::vector<double> eigenVecTOStdVec(Eigen::VectorXd const& v)
    {   
        std::vector<double> result(v.data(), v.data() + v.rows() * v.cols());
        return result;
    }

    inline double linLinInterpolation(double x, double x0, double x1, double y0, double y1)
    {
        double a = (x1 - x) / (x1 - x0);
        double b = (x - x0) / (x1 - x0);
        return (a * y0 + b * y1);
    }

    inline double sqrtInterpolation(double x, double x0, double x1, double y0, double y1)
    {
        double a = (sqrt(x1) - sqrt(x)) / (sqrt(x1) - sqrt(x0));
        double b = (sqrt(x) - sqrt(x0)) / (sqrt(x1) - sqrt(x0));
        return (a * y0 + b * y1);
    }

    inline double logLinInterpolation(double x, double x0, double x1, double y0, double y1)
    {
        return (y0 + (log(x) - log(x0)) * (y1 - y0) / (log(x1) - log(x0)));
    }
}

#endif