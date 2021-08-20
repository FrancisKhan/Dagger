#ifndef NUCLIDEBLOCK_H
#define NUCLIDEBLOCK_H

#include <vector>
#include <string>
#include <iostream>

#include "additionalPrintFuncs.h"
#include "Nuclide.h"

using namespace PrintFuncs;

class NuclideBlock
{
public:
	NuclideBlock(std::vector<std::string> &dataVec, unsigned numberOfEnergyGroups) : 
	m_xsDataLines(dataVec), m_numberOfEnergyGroups(numberOfEnergyGroups),
	m_nuclide(std::make_shared<Nuclide>()) {}

	std::shared_ptr<Nuclide> getNuclide();
	
private:
	std::pair<unsigned, unsigned> getNumberOfValuesToRead(unsigned line);
	unsigned getNumberOfLinesToRead(unsigned line);
	std::vector<double> readParameters(const std::string &key, unsigned lowerBound = 0, 
	unsigned upperBound = std::numeric_limits<unsigned>::max());
	std::vector< std::pair<unsigned, unsigned> > readTemperatureBlocks();
	std::vector< std::pair<unsigned, unsigned> > readDilutionBlocks(std::pair<unsigned, unsigned> &block);
	std::pair<unsigned, unsigned> readInfDilutionBlock(std::pair<unsigned, unsigned> &block);
	void readName();
	void readAWR();
	std::vector<double> readTemperatures();
	std::vector<double> readLambdas();
	std::vector<double> readDilutions(unsigned firstLine, unsigned lastLine);
	void readGroupConstants();
	std::vector<Nuclide::XSSetType> readXSs();
	std::vector<Nuclide::XSMatrixSetType> readXSMatrices();
	void isNuclideResonant();
	bool isNuclideFissionable() const;
	void setNumberOfEnergyGroups();
	unsigned getNumberOfEnergyGroups() {return m_numberOfEnergyGroups;}
	std::vector<double> populateXS(std::vector<double> &xsVec);
	std::vector<Nuclide::XSSetType> addNu();
	std::vector<Nuclide::XSSetType> addScatteringL1XS();
	void additionalXSs();

	std::tuple< std::vector<double>, std::vector<int32_t>, std::vector<int32_t> > 
	readMatrixComponents(XSMatrixKind xsKind, unsigned lowBound, unsigned upperBound);
	std::pair<std::string, std::string> getMatrixKeys(XSMatrixKind xsKind);

	Eigen::MatrixXd assembleMatrixXS(XSMatrixKind xsKind, unsigned lowBound, unsigned upperBound);

	std::vector<std::string> m_xsDataLines;
	unsigned m_numberOfEnergyGroups;
	std::shared_ptr<Nuclide> m_nuclide;
};

#endif