#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <map>

#include "Nuclide.h"

class Library
{
public:
	Library();
	std::vector<std::string> readXSLibrary(std::string &input);
	void findNuclideBLocks();
	std::pair<unsigned, unsigned> getXSNuclideBLock(const std::string &nuclide);
	unsigned getNumberOfEnergyGroups() {return m_numberOfEnergyGroups;}
	std::vector < std::shared_ptr<Nuclide> > readNuclides(std::vector<std::string> &nucVec);
	std::shared_ptr<Nuclide> getNuclide(const std::string &nucName);
	void setXSLibraryPath(const std::string& libraryPath);
	std::string getXSLibraryPath() {return m_libraryPath;}
	size_t getNumberOfNuclidesRead() {return m_nuclides.size();} 
	std::vector<std::string> getLibraryNuclides() {return m_xsNuclides;}
	size_t getNumberOfLibraryNuclides() {return m_xsNuclides.size();}

	void hardCodedPotXSs();

	bool downloadLibrary(const std::string& url, const std::string& targetFolder);
	void printLogsOnConsole(const std::string& logLevel);
	void printLogsOnFile(const std::string& logFile, const std::string& logLevel);
	void printLogsOnBoth(const std::string& logFile, const std::string& logLevel);
	void setLogLevel(const std::string& logLevel);
	std::string getLogLevel();
	
private:
	void setNumberOfEnergyGroups();

	std::vector<std::string> m_xsDataFileLines;
	std::vector<std::string> m_xsNuclides;
	std::vector<unsigned> m_xsNuclideBlocks;
	unsigned m_numberOfEnergyGroups;
	std::string m_libraryPath;

	std::map<std::string, double> m_potXSs;

	std::vector < std::shared_ptr<Nuclide> > m_nuclides;
	TraceLevel m_logLevel;
};

#endif