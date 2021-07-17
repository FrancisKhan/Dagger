#include <iostream>

#include "gtest/gtest.h"
#include "file_tools.h"
#include "network_tools.h"
#include "Library.h"


TEST(DLRTests, DownloadLibrary)
{	
    Library library;
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
    bool result = library.downloadLibrary(url, target);
    File::removeFile(target);
    EXPECT_TRUE(result);
}

TEST(DLRTests, OpenLibrary)
{	
    Library library;
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
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
    std::string target = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
    library.downloadLibrary(url, target);

	library.setXSLibraryPath(target);
    std::vector<std::string> nucVec = {"Pu239", "La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.getNuclides(nucVec);
    size_t numberOfNuclides = library.getNumberOfNuclidesRead();
    File::removeFile(target);

    EXPECT_EQ(numberOfNuclides, 2);
}

TEST(DLRTests, GetLibraryNuclides)
{	
    Library library;
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
    library.downloadLibrary(url, target);

	library.setXSLibraryPath(target);
    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.getNuclides(nucVec);
    std::vector<std::string> nuclideVec = library.getLibraryNuclides();

    std::vector<std::string> refVec {"La139", "B11", "Sm154", "Kr83", "Sn114", "Te126", "Sr86", "Pu239", "C0", "Cm243", "Cd108", "Xe128", "Ti49", "Pa233", "N14", "N15", "Si30", "Nd143",
    "DEPL-CHAIN", "Zr96", "Sm153", "Gd157", "La138", "Ca46", "O16", "Ni61", "Te125", "Se77", "W182", "V0", "Cd106", "Mo100", "Pu238", "O17", "Cm247",
    "Ru104", "Er167", "Sn112", "Sm152", "K40", "Ba140", "Zr95", "F19", "Te124", "Am241", "I135", "Kr82", "Cr52", "Ag111", "Ca42", "Nd142", "Gd156",
    "Si29", "Er166", "Se76", "Sm151", "Bi209", "Rb87", "Zr94", "Ba138", "S36", "Ni60", "Te123", "Pb204", "Pu237", "Ag109", "Cm242", "Mo99", "Na23",
    "Ho165", "Sm150", "Mg24", "In115", "Si28", "Zr93", "Ba137", "Ti46", "Te122", "I131", "As75", "Mg25", "Gd155", "Ag107", "Pr143", "Hf180", "Sm149",
    "Zn0", "Al27", "Ru103", "Mg26", "Kr80", "Zr92", "Ba136", "Pa231", "Sb126", "Pu244", "Pd110", "Sm148", "Hf179", "Pu236", "Ni58", "Ge76", "Zr91",
    "Mo97", "In113", "Ba135", "Sb125", "Sm147", "Gd154", "Hf178", "Pd108", "I130", "S34", "Cm246", "Pr142", "K39", "Sn119", "Rb85", "Zr90", "Pm151",
    "Ba134", "Hf177", "Sb124", "U233", "Pd107", "Ti48", "Np239", "Y91", "Pm149", "Ge74", "Sb123", "Hf176", "Cs137", "Pd106", "Co59", "Ca44", "Gd152",
    "Y90", "Pm148m", "Ru102", "Pd105", "Hf174", "Sb121", "I129", "Cs136", "Pr141", "Pm148", "Cd116", "Cm241", "Br81", "Dy164", "Y89", "Pd104", "Pm147",
    "Sn126", "Mo96", "Cs135", "Dy163", "Nd150", "Rh105", "Sr90", "Sn125", "Nd148", "Eu157", "Dy162", "Rh103", "Ru106", "Nd147", "Cs134", "Nd146", "Dy161",
    "Nd145", "Sr89", "Sn124", "W186", "Dy160", "Sn118", "Sn123", "Cs133", "Tb160", "Pb208", "Sn122", "Tb159", "Ce144", "Gd160", "Gd158", "Sn120", "I127",
    "Xe136", "H1_H2O", "Ge73", "Pu243", "Xe135", "Cu65", "Eu156", "Np238", "Xe134", "Ca40", "Xe133", "Xe132", "Cd115m", "H2_D2O", "Fe58", "Ge72", "H1_CH2",
    "Ti50", "H1_ZRH", "Mo95", "Kr86", "Ce143", "Np237", "Zr90_ZRH", "Ru101", "Br79", "Cf253", "Te132", "Fe57", "Eu155", "S33", "C0_GR", "Cm245", "Cf252",
    "Cd114", "Sn117", "Cr50", "Np236", "Pu242", "Cf251", "Am243", "Sr88", "Mo94", "Xe131", "Ce142", "Th232", "Cf250", "Fe56", "Cf249", "Bk249", "Te130",
    "Eu154", "Se82", "Cu63", "Be9", "U238", "Kr85", "Cd113", "Ru100", "H1", "W184", "Fe54", "U237", "Cr53", "Mo92", "U232", "Ce141", "Sn116", "U236", "Mn55",
    "U235", "Te129m", "Eu153", "Pu241", "U234", "Pb207", "Xe130", "Se80", "Cr54", "Cd112", "Ca48", "Cl37", "Am242m", "Cm244", "Sr87", "Nb95", "H2", "Ce140",
    "H3", "Ru99", "He3", "Ni64", "Eu152", "Te128", "Kr84", "S32", "He4", "Ca43", "Cd111", "Sn115", "K41", "Pu240", "Se79", "Cm248", "Li6", "Nb94", "Xe129",
    "La140", "Ti47", "W183", "Li7", "Eu151", "Th230", "Te127m", "Nd144", "Be7", "B10", "P31", "Ni62", "Cd110", "Ru105", "Cl35", "Am242", "Tc99", "Pb206", "Se78"};

    File::removeFile(target);
    bool areEqual = std::equal(refVec.begin(), refVec.end(), nuclideVec.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetNuclide)
{	
    Library library;
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
    library.downloadLibrary(url, target);

	library.setXSLibraryPath(target);
    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.getNuclides(nucVec);
    
    size_t size = nuclides[0]->getCopyOfXSSets().size();
    File::removeFile(target);
    EXPECT_EQ(size, 10);
}

TEST(DLRTests, GetTotalCrossSectionSetNonResonant)
{	
    Library library;
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
    library.downloadLibrary(url, target);

	library.setXSLibraryPath(target);
    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.getNuclides(nucVec);
    
    size_t size = nuclides[0]->getXSSet(XSKind::NTOT0).getSize();
    File::removeFile(target);
    EXPECT_EQ(size, 5);
}