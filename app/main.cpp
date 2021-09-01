#include "Library.h"
#include "Output.h"
#include "file_tools.h"
#include "MacroCrossSection.h"

#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();

	Library library;

	std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getCurrentPath() + "/draglibendfb7r0.gz";

	library.downloadLibrary(url, target);
	library.setXSLibraryPath(target);
	library.printLogsOnFile("output.txt", "CRITICAL");

	std::vector<std::string> nucVec = {"Pu239", "C0_GR"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

	std::vector<double> dens = {0.0001, 0.001}; // barn
	double temp = 300.0; // Kelvin

	MacroCrossSection macroXS(temp, nucVec, dens);

	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "Main, Timing: " 
			  << std::chrono::duration <double, std::milli> (diff).count() / 1000.0 
			  << std::endl;
}
