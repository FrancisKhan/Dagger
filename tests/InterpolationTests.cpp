#include <iostream>

#include "gtest/gtest.h"
#include "file_tools.h"
#include "network_tools.h"
#include "Library.h"
#include "additionalPrintFuncs.h"

TEST(InterpolationTests, test1)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "Pu239.txt";
	library.setXSLibraryPath(refLibPath);
    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

    CrossSectionSet xsSet = library.getNuclide("Pu239")->getXSSet(XSKind::NTOT0);

    std::vector<double> temps = xsSet.getTemperatures();
    std::cout << "temps: " << std::endl;
    for(auto i : temps)
        std::cout << i << std::endl;

    xsSet.getXS2(300.0);
}

