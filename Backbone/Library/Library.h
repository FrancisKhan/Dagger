#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>

class Library
{
public:
	Library() {}
	std::vector<std::string> readXSFile(std::string &input);
	void findNuclideBLocks();
	std::pair<unsigned, unsigned> getXSNuclideBLock(const std::string &nuclide);
	void getNuclides();
	
private:
	std::vector<std::string> m_xsDataFileLines;
	std::vector<std::string> m_xsNuclides;
	std::vector<unsigned> m_xsNuclideBlocks;
};

#endif