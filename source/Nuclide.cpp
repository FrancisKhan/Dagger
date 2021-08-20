#include "Nuclide.h"
#include "Output.h"
#include "additionalPrintFuncs.h"

Nuclide::Nuclide() 
{
    m_isResonant = false; 

    for (const auto& xsKind : XSKind())
    {
        CrossSectionSet crossSectionSet(xsKind);
        Nuclide::XSSetType tempPair = std::make_pair(xsKind, crossSectionSet);
        m_crossSectionSets.push_back(tempPair);
    }

    for (const auto& xsKind : XSMatrixKind())
    {
        CrossSectionMatrixSet crossSectionMatrixSet(xsKind);
        Nuclide::XSMatrixSetType tempPair = std::make_pair(xsKind, crossSectionMatrixSet);
        m_crossSectionMatrixSets.push_back(tempPair);
    }
}

CrossSectionSet Nuclide::getXSSet(XSKind kind) 
{
    static CrossSectionSet crossSectionSet;

    std::vector<Nuclide::XSSetType>::iterator it = std::find_if(m_crossSectionSets.begin(), m_crossSectionSets.end(), 
    [kind] (Nuclide::XSSetType &p) {return p.first == kind;});

    if (it != m_crossSectionSets.end()) 
        return it->second;
    else
        return crossSectionSet;
}

CrossSectionSet& Nuclide::getXSSet(XSKind kind, std::vector<XSSetType>& crossSectionSets) 
{
    static CrossSectionSet crossSectionSet;

    std::vector<Nuclide::XSSetType>::iterator it = std::find_if(crossSectionSets.begin(), crossSectionSets.end(), 
    [kind, &crossSectionSets] (Nuclide::XSSetType &p) {return p.first == kind;});

    if (it != crossSectionSets.end()) 
        return it->second;
    else
        return crossSectionSet;
}

CrossSectionMatrixSet Nuclide::getXSMatrixSet(XSMatrixKind kind) 
{
    static CrossSectionMatrixSet crossSectionMatrixSet;

    std::vector<Nuclide::XSMatrixSetType>::iterator it = std::find_if(m_crossSectionMatrixSets.begin(), 
    m_crossSectionMatrixSets.end(), [kind] (Nuclide::XSMatrixSetType &m) {return m.first == kind;});

    if (it != m_crossSectionMatrixSets.end()) 
        return it->second;
    else
        return crossSectionMatrixSet;
}

CrossSectionMatrixSet& Nuclide::getXSMatrixSet(XSMatrixKind kind, std::vector<XSMatrixSetType>& crossSectionMatrixSets) 
{
    static CrossSectionMatrixSet crossSectionMatrixSet;

    std::vector<Nuclide::XSMatrixSetType>::iterator it = std::find_if(crossSectionMatrixSets.begin(), 
    crossSectionMatrixSets.end(), [kind] (Nuclide::XSMatrixSetType &m) {return m.first == kind;});

    if (it != crossSectionMatrixSets.end()) 
        return it->second;
    else
        return crossSectionMatrixSet;
}

void Nuclide::calcXSSets()
{
    for(auto& xsSet : m_crossSectionSets)
       xsSet.second.calcXSs();
}

void Nuclide::calcXSMatrixSets()
{
    for(auto& xsMatrixSet : m_crossSectionMatrixSets)
       xsMatrixSet.second.calcXSMatrices();
}

void Nuclide::printXSs(XSKind xsKind)
{
    for(size_t i = 0; i < getXSsNumber(); i++)
    {
        out.print(TraceLevel::CRITICAL, "{} XS: {}",  get_name(xsKind), getXSSet(xsKind).getXSNoInterp(0).getSize());
        out.print(TraceLevel::CRITICAL, "Temperature: {}, Background XS: {}", 
        getXSSet(xsKind).getXSNoInterp(i).getTemperature(), getXSSet(xsKind).getXSNoInterp(i).getBackgroundXS());

        PrintFuncs::printVector(getXSSet(xsKind).getXSNoInterp(i).getValues(), out, TraceLevel::CRITICAL);
    }
}

void Nuclide::printMatrixXSs(XSMatrixKind xsKind)
{
    for(size_t i = 0; i < getXSsNumber(); i++)
    {
        out.print(TraceLevel::CRITICAL, "{} XS Matrix: {}",  get_name(xsKind), getXSMatrixSet(xsKind).getXSMatrixNoInterp(0).getSize());
        out.print(TraceLevel::CRITICAL, "Temperature: {}, Background XS: {}", 
        getXSMatrixSet(xsKind).getXSMatrixNoInterp(i).getTemperature(), getXSMatrixSet(xsKind).getXSMatrixNoInterp(i).getBackgroundXS());

        PrintFuncs::printMatrix(getXSMatrixSet(xsKind).getXSMatrixNoInterp(i).getValues(), out, TraceLevel::CRITICAL);
    }
}

void Nuclide::printDebugData()
{
    out.print(TraceLevel::CRITICAL, "Nuclide name: {}", getName());
    out.print(TraceLevel::CRITICAL, "Nuclide AWR: {}", getAWR());
    out.print(TraceLevel::CRITICAL, "Is nuclide resonant: {}", isResonant());
    out.print(TraceLevel::CRITICAL, "Temperatures:");
    PrintFuncs::printVector(getTemperatures(), out, TraceLevel::CRITICAL);
    out.print(TraceLevel::CRITICAL, "Lambdas:");
    PrintFuncs::printVector(getLambdas(), out, TraceLevel::CRITICAL);
    out.print(TraceLevel::CRITICAL, "getXSsNumber(): {}", int(getXSsNumber()));

    for (const auto& xsKind : XSKind())
        printXSs(xsKind);

    for (const auto& xsKind : XSMatrixKind())
        printMatrixXSs(xsKind);
}