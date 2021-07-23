#include "Library.h"
#include "Output.h"
#include "file_tools.h"

#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();

	Library library;

	std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getCurrentPath() + "/neutron_libraries/draglibendfb7r0.gz";

	//library.downloadLibrary(url, target);

	library.printLogsOnFile("output.txt", "CRITICAL");
	//library.printLogsOnConsole("CRITICAL");

	std::string inputPath = "/home/why/ALMOST_libs/draglibendfb7r0.txt";
	library.setXSLibraryPath(target);

	std::vector<std::string> nucVec = {"Pu239", "La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

	for(const auto& nuc : nuclides)
		nuc->printDebugData();

	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "Main, Timing: " 
			  << std::chrono::duration <double, std::milli> (diff).count() / 1000.0 
			  << std::endl;
}
