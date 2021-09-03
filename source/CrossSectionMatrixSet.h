#ifndef CROSSSECTIONMATRIXSET_H
#define CROSSSECTIONMATRIXSET_H

#include "CrossSectionMatrix.h"
#include "CrossSectionSet.h"
#include "Interpolation.h"
#include "XSMatrixKind.h"
#include "numeric_tools.h"

using namespace Eigen;

class CrossSectionMatrixSet
{
public:
    CrossSectionMatrixSet() {}
	CrossSectionMatrixSet(XSMatrixKind xsKind) : m_kind(xsKind) {}

    void addXS(CrossSectionMatrix &xs) {m_XSSet.push_back(xs);}
    void setXS(unsigned i, CrossSectionMatrix &xs) {m_XSSet[i] = xs;}
    CrossSectionMatrix getXSMatrixNoInterp(unsigned i);
    CrossSectionMatrix getXSMatrixNoInterp(double t, double b);

    std::vector<double> getTemperatures();
    std::vector<double> getBackgroundXSs();
    unsigned getSize() const {return m_XSSet.size();}
    XSMatrixKind getKind() {return m_kind;}
    bool isEmpty() const;
    void calcXSMatrices();
    CrossSectionSet condenseToXSs();

    template <typename InterpolFuncT, typename InterpolFuncB>
    CrossSectionMatrix getXSMatrix(double t, InterpolFuncT funcT, double b, InterpolFuncB funcB)
    {   
        std::pair<double, double> temps   = Numerics::getInterval(t, getTemperatures());
        std::pair<double, double> backXSs = Numerics::getInterval(b, getBackgroundXSs());

        Eigen::MatrixXd result;

        if(getBackgroundXSs().size() > 1)
        {
            Eigen::MatrixXd Q11s = getXSMatrixNoInterp(temps.first,  backXSs.first).getValues();
            Eigen::MatrixXd Q12s = getXSMatrixNoInterp(temps.first,  backXSs.second).getValues();
            Eigen::MatrixXd Q21s = getXSMatrixNoInterp(temps.second, backXSs.first).getValues();
            Eigen::MatrixXd Q22s = getXSMatrixNoInterp(temps.second, backXSs.second).getValues();

            result = MatrixXd::Zero(Q11s.rows(), Q11s.cols());

            for(size_t i = 0; i < static_cast<size_t>(Q11s.rows()); i++)
            {
                for(size_t j = 0; j < static_cast<size_t>(Q11s.cols()); j++)
                {
                    funcT.setIntervals(temps.first, temps.second, Q11s(i, j), Q12s(i, j));
                    double funcxy1 = funcT(t);

                    funcT.setIntervals(temps.first, temps.second, Q21s(i, j), Q22s(i, j));
                    double funcxy2 = funcT(t); 

                    funcB.setIntervals(backXSs.first, backXSs.second, funcxy1, funcxy2);
                    result(i, j) = funcB(b);
                }
            }
        }
        else // non-resonant isotopes have only the infinite background XS
        {
            Eigen::MatrixXd Q1s = getXSMatrixNoInterp(temps.first,  backXSs.second).getValues();
            Eigen::MatrixXd Q2s = getXSMatrixNoInterp(temps.second, backXSs.second).getValues();

            result = MatrixXd::Zero(Q1s.rows(), Q1s.cols());

            for(size_t i = 0; i < static_cast<size_t>(Q1s.rows()); i++)
            {
                for(size_t j = 0; j < static_cast<size_t>(Q1s.cols()); j++)
                {
                    funcT.setIntervals(temps.first, temps.second, Q1s(i, j), Q2s(i, j));
                    result(i, j) = funcT(t);
                }
            }
        }

        CrossSectionMatrix matrix(t, b, result);
        return matrix;
    }

private:
    XSMatrixKind m_kind;
    std::vector<CrossSectionMatrix> m_XSSet;
};

#endif