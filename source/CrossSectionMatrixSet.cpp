#include "CrossSectionMatrixSet.h"
#include "additionalPrintFuncs.h"

using namespace Numerics;

CrossSectionMatrixSet CrossSectionMatrixSet::operator/(const CrossSectionSet& rhs)
{
    std::vector<double> temperatures = getTemperatures();
    std::vector<double> dilutions = getBackgroundXSs();

    CrossSectionMatrixSet result;

    for(size_t i = 0; i < temperatures.size(); i++)
    {
        for(size_t j = 0; j < dilutions.size(); j++)
        {
            std::vector<double> rhsVec = rhs.getXSNoInterp(temperatures[i], dilutions[j]).getValues();
            Eigen::MatrixXd lhsMat = getXSMatrixNoInterp(temperatures[i], dilutions[j]).getValues();
                
            Eigen::MatrixXd resultMat = Eigen::MatrixXd::Zero(rhsVec.size(), rhsVec.size());

            for(unsigned i = 0; i < resultMat.rows(); i++)
        	    for(unsigned j = 0; j < resultMat.cols(); j++)
            	    resultMat(i, j) = lhsMat(i, j) / rhsVec[i];

            CrossSectionMatrix crossSectionMatrix(temperatures[i], dilutions[j], resultMat);
            result.addXS(crossSectionMatrix);
        }
    }

    return result;
}

void CrossSectionMatrixSet::calcXSMatrices() 
{
    for(unsigned i = 0; i < getSize(); i++)
    {
        double sigma0 = getXSMatrixNoInterp(i).getBackgroundXS();
        double temp   = getXSMatrixNoInterp(i).getTemperature();

        if(not_equal(sigma0, DINF))
        {
            Eigen::MatrixXd infValues = getXSMatrixNoInterp(temp, DINF).getValues();
            Eigen::MatrixXd dilValues = getXSMatrixNoInterp(i).getValues();
            Eigen::MatrixXd newValues = infValues + dilValues;

            CrossSectionMatrix matrix(temp, sigma0, newValues);
            setXS(i, matrix);
        }
    }
}

CrossSectionMatrix CrossSectionMatrixSet::getXSMatrixNoInterp(double t, double b)
{
    std::vector<CrossSectionMatrix>::iterator it = std::find_if(XSSet_.begin(), XSSet_.end(), 
    [t, b] (CrossSectionMatrix &c) 
    {return Numerics::is_equal(c.getTemperature(), t) && Numerics::is_equal(c.getBackgroundXS(), b);});

    if (it != XSSet_.end())
        return *it;
    else
        return CrossSectionMatrix {};
}

CrossSectionMatrix CrossSectionMatrixSet::getXSMatrixNoInterp(unsigned i)
{
    if(!XSSet_.empty())
        return XSSet_.at(i);
    else
        return CrossSectionMatrix {};
}

std::vector<double> CrossSectionMatrixSet::getTemperatures()
{
    std::vector<double> result;

    for(const auto& i : XSSet_)
        result.push_back(i.getTemperature());

    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;   
}

std::vector<double> CrossSectionMatrixSet::getBackgroundXSs()
{
    std::vector<double> result;

    for(const auto& i : XSSet_)
        result.push_back(i.getBackgroundXS());

    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;   
}

CrossSectionSet CrossSectionMatrixSet::condenseToXSs()
{
    CrossSectionSet xsSet;

    for(const auto& s : XSSet_)
        xsSet.addXS(s.condenseToXS());

    return xsSet;
}

// It is unlikely that a XSSet has a XS(t_i, b_i) empty and others with values
bool CrossSectionMatrixSet::isEmpty() const
{
    if(XSSet_[0].getSize() != 0)
    {
        if(XSSet_[0].hasOnlyZeroes())
            return true;
        else
            return false;
    }
    else
        return true;
}