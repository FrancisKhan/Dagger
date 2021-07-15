#include <iostream>

#include "gtest/gtest.h"
#include "file_tools.h"
#include "network_tools.h"
#include "Library.h"


TEST(DLRTests, DownloadLibrary)
{	
    Library library;
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getCurrentPath() + "/neutron_libraries/draglibendfb7r0.gz";
    bool result = library.downloadLibrary(url, target);
    File::removeFile(target);
    EXPECT_TRUE(result);
}

TEST(DLRTests, OpenLibrary)
{	
    Library library;
    std::string outputPath = File::getCurrentPath() + "/output.txt";
    library.printLogsOnFile(outputPath, "CRITICAL");
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getCurrentPath() + "/neutron_libraries/draglibendfb7r0.gz";
    library.downloadLibrary(url, target);

	library.setXSLibraryPath(target);
    std::string inputPath = library.getXSLibraryPath();
    File::removeFile(target);

    EXPECT_EQ(inputPath, target);
}

TEST(DLRTests, GetNuclides)
{	
    Library library;
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getCurrentPath() + "/neutron_libraries/draglibendfb7r0.gz";
    library.downloadLibrary(url, target);

	library.setXSLibraryPath(target);
    std::vector<std::string> nucVec = {"Pu239", "La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.getNuclides(nucVec);
    size_t numberOfNuclides = library.getNumberOfNuclidesRead();
    File::removeFile(target);

    EXPECT_EQ(numberOfNuclides, 2);
}