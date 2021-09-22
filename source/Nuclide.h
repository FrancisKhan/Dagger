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
    Nuclide(std::string name) : name_(name),isResonant_(false), 
                                isFissionable_(false) {}

    void setName(std::string name) {name_ = name;}
    std::string getName() {return name_;}
    void setAWR(double awr) {awr_ = awr;}
    double getAWR() {return awr_;}
    void setIsResonant(bool value) {isResonant_ = value;}
    bool isResonant() const {return isResonant_;}
    void setIsFissionable(bool value) {isFissionable_ = value;}
    bool isFissionable() const {return isFissionable_;}
    void setTemperatures(std::vector<double> &temps) {temperatures_ = temps;}
    std::vector<double> getTemperatures() {return temperatures_;}
    void setLambdas(std::vector<double> &lambdas) {lambdas_ = lambdas;}
    std::vector<double> getLambdas() {return lambdas_;}
    double getTemperature(unsigned i) {return temperatures_.at(i);}
    void setDilutions(std::vector<double> &values) {dilutions_ = values;}
    std::vector<double> getDilutions() {return dilutions_;}
    double getDilution(unsigned i) {return dilutions_.at(i);}
    void setEnergyGroupsNumber(unsigned n) {energyGroupsNumber_ = n;}
    unsigned getEnergyGroupsNumber() {return energyGroupsNumber_;}
    unsigned getXSsNumber() {return isResonant() ? (getDilutions().size() * getTemperatures().size()) : getTemperatures().size();}

    void setPotXS(double potXS) {potXS_ = potXS;}
    double getPotXS() const {return potXS_;}

    // Cross section sets

    CrossSectionSet getXSSet(XSKind xsKind);
    static CrossSectionSet& getXSSet(XSKind xsKind, std::vector<XSSetType>& crossSectionSets);
    std::vector<XSSetType>& getXSSets() {return crossSectionSets_;}
    std::vector<XSSetType> getCopyOfXSSets() {return crossSectionSets_;}

    void setXSSets(std::vector<XSSetType>& crossSectionSets) {crossSectionSets_ = crossSectionSets;}
    void calcXSSets();

    // Cross section matrix sets

    CrossSectionMatrixSet getXSMatrixSet(XSMatrixKind kind);
    static CrossSectionMatrixSet& getXSMatrixSet(XSMatrixKind kind, std::vector<XSMatrixSetType>& crossSectionMatrixSets);
    std::vector<XSMatrixSetType>& getXSMatrixSets() {return crossSectionMatrixSets_;}
    std::vector<XSMatrixSetType> getCopyOfXSMatrixSets() {return crossSectionMatrixSets_;}

    void setXSMatrixSets(std::vector<XSMatrixSetType>& crossSectionMatrixSets) {crossSectionMatrixSets_ = crossSectionMatrixSets;}
    void calcXSMatrixSets();

    void printDebugData();
    void printXSs(XSKind kind);
    void printMatrixXSs(XSMatrixKind xsKind);

private:

    std::string name_;
    double awr_;
    std::vector<double> temperatures_;
    std::vector<double> lambdas_;
    std::vector<double> dilutions_;
    unsigned energyGroupsNumber_;
    bool isResonant_;
    bool isFissionable_;
    double potXS_;

    std::vector<XSSetType> crossSectionSets_;
    std::vector<XSMatrixSetType> crossSectionMatrixSets_;
};

#endif