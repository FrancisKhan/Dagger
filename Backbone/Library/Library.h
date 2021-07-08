#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>

#include "Nuclide.h"

class Library
{
public:
	Library() {}
	std::vector<std::string> readXSFile(std::string &input);
	void findNuclideBLocks();
	std::pair<unsigned, unsigned> getXSNuclideBLock(const std::string &nuclide);
	unsigned getNumberOfEnergyGroups() {return m_numberOfEnergyGroups;}
	std::vector < std::shared_ptr<Nuclide> > getNuclides(std::vector<std::string> &nucVec);
	void setXSLibraryPath(const std::string& libraryPath);
	std::string getXSLibraryPath() {return m_libraryPath;}
	
private:
	void setNumberOfEnergyGroups();

	std::vector<std::string> m_xsDataFileLines;
	std::vector<std::string> m_xsNuclides;
	std::vector<unsigned> m_xsNuclideBlocks;
	unsigned m_numberOfEnergyGroups;
	std::string m_libraryPath;

	std::vector < std::shared_ptr<Nuclide> > m_nuclides;
};

#endif