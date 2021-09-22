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
	unsigned getNumberOfEnergyGroups() {return numberOfEnergyGroups_;}
	std::vector < std::shared_ptr<Nuclide> > readNuclides(std::vector<std::string> &nucVec);
	std::shared_ptr<Nuclide> getNuclide(const std::string &nucName);
	void setXSLibraryPath(const std::string& libraryPath);
	std::string getXSLibraryPath() {return libraryPath_;}
	size_t getNumberOfNuclidesRead() {return nuclides_.size();} 
	std::vector<std::string> getLibraryNuclides() {return xsNuclides_;}
	size_t getNumberOfLibraryNuclides() {return xsNuclides_.size();}

	void hardCodedPotXSs();

	bool downloadLibrary(const std::string& url, const std::string& targetFolder);
	void printLogsOnConsole(const std::string& logLevel);
	void printLogsOnFile(const std::string& logFile, const std::string& logLevel);
	void printLogsOnBoth(const std::string& logFile, const std::string& logLevel);
	void setLogLevel(const std::string& logLevel);
	std::string getLogLevel();
	
private:
	void setNumberOfEnergyGroups();

	std::vector<std::string> xsDataFileLines_;
	std::vector<std::string> xsNuclides_;
	std::vector<unsigned> xsNuclideBlocks_;
	unsigned numberOfEnergyGroups_;
	std::string libraryPath_;

	std::map<std::string, double> potXSs_;

	std::vector < std::shared_ptr<Nuclide> > nuclides_;
	TraceLevel logLevel_;
};

#endif