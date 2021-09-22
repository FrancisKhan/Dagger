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
    xsNuclideBlocks_ = InputParser::findLine(xsDataFileLines_, str1);

    for(unsigned i = 0; i < xsNuclideBlocks_.size() - 1; i++)
        xsNuclides_.push_back(xsDataFileLines_[xsNuclideBlocks_[i] + 1]);

    std::sort(xsNuclides_.begin(), xsNuclides_.end());
    xsNuclides_.erase(std::unique(xsNuclides_.begin(), xsNuclides_.end()), xsNuclides_.end());
}

std::pair<unsigned, unsigned> Library::getXSNuclideBLock(const std::string &nuclide)
{
    std::vector<unsigned> lines;
	std::pair<unsigned, unsigned> blockLines(0, 0);

    auto it = std::find(xsNuclides_.begin(), xsNuclides_.end(), nuclide); 
    if (it != xsNuclides_.end())
    {
        lines = InputParser::findLine(xsDataFileLines_, nuclide);
    }
    else
    {
        out.print(TraceLevel::CRITICAL, "ERROR: {} nuclide not found!", nuclide);
        throw std::runtime_error("ERROR: nuclide not found!");
    } 

    if (lines.size() == 1)
    {
        for(size_t i = 1; i < xsNuclideBlocks_.size(); i++)
            if (lines.front() < xsNuclideBlocks_[i])
            {
				blockLines = std::make_pair(xsNuclideBlocks_[i - 1], xsNuclideBlocks_[i]);
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
    xsDataFileLines_ = readXSLibrary(libraryPath_);
    findNuclideBLocks();

    setNumberOfEnergyGroups();
    hardCodedPotXSs();

	for(const auto &nuc : nucVec)
	{
		std::pair<unsigned, unsigned> blockLines = getXSNuclideBLock(nuc);
		std::vector<std::string> dataVec = Numerics::slice(xsDataFileLines_, blockLines.first, blockLines.second);
		NuclideBlock nuclideBlock(dataVec, getNumberOfEnergyGroups());

        std::shared_ptr<Nuclide> nuclide = nuclideBlock.getNuclide();
        nuclide->setPotXS(potXSs_.find(nuclide->getName())->second);
        nuclides_.push_back(nuclide);
	}

    return nuclides_;
}

std::shared_ptr<Nuclide> Library::getNuclide(const std::string &nucName)
{
    auto it = std::find_if(nuclides_.begin(), nuclides_.end(), 
    [&nucName](const auto& i){return i->getName() == nucName;});

    if(it != nuclides_.end())
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
    std::vector<unsigned> lines = InputParser::findLine(xsDataFileLines_, "NTOT0", 0, 100);
    std::string line = InputParser::getLine(xsDataFileLines_, lines[0] - 1);   
    std::vector<std::string> lineVec = InputParser::splitLine(line);
    numberOfEnergyGroups_ = std::stoi(lineVec.end()[-1]);
}

void Library::setXSLibraryPath(const std::string& libraryPath)
{
    if (fs::exists(libraryPath))
    {
        if((File::getFileExtension(libraryPath) == "txt") || (File::getFileExtension(libraryPath) == "gz"))
        {
            libraryPath_ = libraryPath;
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

void Library::hardCodedPotXSs()
{
    potXSs_.insert(std::pair<std::string, double>("Ag107", 5.4739));
	potXSs_.insert(std::pair<std::string, double>("Ag109", 5.4739));
	potXSs_.insert(std::pair<std::string, double>("Ag111", 5.4739));
	potXSs_.insert(std::pair<std::string, double>("Al27", 2.3480));
	potXSs_.insert(std::pair<std::string, double>("Am241", 11.0329));
	potXSs_.insert(std::pair<std::string, double>("Am242", 11.1509));
	potXSs_.insert(std::pair<std::string, double>("Am242m", -1.0));
	potXSs_.insert(std::pair<std::string, double>("Am243", 11.8237));
	potXSs_.insert(std::pair<std::string, double>("As75", 5.6410));
	potXSs_.insert(std::pair<std::string, double>("B10", 2.1424));
	potXSs_.insert(std::pair<std::string, double>("B11", 4.8400));
	potXSs_.insert(std::pair<std::string, double>("Ba134", 3.5299));
	potXSs_.insert(std::pair<std::string, double>("Ba135", 3.5221));
	potXSs_.insert(std::pair<std::string, double>("Ba136", 3.5299));
	potXSs_.insert(std::pair<std::string, double>("Ba137", 3.5299));
	potXSs_.insert(std::pair<std::string, double>("Ba138", 3.5299));
	potXSs_.insert(std::pair<std::string, double>("Ba140", 4.8821));
	potXSs_.insert(std::pair<std::string, double>("Be7", 19.0643));
	potXSs_.insert(std::pair<std::string, double>("Be9", 6.1470));
	potXSs_.insert(std::pair<std::string, double>("Bi209", 11.7730));
	potXSs_.insert(std::pair<std::string, double>("Bk249", 11.0983));
	potXSs_.insert(std::pair<std::string, double>("Br79", 5.5934));
	potXSs_.insert(std::pair<std::string, double>("Br81", 5.9828));
	potXSs_.insert(std::pair<std::string, double>("C0", 4.7392));
	potXSs_.insert(std::pair<std::string, double>("C0_GR", 4.7392));
	potXSs_.insert(std::pair<std::string, double>("Ca40", 1.6286));
	potXSs_.insert(std::pair<std::string, double>("Ca42", 1.6286));
	potXSs_.insert(std::pair<std::string, double>("Ca43", 1.6286));
	potXSs_.insert(std::pair<std::string, double>("Ca44", 1.6286));
	potXSs_.insert(std::pair<std::string, double>("Ca46", 1.1529));
	potXSs_.insert(std::pair<std::string, double>("Ca48", 1.6286));
	potXSs_.insert(std::pair<std::string, double>("Cd106", 4.4183));
	potXSs_.insert(std::pair<std::string, double>("Cd108", 4.2091));
	potXSs_.insert(std::pair<std::string, double>("Cd110", 4.2441));
	potXSs_.insert(std::pair<std::string, double>("Cd111", 4.3383));
	potXSs_.insert(std::pair<std::string, double>("Cd112", 4.3152));
	potXSs_.insert(std::pair<std::string, double>("Cd113", 4.9876));
	potXSs_.insert(std::pair<std::string, double>("Cd114", 5.0002));
	potXSs_.insert(std::pair<std::string, double>("Cd115m", -1.0));
	potXSs_.insert(std::pair<std::string, double>("Cd116", 4.6759));
	potXSs_.insert(std::pair<std::string, double>("Ce140", 3.9408));
	potXSs_.insert(std::pair<std::string, double>("Ce141", 3.6348));
	potXSs_.insert(std::pair<std::string, double>("Ce142", 4.0828));
	potXSs_.insert(std::pair<std::string, double>("Ce143", 8.4496));
	potXSs_.insert(std::pair<std::string, double>("Ce144", 2.9930));
	potXSs_.insert(std::pair<std::string, double>("Cf249", 11.1510));
	potXSs_.insert(std::pair<std::string, double>("Cf250", 9.8800));
	potXSs_.insert(std::pair<std::string, double>("Cf251", 9.8800));
	potXSs_.insert(std::pair<std::string, double>("Cf252", 9.8000));
	potXSs_.insert(std::pair<std::string, double>("Cf253", 9.7600));
	potXSs_.insert(std::pair<std::string, double>("Cl35", 2.9222));
	potXSs_.insert(std::pair<std::string, double>("Cl37", 2.9995));
	potXSs_.insert(std::pair<std::string, double>("Cm241", 10.1788));
	potXSs_.insert(std::pair<std::string, double>("Cm242", 10.2000));
	potXSs_.insert(std::pair<std::string, double>("Cm243", 11.2832));
	potXSs_.insert(std::pair<std::string, double>("Cm244", 14.0427));
	potXSs_.insert(std::pair<std::string, double>("Cm245", 11.3900));
	potXSs_.insert(std::pair<std::string, double>("Cm246", 10.2758));
	potXSs_.insert(std::pair<std::string, double>("Cm247", 9.9444));
	potXSs_.insert(std::pair<std::string, double>("Cm248", 10.3971));
	potXSs_.insert(std::pair<std::string, double>("Co59", 5.5940));
	potXSs_.insert(std::pair<std::string, double>("Cr50", 3.6313));
	potXSs_.insert(std::pair<std::string, double>("Cr52", 3.7254));
	potXSs_.insert(std::pair<std::string, double>("Cr53", 3.7722));
	potXSs_.insert(std::pair<std::string, double>("Cr54", 3.8186));
	potXSs_.insert(std::pair<std::string, double>("Cs133", 3.5299));
	potXSs_.insert(std::pair<std::string, double>("Cs134", 3.5419));
	potXSs_.insert(std::pair<std::string, double>("Cs135", 4.8834));
	potXSs_.insert(std::pair<std::string, double>("Cs136", 3.4011));
	potXSs_.insert(std::pair<std::string, double>("Cs137", 3.2701));
	potXSs_.insert(std::pair<std::string, double>("Cu63", 5.6410));
	potXSs_.insert(std::pair<std::string, double>("Cu65", 5.6410));
	potXSs_.insert(std::pair<std::string, double>("DEPL-CHAIN", -1.0));
	potXSs_.insert(std::pair<std::string, double>("Dy160", 6.9861));
	potXSs_.insert(std::pair<std::string, double>("Dy161", 7.0121));
	potXSs_.insert(std::pair<std::string, double>("Dy162", 4.5681));
	potXSs_.insert(std::pair<std::string, double>("Dy163", 7.0639));
	potXSs_.insert(std::pair<std::string, double>("Dy164", 7.0897));
	potXSs_.insert(std::pair<std::string, double>("Er166", 8.2448));
	potXSs_.insert(std::pair<std::string, double>("Er167", 7.9704));
	potXSs_.insert(std::pair<std::string, double>("Eu151", 6.6944));
	potXSs_.insert(std::pair<std::string, double>("Eu152", 6.3735));
	potXSs_.insert(std::pair<std::string, double>("Eu153", 8.4496));
	potXSs_.insert(std::pair<std::string, double>("Eu154", 6.6115));
	potXSs_.insert(std::pair<std::string, double>("Eu155", 6.9739));
	potXSs_.insert(std::pair<std::string, double>("Eu156", 6.2886));
	potXSs_.insert(std::pair<std::string, double>("Eu157", 7.5555));
	potXSs_.insert(std::pair<std::string, double>("F19", 3.6103));
	potXSs_.insert(std::pair<std::string, double>("Fe54", 3.7737));
	potXSs_.insert(std::pair<std::string, double>("Fe56", 3.7152));
	potXSs_.insert(std::pair<std::string, double>("Fe57", 4.3744));
	potXSs_.insert(std::pair<std::string, double>("Fe58", 6.5144));
	potXSs_.insert(std::pair<std::string, double>("Gd152", 8.0425));
	potXSs_.insert(std::pair<std::string, double>("Gd154", 6.6723));
	potXSs_.insert(std::pair<std::string, double>("Gd155", 6.3376));
	potXSs_.insert(std::pair<std::string, double>("Gd156", 7.3792));
	potXSs_.insert(std::pair<std::string, double>("Gd157", 6.6063));
	potXSs_.insert(std::pair<std::string, double>("Gd158", 7.6454));
	potXSs_.insert(std::pair<std::string, double>("Gd160", 7.0241));
	potXSs_.insert(std::pair<std::string, double>("Ge72", 5.3093));
	potXSs_.insert(std::pair<std::string, double>("Ge73", 5.3093));
	potXSs_.insert(std::pair<std::string, double>("Ge74", 5.2608));
	potXSs_.insert(std::pair<std::string, double>("Ge76", 5.3093));
	potXSs_.insert(std::pair<std::string, double>("H1", 20.4780));
	potXSs_.insert(std::pair<std::string, double>("H1_CH2", 20.4780));
	potXSs_.insert(std::pair<std::string, double>("H1_H2O", 20.4780));
	potXSs_.insert(std::pair<std::string, double>("H1_ZRH", 20.4780));
	potXSs_.insert(std::pair<std::string, double>("H2", 3.3949));
	potXSs_.insert(std::pair<std::string, double>("H2_D2O", 3.3949));
	potXSs_.insert(std::pair<std::string, double>("H3", 1.6649));
	potXSs_.insert(std::pair<std::string, double>("He3", 3.3100));
	potXSs_.insert(std::pair<std::string, double>("He4", 0.7592));
	potXSs_.insert(std::pair<std::string, double>("Hf174", 7.4506));
	potXSs_.insert(std::pair<std::string, double>("Hf176", 7.2583));
	potXSs_.insert(std::pair<std::string, double>("Hf177", 8.0425));
	potXSs_.insert(std::pair<std::string, double>("Hf178", 7.5867));
	potXSs_.insert(std::pair<std::string, double>("Hf179", 7.7043));
	potXSs_.insert(std::pair<std::string, double>("Hf180", 8.0425));
	potXSs_.insert(std::pair<std::string, double>("Ho165", 7.4506));
	potXSs_.insert(std::pair<std::string, double>("I127", 4.5239));
	potXSs_.insert(std::pair<std::string, double>("I129", 5.8221));
	potXSs_.insert(std::pair<std::string, double>("I130", 3.3979));
	potXSs_.insert(std::pair<std::string, double>("I131", 3.6623));
	potXSs_.insert(std::pair<std::string, double>("I135", 4.8118));
	potXSs_.insert(std::pair<std::string, double>("In113", 4.3747));
	potXSs_.insert(std::pair<std::string, double>("In115", 5.0439));
	potXSs_.insert(std::pair<std::string, double>("K39", 0.4072));
	potXSs_.insert(std::pair<std::string, double>("K40", 2.3186));
	potXSs_.insert(std::pair<std::string, double>("K41", 0.5027));
	potXSs_.insert(std::pair<std::string, double>("Kr80", 5.9278));
	potXSs_.insert(std::pair<std::string, double>("Kr82", 6.8813));
	potXSs_.insert(std::pair<std::string, double>("Kr83", 6.2126));
	potXSs_.insert(std::pair<std::string, double>("Kr84", 5.9828));
	potXSs_.insert(std::pair<std::string, double>("Kr85", 5.4935));
	potXSs_.insert(std::pair<std::string, double>("Kr86", 6.3347));
	potXSs_.insert(std::pair<std::string, double>("La138", 3.6333));
	potXSs_.insert(std::pair<std::string, double>("La139", 3.0172));
	potXSs_.insert(std::pair<std::string, double>("La140", 3.1416));
	potXSs_.insert(std::pair<std::string, double>("Li6", 0.6716));
	potXSs_.insert(std::pair<std::string, double>("Li7", 0.9700));
	potXSs_.insert(std::pair<std::string, double>("Mg24", 3.6644));
	potXSs_.insert(std::pair<std::string, double>("Mg25", 2.0106));
	potXSs_.insert(std::pair<std::string, double>("Mg26", 2.3235));
	potXSs_.insert(std::pair<std::string, double>("Mn55", 3.3329));
	potXSs_.insert(std::pair<std::string, double>("Mo100", 5.9828));
	potXSs_.insert(std::pair<std::string, double>("Mo92", 6.1575));
	potXSs_.insert(std::pair<std::string, double>("Mo94", 5.9828));
	potXSs_.insert(std::pair<std::string, double>("Mo95", 6.1575));
	potXSs_.insert(std::pair<std::string, double>("Mo96", 6.1575));
	potXSs_.insert(std::pair<std::string, double>("Mo97", 5.9108));
	potXSs_.insert(std::pair<std::string, double>("Mo99", 5.6385));
	potXSs_.insert(std::pair<std::string, double>("N14", 9.8727));
	potXSs_.insert(std::pair<std::string, double>("N15", 4.4175));
	potXSs_.insert(std::pair<std::string, double>("Na23", 3.6779));
	potXSs_.insert(std::pair<std::string, double>("Nb94", 5.7634));
	potXSs_.insert(std::pair<std::string, double>("Nb95", 5.6410));
	potXSs_.insert(std::pair<std::string, double>("Nd142", 3.9408));
	potXSs_.insert(std::pair<std::string, double>("Nd143", 3.9408));
	potXSs_.insert(std::pair<std::string, double>("Nd144", 5.1472));
	potXSs_.insert(std::pair<std::string, double>("Nd145", 4.4902));
	potXSs_.insert(std::pair<std::string, double>("Nd146", 6.5144));
	potXSs_.insert(std::pair<std::string, double>("Nd147", 7.9569));
	potXSs_.insert(std::pair<std::string, double>("Nd148", 6.1575));
	potXSs_.insert(std::pair<std::string, double>("Nd150", 6.1575));
	potXSs_.insert(std::pair<std::string, double>("Ni58", 5.1472));
	potXSs_.insert(std::pair<std::string, double>("Ni60", 4.5239));
	potXSs_.insert(std::pair<std::string, double>("Ni61", 5.3093));
	potXSs_.insert(std::pair<std::string, double>("Ni62", 4.8305));
	potXSs_.insert(std::pair<std::string, double>("Ni64", 7.1631));
	potXSs_.insert(std::pair<std::string, double>("Np236", 12.1427));
	potXSs_.insert(std::pair<std::string, double>("Np237", 13.2169));
	potXSs_.insert(std::pair<std::string, double>("Np238", 12.0687));
	potXSs_.insert(std::pair<std::string, double>("Np239", 10.4979));
	potXSs_.insert(std::pair<std::string, double>("O16", 3.8883));
	potXSs_.insert(std::pair<std::string, double>("O17", 4.1982));
	potXSs_.insert(std::pair<std::string, double>("P31", 4.0972));
	potXSs_.insert(std::pair<std::string, double>("Pa231", 12.3367));
	potXSs_.insert(std::pair<std::string, double>("Pa233", 12.6770));
	potXSs_.insert(std::pair<std::string, double>("Pb204", 9.0792));
	potXSs_.insert(std::pair<std::string, double>("Pb206", 11.3412));
	potXSs_.insert(std::pair<std::string, double>("Pb207", 11.3412));
	potXSs_.insert(std::pair<std::string, double>("Pb208", 11.7993));
	potXSs_.insert(std::pair<std::string, double>("Pd104", 5.4464));
	potXSs_.insert(std::pair<std::string, double>("Pd105", 5.4739));
	potXSs_.insert(std::pair<std::string, double>("Pd106", 5.3093));
	potXSs_.insert(std::pair<std::string, double>("Pd107", 5.0897));
	potXSs_.insert(std::pair<std::string, double>("Pd108", 5.9828));
	potXSs_.insert(std::pair<std::string, double>("Pd110", 5.6410));
	potXSs_.insert(std::pair<std::string, double>("Pm147", 4.0979));
	potXSs_.insert(std::pair<std::string, double>("Pm148", 2.0257));
	potXSs_.insert(std::pair<std::string, double>("Pm148m", -1.0));
	potXSs_.insert(std::pair<std::string, double>("Pm149", 1.9803));
	potXSs_.insert(std::pair<std::string, double>("Pm151", 6.6966));
	potXSs_.insert(std::pair<std::string, double>("Pr141", 3.0172));
	potXSs_.insert(std::pair<std::string, double>("Pr142", 3.9408));
	potXSs_.insert(std::pair<std::string, double>("Pr143", 2.8773));
	potXSs_.insert(std::pair<std::string, double>("Pu236", 11.5824));
	potXSs_.insert(std::pair<std::string, double>("Pu237", 10.5209));
	potXSs_.insert(std::pair<std::string, double>("Pu238", 10.8897));
	potXSs_.insert(std::pair<std::string, double>("Pu239", 11.1471));
	potXSs_.insert(std::pair<std::string, double>("Pu240", 9.9091));
	potXSs_.insert(std::pair<std::string, double>("Pu241", 11.2156));
	potXSs_.insert(std::pair<std::string, double>("Pu242", 10.6961));
	potXSs_.insert(std::pair<std::string, double>("Pu243", 10.2000));
	potXSs_.insert(std::pair<std::string, double>("Pu244", 10.1000));
	potXSs_.insert(std::pair<std::string, double>("Rb85", 6.5080));
	potXSs_.insert(std::pair<std::string, double>("Rb87", 6.3347));
	potXSs_.insert(std::pair<std::string, double>("Rh103", 5.3342));
	potXSs_.insert(std::pair<std::string, double>("Rh105", 4.8413));
	potXSs_.insert(std::pair<std::string, double>("Ru100", 4.9876));
	potXSs_.insert(std::pair<std::string, double>("Ru101", 5.3510));
	potXSs_.insert(std::pair<std::string, double>("Ru102", 4.9876));
	potXSs_.insert(std::pair<std::string, double>("Ru103", 4.7589));
	potXSs_.insert(std::pair<std::string, double>("Ru104", 4.6759));
	potXSs_.insert(std::pair<std::string, double>("Ru105", 5.4758));
	potXSs_.insert(std::pair<std::string, double>("Ru106", 3.3415));
	potXSs_.insert(std::pair<std::string, double>("Ru99", 4.7304));
	potXSs_.insert(std::pair<std::string, double>("S32", 1.9310));
	potXSs_.insert(std::pair<std::string, double>("S33", 1.8627));
	potXSs_.insert(std::pair<std::string, double>("S34", 1.6286));
	potXSs_.insert(std::pair<std::string, double>("S36", 2.1613));
	potXSs_.insert(std::pair<std::string, double>("Sb121", 4.9381));
	potXSs_.insert(std::pair<std::string, double>("Sb123", 4.3701));
	potXSs_.insert(std::pair<std::string, double>("Sb124", 4.0828));
	potXSs_.insert(std::pair<std::string, double>("Sb125", 4.3855));
	potXSs_.insert(std::pair<std::string, double>("Sb126", 4.3744));
	potXSs_.insert(std::pair<std::string, double>("Se76", 7.0681));
	potXSs_.insert(std::pair<std::string, double>("Se77", 7.1008));
	potXSs_.insert(std::pair<std::string, double>("Se78", 8.6570));
	potXSs_.insert(std::pair<std::string, double>("Se79", 7.1679));
	potXSs_.insert(std::pair<std::string, double>("Se80", 7.0686));
	potXSs_.insert(std::pair<std::string, double>("Se82", 5.6410));
	potXSs_.insert(std::pair<std::string, double>("Si28", 2.1501));
	potXSs_.insert(std::pair<std::string, double>("Si29", 2.4328));
	potXSs_.insert(std::pair<std::string, double>("Si30", 2.2167));
	potXSs_.insert(std::pair<std::string, double>("Sm147", 8.6570));
	potXSs_.insert(std::pair<std::string, double>("Sm148", 7.8690));
	potXSs_.insert(std::pair<std::string, double>("Sm149", 8.6570));
	potXSs_.insert(std::pair<std::string, double>("Sm150", 7.6673));
	potXSs_.insert(std::pair<std::string, double>("Sm151", 8.6570));
	potXSs_.insert(std::pair<std::string, double>("Sm152", 8.5265));
	potXSs_.insert(std::pair<std::string, double>("Sm153", 7.6454));
	potXSs_.insert(std::pair<std::string, double>("Sm154", 7.9246));
	potXSs_.insert(std::pair<std::string, double>("Sn112", 4.7206));
	potXSs_.insert(std::pair<std::string, double>("Sn114", 4.8805));
	potXSs_.insert(std::pair<std::string, double>("Sn115", 4.7870));
	potXSs_.insert(std::pair<std::string, double>("Sn116", 4.8305));
	potXSs_.insert(std::pair<std::string, double>("Sn117", 4.6605));
	potXSs_.insert(std::pair<std::string, double>("Sn118", 4.4658));
	potXSs_.insert(std::pair<std::string, double>("Sn119", 4.4408));
	potXSs_.insert(std::pair<std::string, double>("Sn120", 4.8305));
	potXSs_.insert(std::pair<std::string, double>("Sn122", 4.5390));
	potXSs_.insert(std::pair<std::string, double>("Sn123", 3.8681));
	potXSs_.insert(std::pair<std::string, double>("Sn124", 4.5239));
	potXSs_.insert(std::pair<std::string, double>("Sn125", 4.5239));
	potXSs_.insert(std::pair<std::string, double>("Sn126", 3.9161));
	potXSs_.insert(std::pair<std::string, double>("Sr86", 4.8749));
	potXSs_.insert(std::pair<std::string, double>("Sr87", 6.3526));
	potXSs_.insert(std::pair<std::string, double>("Sr88", 6.3347));
	potXSs_.insert(std::pair<std::string, double>("Sr89", 6.2398));
	potXSs_.insert(std::pair<std::string, double>("Sr90", 5.8037));
	potXSs_.insert(std::pair<std::string, double>("Tb159", 7.0506));
	potXSs_.insert(std::pair<std::string, double>("Tb160", 6.6966));
	potXSs_.insert(std::pair<std::string, double>("Tc99", 6.4675));
	potXSs_.insert(std::pair<std::string, double>("Te122", 3.8013));
	potXSs_.insert(std::pair<std::string, double>("Te123", 4.2642));
	potXSs_.insert(std::pair<std::string, double>("Te124", 4.2273));
	potXSs_.insert(std::pair<std::string, double>("Te125", 3.9456));
	potXSs_.insert(std::pair<std::string, double>("Te126", 4.0828));
	potXSs_.insert(std::pair<std::string, double>("Te127m", -1.0));
	potXSs_.insert(std::pair<std::string, double>("Te128", 3.8013));
	potXSs_.insert(std::pair<std::string, double>("Te129m", -1.0));
	potXSs_.insert(std::pair<std::string, double>("Te130", 3.6644));
	potXSs_.insert(std::pair<std::string, double>("Te132", 3.8013));
	potXSs_.insert(std::pair<std::string, double>("Th230", 8.7040));
	potXSs_.insert(std::pair<std::string, double>("Th232", 11.8194));
	potXSs_.insert(std::pair<std::string, double>("Ti46", 2.5447));
	potXSs_.insert(std::pair<std::string, double>("Ti47", 2.5447));
	potXSs_.insert(std::pair<std::string, double>("Ti48", 2.2167));
	potXSs_.insert(std::pair<std::string, double>("Ti49", 2.5447));
	potXSs_.insert(std::pair<std::string, double>("Ti50", 2.5447));
	potXSs_.insert(std::pair<std::string, double>("U232", 12.0687));
	potXSs_.insert(std::pair<std::string, double>("U233", 11.7185));
	potXSs_.insert(std::pair<std::string, double>("U234", 10.0210));
	potXSs_.insert(std::pair<std::string, double>("U235", 11.6137));
	potXSs_.insert(std::pair<std::string, double>("U236", 10.9954));
	potXSs_.insert(std::pair<std::string, double>("U237", 10.5000));
	potXSs_.insert(std::pair<std::string, double>("U238", 11.2934));
	potXSs_.insert(std::pair<std::string, double>("V0", 4.8000));
	potXSs_.insert(std::pair<std::string, double>("W182", 8.0451));
	potXSs_.insert(std::pair<std::string, double>("W183", 8.1587));
	potXSs_.insert(std::pair<std::string, double>("W184", 8.0790));
	potXSs_.insert(std::pair<std::string, double>("W186", 8.0669));
	potXSs_.insert(std::pair<std::string, double>("Xe128", 5.7972));
	potXSs_.insert(std::pair<std::string, double>("Xe129", 3.1946));
	potXSs_.insert(std::pair<std::string, double>("Xe130", 6.2075));
	potXSs_.insert(std::pair<std::string, double>("Xe131", 3.6644));
	potXSs_.insert(std::pair<std::string, double>("Xe132", 3.6634));
	potXSs_.insert(std::pair<std::string, double>("Xe133", 3.5739));
	potXSs_.insert(std::pair<std::string, double>("Xe134", 4.2273));
	potXSs_.insert(std::pair<std::string, double>("Xe135", 3.5491));
	potXSs_.insert(std::pair<std::string, double>("Xe136", 6.3754));
	potXSs_.insert(std::pair<std::string, double>("Y89", 5.7086));
	potXSs_.insert(std::pair<std::string, double>("Y90", 6.1575));
	potXSs_.insert(std::pair<std::string, double>("Y91", 5.7208));
	potXSs_.insert(std::pair<std::string, double>("Zn0", 4.5840));
	potXSs_.insert(std::pair<std::string, double>("Zr90", 6.5144));
	potXSs_.insert(std::pair<std::string, double>("Zr90_ZRH", 6.5144));
	potXSs_.insert(std::pair<std::string, double>("Zr91", 6.5144));
	potXSs_.insert(std::pair<std::string, double>("Zr92", 6.5144));
	potXSs_.insert(std::pair<std::string, double>("Zr93", 6.4825));
	potXSs_.insert(std::pair<std::string, double>("Zr94", 6.5144));
	potXSs_.insert(std::pair<std::string, double>("Zr95", 5.7035));
	potXSs_.insert(std::pair<std::string, double>("Zr96", 5.8107));
}

// void Input::printData()
// {
// 	out.print(TraceLevel::CRITICAL, "Input file: {}/{}",  out.getInputPath(), out.getInputName());
// 	out.print(TraceLevel::CRITICAL, "Output file: {} \n", out.getOutputName());
// }