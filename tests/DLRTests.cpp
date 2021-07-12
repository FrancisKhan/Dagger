#include <iostream>

#include "gtest/gtest.h"
#include "Library.h"

TEST(DLRTests, OpenLibrary)
{	
    Library library;
	std::string refInputPath = "/home/why/ALMOST_libs/draglibendfb7r0.txt";
	library.setXSLibraryPath(refInputPath);
    std::string inputPath = library.getXSLibraryPath();

    EXPECT_EQ(inputPath, refInputPath);
}

TEST(DLRTests, GetNuclides)
{	
    Library library;
	std::string refInputPath = "/home/why/ALMOST_libs/draglibendfb7r0.txt";
	library.setXSLibraryPath(refInputPath);
    std::vector<std::string> nucVec = {"Pu239", "La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.getNuclides(nucVec);

    size_t numberOfNuclides = library.getNumberOfNuclidesRead();

    EXPECT_EQ(numberOfNuclides, 2);
}