#ifndef CROSSSECTIONMATRIXSET_H
#define CROSSSECTIONMATRIXSET_H

#include "CrossSectionMatrix.h"
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
    unsigned getSize() {return m_XSSet.size();}
    XSMatrixKind getKind() {return m_kind;}
    void calcXSMatrices();

    template <typename InterpolFuncT, typename InterpolFuncB>
    CrossSectionMatrix getXSMatrix(double t, InterpolFuncT funcT, double b, InterpolFuncB funcB)
    {   
        std::pair<double, double> temps   = Numerics::getInterval(t, getTemperatures());
        std::pair<double, double> backXSs = Numerics::getInterval(b, getBackgroundXSs());

        Eigen::MatrixXd Q11s = getXSMatrixNoInterp(temps.first,  backXSs.first).getValues();
        Eigen::MatrixXd Q12s = getXSMatrixNoInterp(temps.first,  backXSs.second).getValues();
        Eigen::MatrixXd Q21s = getXSMatrixNoInterp(temps.second, backXSs.first).getValues();
        Eigen::MatrixXd Q22s = getXSMatrixNoInterp(temps.second, backXSs.second).getValues();

        Eigen::MatrixXd result = MatrixXd::Zero(Q11s.rows(), Q11s.cols());

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

        CrossSectionMatrix matrix(t, b, result);
        return matrix;
    }

private:
    XSMatrixKind m_kind;
    std::vector<CrossSectionMatrix> m_XSSet;
};

#endif