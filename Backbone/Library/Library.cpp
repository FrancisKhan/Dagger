#include "Library.h"
#include "Output.h"
#include "inputParser.h"
#include "NuclideBlock.h"
#include "numeric_tools.h"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

std::vector<std::string> Library::readXSFile(std::string &input)
{
	std::vector<std::string> data;

    std::ifstream xsDataFile;
	xsDataFile.open(input);
	if (!xsDataFile) 
	{
		out.print(TraceLevel::CRITICAL, "Unable to open file: {}", input); 
		exit(-1);
	}
	
    std::string line;
	std::string noExtraSpacesline;
    while (std::getline(xsDataFile, line))
    {
        data.push_back(InputParser::removeSpaces(line));
    }

	xsDataFile.close();
	return data;
}


void Library::findNuclideBLocks()
{
    std::string str1 = "->       1      12       0       1";
    m_xsNuclideBlocks = InputParser::findLine(m_xsDataFileLines, str1);

    for(unsigned i = 0; i < m_xsNuclideBlocks.size() - 1; i++)
        m_xsNuclides.push_back(m_xsDataFileLines[m_xsNuclideBlocks[i] + 1]);
}

std::pair<unsigned, unsigned> Library::getXSNuclideBLock(const std::string &nuclide)
{
    std::vector<unsigned> lines;
	std::pair<unsigned, unsigned> blockLines(0, 0);

    auto it = std::find(m_xsNuclides.begin(), m_xsNuclides.end(), nuclide); 
    if (it != m_xsNuclides.end())
    {
        lines = InputParser::findLine(m_xsDataFileLines, nuclide);
    }
    else
    {
        out.print(TraceLevel::CRITICAL, "{} nuclide not found!", nuclide);
	    exit(-1);
    } 

    if (lines.size() == 1)
    {
        for(size_t i = 1; i < m_xsNuclideBlocks.size(); i++)
            if (lines.front() < m_xsNuclideBlocks[i])
            {
				blockLines = std::make_pair(m_xsNuclideBlocks[i - 1], m_xsNuclideBlocks[i]);
                break;
            }
    }
	else
    {
        out.print(TraceLevel::CRITICAL, "Error in reading the {} nuclide data block!", nuclide);
	    exit(-1);
    } 

	return blockLines;
}

std::vector < std::shared_ptr<Nuclide> > Library::getNuclides(std::vector<std::string> &nucVec)
{
    m_xsDataFileLines = readXSFile(m_libraryPath);
    findNuclideBLocks();

    setNumberOfEnergyGroups();

	for(const auto &nuc : nucVec)
	{
		std::pair<unsigned, unsigned> blockLines = getXSNuclideBLock(nuc);
		std::vector<std::string> dataVec = Numerics::slice(m_xsDataFileLines, blockLines.first, blockLines.second);
		NuclideBlock nuclideBlock(dataVec, getNumberOfEnergyGroups());

        std::shared_ptr<Nuclide> nuclide = nuclideBlock.getNuclide();
        m_nuclides.push_back(nuclide);
	}

    return m_nuclides;
}

void Library::setNumberOfEnergyGroups()
{
    std::vector<unsigned> lines = InputParser::findLine(m_xsDataFileLines, "SUBTMP0001", 0, 100);
    std::string line = InputParser::getLine(m_xsDataFileLines, lines[0] + 1);   
    std::vector<std::string> lineVec = InputParser::splitLine(line);
    m_numberOfEnergyGroups = std::stoi(lineVec.end()[-1]);
}

void Library::setXSLibraryPath(const std::string& libraryPath)
{
    if (fs::exists(libraryPath))
	{
		m_libraryPath = libraryPath;
	}
    else
    {
        std::cout << "ERROR: library file not found!" << std::endl;
    }
}

void Library::printLogsOnConsole(const std::string& logLevel)
{
    out.createLogger(Sink::CONSOLE);
    out.setLevel(logLevel);
    out.printStart();
}


void Library::printLogsOnFile(const std::string& logFile, const std::string& logLevel)
{
    out.setOutputPath(logFile);
    out.createLogger(Sink::FILE);
    out.setLevel(logLevel);
    out.printStart();
}

void Library::printLogsOnBoth(const std::string& logFile, const std::string& logLevel)
{
    out.setOutputPath(logFile);
    out.createLogger(Sink::BOTH);
    out.setLevel(logLevel);
    out.printStart();
}

void setLogLevel(const std::string& logLevel)
{
    out.setLevel(logLevel);
}

std::string Library::getLogLevel()
{
    return get_name(out.getLevel());
}

// void Input::printData()
// {
// 	out.print(TraceLevel::CRITICAL, "Input file: {}/{}",  out.getInputPath(), out.getInputName());
// 	out.print(TraceLevel::CRITICAL, "Output file: {} \n", out.getOutputName());
// }