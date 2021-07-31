#include "Library.h"
#include "Output.h"
#include "NuclideBlock.h"
#include "numeric_tools.h"
#include "network_tools.h"
#include "file_tools.h"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Library::Library() 
{
    out.createLogger(Sink::EMPTY);
}

std::vector<std::string> Library::readXSLibrary(std::string &input)
{
    std::vector<std::string> result {};

	if(File::getFileExtension(input) == "gz") // reading a zlib archive
    {
        result = File::decompressFile(input);
    }
    else if(File::getFileExtension(input) == "txt") // reading a text file
    {
        result = File::readTextFile(input);
    }
    else
    {

    }

    return result;
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
        out.print(TraceLevel::CRITICAL, "ERROR: {} nuclide not found!", nuclide);
        throw std::runtime_error("ERROR: nuclide not found!");
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
        out.print(TraceLevel::CRITICAL, "ERROR: reading the {} nuclide data block not successful!", nuclide);
        throw std::runtime_error("ERROR: nuclide not found!");
    } 

	return blockLines;
}

std::vector < std::shared_ptr<Nuclide> > Library::readNuclides(std::vector<std::string> &nucVec)
{
    m_xsDataFileLines = readXSLibrary(m_libraryPath);
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

std::shared_ptr<Nuclide> Library::getNuclide(const std::string &nucName)
{
    auto it = std::find_if(m_nuclides.begin(), m_nuclides.end(), 
    [&nucName](const auto& i){return i->getName() == nucName;});

    if(it != m_nuclides.end())
    {
        return *it;
    }
    else
    {
        out.print(TraceLevel::CRITICAL, "ERROR: {} has not being read yet", nucName);
        throw std::runtime_error("ERROR: nuclide not being read yet");
    }
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
        if((File::getFileExtension(libraryPath) == "txt") || (File::getFileExtension(libraryPath) == "gz"))
        {
            m_libraryPath = libraryPath;
        }
        else
        {
            out.print(TraceLevel::CRITICAL, "ERROR: library file has not a txt or gz extension");
            throw std::runtime_error("ERROR: library file has not a txt or gz extension");
        }
    }
    else
    {
        out.print(TraceLevel::CRITICAL, "ERROR: library file not found in: {}", libraryPath);
        throw std::runtime_error("ERROR: library file not found");
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

bool Library::downloadLibrary(const std::string& url, const std::string& targetFolder)
{
    curl_global_init(CURL_GLOBAL_ALL);
    bool result = Network::downloadFile(url, targetFolder);
    curl_global_cleanup();
    return result;
}

// void Input::printData()
// {
// 	out.print(TraceLevel::CRITICAL, "Input file: {}/{}",  out.getInputPath(), out.getInputName());
// 	out.print(TraceLevel::CRITICAL, "Output file: {} \n", out.getOutputName());
// }