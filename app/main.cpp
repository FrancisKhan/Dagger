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

	double temp = 300.0; // Kelvin
	// std::vector<std::string> nucVec = {"U235" , "U238", "C0_GR"};
	// std::vector<double> dens = {3.75440E-06, 8.49430E-05, 5.25310E-02}; // barn

	// std::vector<std::string> nucVec = {"U235" , "U238", "O16", "Si28", 
	// 								   "Si29", "Si30", "He4", "C0_GR"};

	// std::vector<double> dens = {6.2728E-05,  // U235
	// 							3.3767E-04,  // U238
	// 							6.0058E-04,  // O16
	// 							1.1323E-03,  // Si28
	// 							5.7520E-05,  // Si29
	// 							3.7962E-05,  // Si30
	// 							3.9705E-07,  // He4
	// 							8.2188E-02}; // Graphite

	// std::vector<std::string> nucVec = {"U235", "U238", "C0_GR"};
	// std::vector<double> dens = {6.2728E-05,  // U235
	// 							3.3767E-04,  // U238
	// 							8.2188E-02}; // Graphite

	std::vector<std::string> nucVec = {"U235", "C0"};
	std::vector<double> dens = {6.2728E-05,  // U235
								8.2188E-02}; // Graphite

	// std::vector<std::string> nucVec = {"U235" , "U238", "C0_GR"};
	// std::vector<double> dens = {3.75440E-06, 1.96955E-04, 5.25310E-02}; // barn

	std::vector < std::shared_ptr<Nuclide> > libNuclides = library.readNuclides(nucVec);

	Material mat(temp, nucVec, dens, libNuclides);

	std::vector<Material::MacroXSType> crossSections = mat.calculateMacroXSs();
	std::vector<Material::MacroXSMatrixType> crossSectionMatrices = mat.calculateMacroXSMatrices();
	std::map<XSKind, Material::XSMapType> otherGroupConstants = mat.calculateOtherGroupConstants();

	Solver solver(crossSections, crossSectionMatrices, otherGroupConstants);

	Eigen::MatrixXd AMatrix = solver.calcAMatrix();
	Eigen::MatrixXd FMatrix = solver.calcFMatrix();
	solver.sourceIteration(AMatrix, FMatrix);

	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "\nMain, Timing: " 
			  << std::chrono::duration <double, std::milli> (diff).count() / 1000.0 
			  << std::endl;
}
