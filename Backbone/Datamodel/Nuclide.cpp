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
}

void Nuclide::setXSMatrix(CrossSectionMatrixSet &xsMatrixSet) 
{
    switch(xsMatrixSet.getKind()) 
    {
        case XSMatrixKind::SCAT00:
            m_scattMatrix00 = xsMatrixSet;
            m_scattMatrix00.calcXS();
            break;
        case XSMatrixKind::SCAT01:
            m_scattMatrix01 = xsMatrixSet;
            m_scattMatrix01.calcXS();
            break;
        default:
            out.print(TraceLevel::CRITICAL, "Error {} XS matrix not recognized!", get_name(xsMatrixSet.getKind()));
            exit(-1);
    }
}

CrossSectionSet& Nuclide::getXSSet(XSKind kind) 
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
    switch(kind) 
    {
        case XSMatrixKind::SCAT00:  return m_scattMatrix00;
        case XSMatrixKind::SCAT01:  return m_scattMatrix01;
        default: return CrossSectionMatrixSet {};
    }
}

void Nuclide::calcXSSets()
{
    for(auto& xsSet : m_crossSectionSets)
       xsSet.second.calcXSs();
}

void Nuclide::printXSs(XSKind xsKind)
{
    for(size_t i = 0; i < getXSsNumber(); i++)
    {
        out.print(TraceLevel::CRITICAL, "{} XS: {}",  get_name(xsKind), getXSSet(xsKind).getXS(0).getSize());
        out.print(TraceLevel::CRITICAL, "Temperature: {}, Background XS: {}", 
        getXSSet(xsKind).getXS(i).getTemperature(), getXSSet(xsKind).getXS(i).getBackgroundXS());

        PrintFuncs::printVector(getXSSet(xsKind).getXS(i).getValues(), out, TraceLevel::CRITICAL);
    }
}

void Nuclide::printMatrixXSs(XSMatrixKind xsKind)
{
    for(size_t i = 0; i < getXSsNumber(); i++)
    {
        out.print(TraceLevel::CRITICAL, "{} XS Matrix: {}",  get_name(xsKind), getXSMatrixSet(xsKind).getXSMatrix(0).getSize());
        out.print(TraceLevel::CRITICAL, "Temperature: {}, Background XS: {}", 
        getXSMatrixSet(xsKind).getXSMatrix(i).getTemperature(), getXSMatrixSet(xsKind).getXSMatrix(i).getBackgroundXS());

        PrintFuncs::printMatrix(getXSMatrixSet(xsKind).getXSMatrix(i).getValues(), out, TraceLevel::CRITICAL);
    }
}

void Nuclide::printDebugData()
{
    out.print(TraceLevel::CRITICAL, "Nuclide name: {}", getName());
    out.print(TraceLevel::CRITICAL, "Nuclide AWR: {}", getAWR());
    out.print(TraceLevel::CRITICAL, "Is nuclide resonant: {}", isResonant());
    out.print(TraceLevel::CRITICAL, "Temperatures:");
    out.print(TraceLevel::CRITICAL, "getXSsNumber(): {}", int(getXSsNumber()));
    PrintFuncs::printVector(getTemperatures(), out, TraceLevel::CRITICAL);

    for (const auto& xsKind : XSKind())
        printXSs(xsKind);

    for (const auto& xsKind : XSMatrixKind())
        printMatrixXSs(xsKind);
}