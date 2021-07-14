#include <iostream>

#include "gtest/gtest.h"
#include "network_tools.h"
#include "Library.h"

TEST(DLRTests, DownloadLibrary)
{	
    curl_global_init(CURL_GLOBAL_ALL);
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = "draglibendfb7r0.gz";
    bool result = Network::downloadFile(url, target);
    curl_global_cleanup();
    EXPECT_TRUE(result);
}

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