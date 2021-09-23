#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <vector>
#include <string>
#include <limits>

namespace InputParser
{
	std::string removeUnwantedCharacters(std::string &input);
	std::string removeLeadingSpaces(std::string &input);
    std::string removeTrailingSpaces(std::string &input);
	std::string removeLeftArrow(std::string &input);

	std::vector<unsigned> findLine(const std::vector<std::string> &dataVec, const std::string &key, unsigned lowerBound = 0, 
	unsigned upperBound = std::numeric_limits<unsigned>::max());

	std::string findKeyword(std::string toSearch, unsigned lowLimit = 0, 
	unsigned topLimit = std::numeric_limits<unsigned>::max());
    std::string getLine(std::vector<std::string> &dataVec, unsigned i);
	std::vector<std::string> splitLine(std::string line);
	std::vector<double> fromStringVecToDoubleVec(std::vector<std::string> &strVec);
	
	bool isKeywordPresent(std::vector<std::string> &dataVec, const std::string &key, unsigned lowerBound = 0, 
	unsigned upperBound = std::numeric_limits<unsigned>::max());

	bool isKeywordPresentInString(const std::string &key, const std::string& line);
}

#endif