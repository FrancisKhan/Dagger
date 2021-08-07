#include <iostream>

#include "gtest/gtest.h"
#include "file_tools.h"
#include "Library.h"
#include "Interpolation.h"


TEST(InterpolationTests, test1)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "Pu239.txt";
	library.setXSLibraryPath(refLibPath);
    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

    CrossSectionSet xsSet = library.getNuclide("Pu239")->getXSSet(XSKind::NTOT0);

    std::cout << std::setprecision(10) << std::endl;
    std::cout << "xsSet.getXS3(): " << xsSet.getXS3(300.0, LinLin(), 1222.5, LinLin()) << std::endl;
}

TEST(InterpolationTests, test2)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "Pu239.txt";
	library.setXSLibraryPath(refLibPath);
    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

    CrossSectionSet xsSet = library.getNuclide("Pu239")->getXSSet(XSKind::NTOT0);

    std::cout << std::setprecision(10) << std::endl;
    std::vector<double> vec = xsSet.getXS4(300.0, LinLin(), 1222.5, LinLin()).getValues();

    std::cout << std::scientific << std::endl;

    for(auto i : vec)
        std::cout << i << std::endl;
}

