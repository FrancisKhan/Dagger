#include "Library.h"
#include "Output.h"
#include "file_tools.h"
#include "Material.h"
#include "Solver.h"

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

	std::vector<std::string> nucVec = {"U235", "C0"};
	std::vector < std::shared_ptr<Nuclide> > libNuclides = library.readNuclides(nucVec);

	std::vector<double> dens = {3.75440E-08, 5.25310E-02}; // barn
	double temp = 300.0; // Kelvin

	Material mat(temp, nucVec, dens, libNuclides);
	std::vector<Material::MacroXSType> crossSections = mat.calculateMacroXSs();
	std::vector<Material::MacroXSMatrixType> crossSectionMatrices = mat.calculateMacroXSMatrices();

	Solver solver(crossSections, crossSectionMatrices);
	Eigen::MatrixXd AMatrix = solver.calcAMatrix();
	Eigen::MatrixXd FMatrix = solver.calcFMatrix();
	solver.sourceIteration(AMatrix, FMatrix);

	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "Main, Timing: " 
			  << std::chrono::duration <double, std::milli> (diff).count() / 1000.0 
			  << std::endl;
}
