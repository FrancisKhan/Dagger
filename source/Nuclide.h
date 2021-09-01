#ifndef NUCLIDE_H
#define NUCLIDE_H

#include "numeric_tools.h"
#include "CrossSectionSet.h"
#include "CrossSectionMatrixSet.h"

#include <memory>
#include <vector>
#include <string>

class Nuclide
{
public:

    typedef std::pair<XSKind, CrossSectionSet> XSSetType;
    typedef std::pair<XSMatrixKind, CrossSectionMatrixSet> XSMatrixSetType;

	Nuclide();
    Nuclide(std::string name) : m_name(name),m_isResonant(false), 
                                m_isFissionable(false) {}

    void setName(std::string name) {m_name = name;}
    std::string getName() {return m_name;}
    void setAWR(double awr) {m_awr = awr;}
    double getAWR() {return m_awr;}
    void setIsResonant(bool value) {m_isResonant = value;}
    bool isResonant() const {return m_isResonant;}
    void setIsFissionable(bool value) {m_isFissionable = value;}
    bool isFissionable() const {return m_isFissionable;}
    void setTemperatures(std::vector<double> &temps) {m_temperatures = temps;}
    std::vector<double> getTemperatures() {return m_temperatures;}
    void setLambdas(std::vector<double> &lambdas) {m_lambdas = lambdas;}
    std::vector<double> getLambdas() {return m_lambdas;}
    double getTemperature(unsigned i) {return m_temperatures.at(i);}
    void setDilutions(std::vector<double> &values) {m_dilutions = values;}
    std::vector<double> getDilutions() {return m_dilutions;}
    double getDilution(unsigned i) {return m_dilutions.at(i);}
    void setEnergyGroupsNumber(unsigned n) {m_energyGroupsNumber = n;}
    unsigned getEnergyGroupsNumber() {return m_energyGroupsNumber;}
    unsigned getXSsNumber() {return isResonant() ? (getDilutions().size() * getTemperatures().size()) : getTemperatures().size();}

    void setPotXS(double potXS) {m_potXS = potXS;}
    double getPotXS() const {return m_potXS;}

    // Cross section sets

    CrossSectionSet getXSSet(XSKind xsKind);
    static CrossSectionSet& getXSSet(XSKind xsKind, std::vector<XSSetType>& crossSectionSets);
    std::vector<XSSetType>& getXSSets() {return m_crossSectionSets;}
    std::vector<XSSetType> getCopyOfXSSets() {return m_crossSectionSets;}

    void setXSSets(std::vector<XSSetType>& crossSectionSets) {m_crossSectionSets = crossSectionSets;}
    void calcXSSets();

    // Cross section matrix sets

    CrossSectionMatrixSet getXSMatrixSet(XSMatrixKind kind);
    static CrossSectionMatrixSet& getXSMatrixSet(XSMatrixKind kind, std::vector<XSMatrixSetType>& crossSectionMatrixSets);
    std::vector<XSMatrixSetType>& getXSMatrixSets() {return m_crossSectionMatrixSets;}
    std::vector<XSMatrixSetType> getCopyOfXSMatrixSets() {return m_crossSectionMatrixSets;}

    void setXSMatrixSets(std::vector<XSMatrixSetType>& crossSectionMatrixSets) {m_crossSectionMatrixSets = crossSectionMatrixSets;}
    void calcXSMatrixSets();

    void printDebugData();
    void printXSs(XSKind kind);
    void printMatrixXSs(XSMatrixKind xsKind);

private:

    std::string m_name;
    double m_awr;
    std::vector<double> m_temperatures;
    std::vector<double> m_lambdas;
    std::vector<double> m_dilutions;
    unsigned m_energyGroupsNumber;
    bool m_isResonant;
    bool m_isFissionable;
    double m_potXS;

    std::vector<XSSetType> m_crossSectionSets;
    std::vector<XSMatrixSetType> m_crossSectionMatrixSets;
};

#endif