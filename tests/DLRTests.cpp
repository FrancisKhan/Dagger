#include <iostream>

#include "gtest/gtest.h"
#include "file_tools.h"
#include "network_tools.h"
#include "Library.h"
#include "additionalPrintFuncs.h"


TEST(DLRTests, DownloadLibrary)
{	
    Library library;
    std::string url = "https://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibendfb7r0.gz";
    std::string target = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	File::removeFile(target);

    EXPECT_TRUE(library.downloadLibrary(url, target));
}

TEST(DLRTests, OpenLibrary)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::string inputPath = library.getXSLibraryPath();
    EXPECT_EQ(inputPath, refLibPath);
}

TEST(DLRTests, GetNuclides)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239", "La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    size_t numberOfNuclides = library.getNumberOfNuclidesRead();
    EXPECT_EQ(numberOfNuclides, 2);
}

TEST(DLRTests, GetLibraryNuclides)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
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

    bool areEqual = std::equal(refVec.begin(), refVec.end(), nuclideVec.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetNuclide)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    size_t size = library.getNuclide("La139")->getCopyOfXSSets().size();
    EXPECT_EQ(size, 14);
}

TEST(DLRTests, GetTotalCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::NTOT0).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetInelCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

    size_t size = library.getNuclide("La139")->getXSSet(XSKind::NINEL).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetN2NCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

    size_t size = library.getNuclide("La139")->getXSSet(XSKind::N2N).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetN3NCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::N3N).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetN4NCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::N4N).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetNNPCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::NNP).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetNGCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::NG).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetNPCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::NP).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetNDCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::ND).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetNTCrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::NT).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetNACrossSectionSetNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("La139")->getXSSet(XSKind::NA).getSize();
    EXPECT_EQ(size, 5);
}

TEST(DLRTests, GetTotalCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NTOT0).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetInelCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NINEL).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetN2NCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);

    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::N2N).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetN3NCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::N3N).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetN4NCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::N4N).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetNNPCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NNP).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetNGCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NG).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetNPCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NP).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetNDCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::ND).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetNTCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NT).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetNACrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NA).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetNFTOTCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NFTOT).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetNUSIGFCrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::NUSIGF).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetCHICrossSectionSetResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    
    size_t size = library.getNuclide("Pu239")->getXSSet(XSKind::CHI).getSize();
    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetTotalCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::NTOT0).getXS(293.0, Numerics::DINF).getValues();

	std::vector<double> ref {4.54110384e+00, 4.80455208e+00, 4.91122198e+00, 
	4.92818308e+00, 4.81587982e+00, 4.56882095e+00, 4.30204201e+00, 4.22017908e+00, 
	4.26859808e+00, 4.51293898e+00, 4.99486494e+00, 5.54959106e+00, 6.08871984e+00, 
	6.45873594e+00, 6.67825699e+00, 6.93404198e+00, 7.11555481e+00, 7.10220623e+00, 
	7.00825691e+00, 6.88025188e+00, 6.74418879e+00, 6.59889507e+00, 6.35092688e+00, 
	6.13608599e+00, 6.03478003e+00, 5.93299484e+00, 5.82348680e+00, 5.59495115e+00, 
	5.36819410e+00, 5.25953388e+00, 5.06271315e+00, 4.80566120e+00, 4.70044994e+00, 
	4.71004581e+00, 4.86195803e+00, 5.00532293e+00, 5.19846201e+00, 5.36432409e+00, 
	5.51521492e+00, 5.65878391e+00, 5.74306583e+00, 5.42385197e+00, 4.32109118e+00, 
	4.56141996e+00, 4.47037601e+00, 5.72132683e+00, 5.45120478e+00, 4.33354521e+00, 
	8.20845509e+00, 8.40700722e+00, 1.14971905e+01, 2.26723309e+01, 2.35801911e+00, 
	2.66417193e+00, 3.31265807e+00, 1.60623894e+01, 2.73721600e+00, 2.90113401e+00, 
	2.96272206e+00, 3.17677999e+00, 2.94368100e+00, 3.09399199e+00, 3.32189202e+00, 
	3.65472603e+00, 3.89585996e+00, 4.28305817e+00, 5.29422522e+00, 1.14840103e+02, 
	4.80964518e+00, 5.18665504e+00, 5.35645485e+00, 5.50124216e+00, 5.70934391e+00, 
	5.93407679e+00, 6.12901402e+00, 6.35085583e+00, 6.57172298e+00, 6.79089022e+00, 
	7.00767994e+00, 7.27411509e+00, 7.63594389e+00, 7.98301697e+00, 8.31119919e+00, 
	8.59934044e+00, 8.76777935e+00, 8.90929127e+00, 9.06481647e+00, 9.28493786e+00, 
	9.52058983e+00, 9.65082455e+00, 9.81008053e+00, 9.94725704e+00, 1.00601263e+01, 
	1.01658087e+01, 1.02716179e+01, 1.03714695e+01, 1.04034576e+01, 1.04356575e+01, 
	1.04841280e+01, 1.05726910e+01, 1.06297464e+01, 1.06552401e+01, 1.06954088e+01, 
	1.07400303e+01, 1.07853889e+01, 1.08313599e+01, 1.08779898e+01, 1.09290581e+01, 
	1.09644089e+01, 1.09843025e+01, 1.10192394e+01, 1.10541286e+01, 1.10792189e+01, 
	1.11178293e+01, 1.11693687e+01, 1.12048855e+01, 1.12252598e+01, 1.12432194e+01, 
	1.12555199e+01, 1.12740107e+01, 1.12992697e+01, 1.13180981e+01, 1.13313208e+01, 
	1.13520174e+01, 1.13711786e+01, 1.13855906e+01, 1.14078608e+01, 1.14366713e+01, 
	1.14655886e+01, 1.15300016e+01, 1.16005402e+01, 1.17829800e+01, 1.21841021e+01, 
	1.32906504e+01, 1.21755733e+01, 1.19541607e+01, 1.20430355e+01, 1.20980005e+01, 
	1.21767998e+01, 1.22878103e+01, 1.23493004e+01, 1.24327793e+01, 1.25624542e+01, 
	1.26340332e+01, 1.26781158e+01, 1.27592268e+01, 1.28968506e+01, 1.30794840e+01, 
	1.33037720e+01, 1.34685259e+01, 1.36240377e+01, 1.38586750e+01, 1.40207281e+01, 
	1.42325993e+01, 1.45453300e+01, 1.47563810e+01, 1.50345287e+01, 1.52916317e+01, 
	1.55320902e+01, 1.59297228e+01, 1.63711815e+01, 1.68970661e+01, 1.75275230e+01, 
	1.81780815e+01, 1.88826370e+01, 1.98104248e+01, 2.11133747e+01, 2.31346550e+01, 
	2.59432449e+01, 2.89832954e+01, 3.31386414e+01, 4.61073036e+01};

    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetInelCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::NINEL).getXS(293.0, Numerics::DINF).getValues();

	std::vector<double> ref {0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 4.44751501e-01, 5.34929395e-01, 6.28362477e-01, 
	9.15886104e-01, 1.54972100e+00, 2.12181091e+00, 2.14398789e+00, 2.14158392e+00, 
	2.16643095e+00, 2.23892808e+00, 2.29722404e+00, 2.18650389e+00, 1.91091895e+00, 
	1.74666297e+00, 1.65001297e+00, 1.46051502e+00, 1.04663599e+00, 7.28291690e-01, 
	6.19041383e-01, 5.91151476e-01, 5.61844826e-01, 5.29296875e-01, 4.67026114e-01, 
	4.12149698e-01, 3.88583809e-01, 3.67220700e-01, 3.47438604e-01, 3.09488088e-01, 
	2.68817514e-01, 2.45647207e-01, 1.76098093e-01, 8.89868010e-03};

    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetN2NCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::N2N).getXS(293.0, Numerics::DINF).getValues();

	std::vector<double> ref {0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 1.55825698e+00, 1.56992400e+00, 
	1.48506498e+00, 1.21417201e+00, 6.03158891e-01, 4.12262082e-02};
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetN3NCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::N3N).getXS(293.0, Numerics::DINF).getValues();

    std::vector<double> ref {0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 8.07629228e-02, 3.16674792e-04};
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetN4NCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::N4N).getXS(293.0, Numerics::DINF).getValues();

    std::vector<double> ref(172, 0.000000000000e+00);
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetNNPCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::NNP).getXS(293.0, Numerics::DINF).getValues();

	std::vector<double> ref {0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 4.04511811e-03, 
	1.05167401e-03, 2.55840103e-04, 3.25791189e-05, 1.05037998e-06};
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetNGCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::NG).getXS(293.0, Numerics::DINF).getValues();

	std::vector<double> ref {1.05950504e-03, 9.97772557e-04, 9.98312258e-04, 
	1.01523101e-03, 8.04598676e-04, 3.60931503e-04, 2.28132296e-04, 3.21953004e-04, 
	4.78444912e-04, 8.13469815e-04, 1.75857905e-03, 3.43982503e-03, 5.22513315e-03, 
	6.48058578e-03, 7.37583404e-03, 8.75606574e-03, 9.97378957e-03, 9.94500145e-03, 
	9.60356742e-03, 9.00797546e-03, 8.51736683e-03, 8.14251229e-03, 7.65158515e-03, 
	7.39035383e-03, 7.35607091e-03, 7.36624887e-03, 7.44071789e-03, 7.76361814e-03, 
	8.27548560e-03, 8.62626266e-03, 9.78147332e-03, 1.36347497e-02, 1.60401799e-02, 
	1.83553807e-02, 2.11307798e-02, 2.37601008e-02, 2.77456306e-02, 3.15924101e-02, 
	3.54999788e-02, 3.94336805e-02, 4.18988690e-02, 4.02034707e-02, 2.92051509e-02, 
	4.51526493e-02, 6.05048314e-02, 1.62154496e-01, 1.13257602e-01, 1.13868698e-01, 
	1.12263203e-01, 1.80145994e-01, 1.72051594e-01, 6.31296217e-01, 1.04820698e-01, 
	1.35181397e-02, 1.63397595e-01, 3.81491214e-01, 2.78494805e-01, 2.79772997e-01, 
	2.81265795e-01, 2.52580494e-01, 1.03550300e-03, 2.11940892e-02, 1.87321901e-02, 
	5.93377696e-03, 9.01488960e-03, 1.81366205e-02, 1.34107500e-01, 6.64971085e+01, 
	1.37203202e-01, 6.88466206e-02, 6.71038330e-02, 6.83850423e-02, 7.31092021e-02, 
	8.03599730e-02, 8.82344916e-02, 9.86144692e-02, 1.10401101e-01, 1.23505697e-01, 
	1.37896895e-01, 1.57765999e-01, 1.88877493e-01, 2.23735094e-01, 2.62765110e-01, 
	3.02379191e-01, 3.28539997e-01, 3.52620989e-01, 3.81355494e-01, 4.27136898e-01, 
	4.83166903e-01, 5.17981827e-01, 5.65746427e-01, 6.10222518e-01, 6.51152074e-01, 
	6.91765606e-01, 7.36479580e-01, 7.80843496e-01, 7.96029925e-01, 8.11353981e-01, 
	8.35471690e-01, 8.81355882e-01, 9.12267208e-01, 9.26425695e-01, 9.49088573e-01, 
	9.75080729e-01, 1.00225401e+00, 1.03047705e+00, 1.05981803e+00, 1.09295404e+00, 
	1.11623299e+00, 1.12975204e+00, 1.15349305e+00, 1.17752397e+00, 1.19513798e+00, 
	1.22272599e+00, 1.26029599e+00, 1.28672099e+00, 1.30201995e+00, 1.31566703e+00, 
	1.32515204e+00, 1.33940804e+00, 1.35903299e+00, 1.37396502e+00, 1.38446796e+00, 
	1.40092003e+00, 1.41639698e+00, 1.42818499e+00, 1.44651699e+00, 1.47073996e+00, 
	1.49529505e+00, 1.55199301e+00, 1.61600101e+00, 1.79066098e+00, 2.18414903e+00, 
	3.28116989e+00, 2.14883089e+00, 1.90892196e+00, 1.98389995e+00, 2.03270507e+00, 
	2.10379791e+00, 2.20517993e+00, 2.26189590e+00, 2.33953500e+00, 2.46102810e+00, 
	2.52850509e+00, 2.57024288e+00, 2.64727592e+00, 2.77867103e+00, 2.95409489e+00, 
	3.17091894e+00, 3.33088994e+00, 3.48245192e+00, 3.71182489e+00, 3.87060905e+00, 
	4.07869816e+00, 4.38648176e+00, 4.59453392e+00, 4.86912823e+00, 5.12316608e+00, 
	5.36096716e+00, 5.75448084e+00, 6.19165611e+00, 6.71268511e+00, 7.33749199e+00, 
	7.98223686e+00, 8.68041039e+00, 9.59947491e+00, 1.08893299e+01, 1.28879299e+01, 
	1.56598902e+01, 1.86530800e+01, 2.27311001e+01, 3.53096619e+01};
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetNPCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::NP).getXS(293.0, Numerics::DINF).getValues();

	std::vector<double> ref {0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 1.07188597e-02, 
	6.42032316e-03, 3.72799905e-03, 1.39681099e-03, 3.29124392e-04, 5.68041287e-05, 
	7.79704624e-06, 1.53961298e-06, 4.86339673e-07, 5.70574308e-08};
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetNDCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::ND).getXS(293.0, Numerics::DINF).getValues();

    std::vector<double> ref {0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 7.31842406e-03, 1.41100097e-03, 
	2.85235496e-04, 6.10484421e-05, 6.37466292e-06, 2.66982710e-07};
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetNTCrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::NT).getXS(293.0, Numerics::DINF).getValues();

    std::vector<double> ref {0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 1.39458396e-03, 
	5.88281022e-04, 1.04688697e-04, 5.81945278e-06, 1.30193802e-08};
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetNACrossSectionNonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"La139"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("La139")->getXSSet(XSKind::NA).getXS(293.0, Numerics::DINF).getValues();
    
    	std::vector<double> ref {0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 
	0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 3.41834011e-03, 
	2.63833394e-03, 1.86971703e-03, 9.33425501e-04, 2.53727514e-04, 8.53571601e-06, 
	1.63235404e-06, 4.52618195e-07, 1.61087897e-07, 9.27575972e-09};
    
    bool areEqual = std::equal(ref.begin(), ref.end(), xs.begin());
    EXPECT_TRUE(areEqual);
}

TEST(DLRTests, GetTotalCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NTOT0).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref {6.151040080000e+00, 6.006264210000e+00, 5.894751070000e+00, 
	5.796453000000e+00, 5.845954900000e+00, 6.111144070000e+00, 6.577434060000e+00, 6.961059090000e+00, 
	7.254042150000e+00, 7.649480820000e+00, 7.944606780000e+00, 7.907044890000e+00, 7.696843150000e+00, 
	7.479269030000e+00, 7.317226890000e+00, 7.105926040000e+00, 6.896525860000e+00, 6.827847000000e+00, 
	6.845621110000e+00, 6.915193080000e+00, 7.036260130000e+00, 7.238356110000e+00, 7.719263080000e+00, 
	8.204987530000e+00, 8.454483030000e+00, 8.711734770000e+00, 8.974776270000e+00, 9.509425160000e+00, 
	1.003845980000e+01, 1.028818040000e+01, 1.074361040000e+01, 1.142817970000e+01, 1.184842970000e+01, 
	1.214863970000e+01, 1.252033040000e+01, 1.282674980000e+01, 1.322647000000e+01, 1.355494980000e+01, 
	1.384167000000e+01, 1.414873980000e+01, 1.428588010000e+01, 1.471827030000e+01, 1.517368030000e+01, 
	1.556690980000e+01, 1.595143030000e+01, 1.647966960000e+01, 1.712413020000e+01, 1.773407940000e+01, 
	1.826655010000e+01, 1.777301980000e+01, 2.007872010000e+01, 1.925996020000e+01, 2.107517050000e+01, 
	2.037490080000e+01, 2.287550930000e+01, 2.327058030000e+01, 2.879990010000e+01, 2.318672940000e+01, 
	2.152634050000e+01, 3.494644170000e+01, 2.486829950000e+01, 3.535044100000e+01, 5.032812880000e+01, 
	4.432304000000e+01, 4.674983980000e+01, 5.520196910000e+01, 9.920126340000e+01, 1.363560940000e+02, 
	1.277938000000e+02, 1.581064000000e+02, 9.468679810000e+01, 4.889522170000e+01, 1.452032010000e+02, 
	9.292217250000e+00, 1.665612030000e+01, 1.846541020000e+01, 1.130613990000e+01, 8.525469970000e+01, 
	2.751512910000e+01, 1.102893980000e+02, 1.072029040000e+02, 2.925147090000e+02, 1.527463990000e+02, 
	3.312701110000e+02, 1.641695980000e+01, 1.732208060000e+01, 3.828304140000e+02, 2.512553980000e+01, 
	1.690971950000e+01, 1.690476990000e+01, 1.750494960000e+01, 1.825637050000e+01, 1.910868640000e+01, 
	2.001894570000e+01, 2.114936640000e+01, 2.234705730000e+01, 2.277967070000e+01, 2.323751070000e+01, 
	2.397585300000e+01, 2.547199820000e+01, 2.652802470000e+01, 2.704931830000e+01, 2.790475460000e+01, 
	2.892482950000e+01, 3.004311560000e+01, 3.127496340000e+01, 3.263522720000e+01, 3.424046330000e+01, 
	3.545314410000e+01, 3.611279720090e+01, 3.744636515710e+01, 3.886323978790e+01, 3.993930961800e+01, 
	4.170324814300e+01, 4.428437136100e+01, 4.619013679900e+01, 4.737296392200e+01, 4.843298069100e+01, 
	4.913967894400e+01, 5.027384217300e+01, 5.189069243100e+01, 5.308205071600e+01, 5.393739256500e+01, 
	5.536838292600e+01, 5.668555111100e+01, 5.764383058200e+01, 5.933907624700e+01, 6.109191001600e+01, 
	6.338491139200e+01, 6.734307387000e+01, 7.176614724800e+01, 7.718921902000e+01, 8.371049830000e+01, 
	9.318605469000e+01, 1.238774182000e+02, 1.841017066900e+02, 2.660296537900e+02, 3.339229541900e+02, 
	4.683134084700e+02, 7.760038285000e+02, 1.053639295000e+03, 1.707973433000e+03, 3.374625847300e+03, 
	4.488781342100e+03, 4.967381072200e+03, 5.215709838300e+03, 3.963940734000e+03, 2.403321220100e+03, 
	1.515375165100e+03, 1.106121184800e+03, 1.027054029037e+03, 8.767338900600e+02, 8.136724757000e+02, 
	7.673570694756e+02, 6.915119016000e+02, 7.152223566600e+02, 6.468775249000e+02, 6.578510590000e+02, 
	5.422652890000e+02, 6.598287662000e+02, 5.428160860000e+02, 8.151601443990e+02, 8.680026507260e+02, 
	6.569344790000e+02, 9.903212340700e+02, 1.081089357294e+03, 1.209636899291e+03, 1.413053130877e+03, 
	1.699493832764e+03, 2.011764579486e+03, 2.439847328493e+03, 3.768437451409e+03};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetInelCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NINEL).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref {0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 4.045647980000e-01, 4.588080940000e-01, 
	4.901109040000e-01, 5.601137280000e-01, 6.439865230000e-01, 7.595742940000e-01, 9.639034870000e-01, 
	1.371742960000e+00, 1.689239030000e+00, 1.756311060000e+00, 1.754394050000e+00, 1.816218020000e+00, 
	1.878677960000e+00, 1.880898000000e+00, 1.861026050000e+00, 1.830957060000e+00, 1.723109010000e+00, 
	1.612424020000e+00, 1.582736970000e+00, 1.562841060000e+00, 1.518908980000e+00, 1.463665960000e+00, 
	1.377563000000e+00, 1.320667980000e+00, 1.274271010000e+00, 1.221135020000e+00, 1.209246990000e+00, 
	1.157217030000e+00, 1.090363030000e+00, 1.056154970000e+00, 9.982910750000e-01, 8.578732010000e-01, 
	7.423893210000e-01, 6.599575880000e-01, 5.509240030000e-01, 4.849047960000e-01, 4.412296120000e-01, 
	4.176518920000e-01, 4.032954870000e-01, 3.923409880000e-01, 3.873212040000e-01, 3.724480870000e-01, 
	3.524008990000e-01, 3.265711960000e-01, 2.863177060000e-01, 9.695281830000e-02};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetN2NCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::N2N).getXS(5.50000000e+02, 2.51750000e+02).getValues();

		std::vector<double> ref {0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	1.121985020000e-01, 1.626157020000e-01, 2.167616040000e-01, 2.925193010000e-01, 3.255606890000e-01, 
	2.495885940000e-01, 1.381752940000e-01, 6.794351340000e-02, 4.514005970000e-03};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetN3NCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::N3N).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref {0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 0.000000000000e+00, 
	3.179849090000e-01, 1.265338960000e-01, 2.607551960000e-02, 5.865367710000e-04};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetN4NCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::N4N).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref(171, 0.000000000000e+00);
	ref.push_back(1.824667920000e-05);

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetNNPCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NNP).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref(172, 0.000000000000e+00);

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetNGCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NG).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref {2.210438950000e-03, 2.118142090000e-03, 2.229847010000e-03, 
	2.448844020000e-03, 2.181936060000e-03, 9.069116200000e-04, 3.745626890000e-04, 4.630720940000e-04, 
	8.187838830000e-04, 1.608195950000e-03, 2.030418020000e-03, 2.599681960000e-03, 3.899808040000e-03, 
	5.681205080000e-03, 7.182520810000e-03, 9.426450360000e-03, 1.306570040000e-02, 1.689573940000e-02, 
	1.980582070000e-02, 2.347821000000e-02, 2.835730090000e-02, 3.475702180000e-02, 6.198799980000e-02, 
	8.738352360000e-02, 9.997683020000e-02, 1.113997030000e-01, 1.233917030000e-01, 1.515721980000e-01, 
	1.821082980000e-01, 1.883980930000e-01, 1.922121050000e-01, 2.086540010000e-01, 2.226818050000e-01, 
	2.377216070000e-01, 2.699317040000e-01, 3.091860120000e-01, 3.697252870000e-01, 4.204905030000e-01, 
	4.742453100000e-01, 5.520278220000e-01, 5.838804240000e-01, 6.951770190000e-01, 8.109478950000e-01, 
	9.599943160000e-01, 1.116376040000e+00, 1.282526970000e+00, 1.657578950000e+00, 1.938063030000e+00, 
	2.127799030000e+00, 2.347717050000e+00, 2.729408980000e+00, 3.817059990000e+00, 3.640553950000e+00, 
	2.986349110000e+00, 3.843030930000e+00, 4.191730980000e+00, 5.028538230000e+00, 3.984361890000e+00, 
	4.472674850000e+00, 7.783953190000e+00, 4.782465930000e+00, 1.174172970000e+01, 1.628525920000e+01, 
	1.199073980000e+01, 1.733997920000e+01, 1.741328050000e+01, 2.944676020000e+01, 3.605199810000e+01, 
	2.268330000000e+01, 1.015835040000e+02, 4.643902970000e+01, 5.638514040000e+00, 1.052053990000e+02, 
	6.782180070000e-01, 6.289919850000e+00, 2.285613060000e+00, 5.551387070000e-01, 3.836269000000e+01, 
	6.088389870000e+00, 3.990327070000e+01, 4.549312970000e+01, 1.198088000000e+02, 7.278118900000e+01, 
	6.380638890000e+01, 3.230456110000e+00, 4.172525880000e+00, 1.693132930000e+02, 4.944345000000e+00, 
	1.515349030000e+00, 1.381261940000e+00, 1.399252060000e+00, 1.474851010000e+00, 1.589723940000e+00, 
	1.720927000000e+00, 1.896579980000e+00, 2.088691950000e+00, 2.160296920000e+00, 2.236762050000e+00, 
	2.362380980000e+00, 2.623322010000e+00, 2.811904910000e+00, 2.906919960000e+00, 3.064605000000e+00, 
	3.256383900000e+00, 3.470972060000e+00, 3.712563040000e+00, 3.985640050000e+00, 4.315779210000e+00, 
	4.570602890000e+00, 4.720078841106e+00, 5.012964106610e+00, 5.330391092000e+00, 5.576360123520e+00, 
	5.986664801130e+00, 6.600340441750e+00, 7.064511620630e+00, 7.360274585020e+00, 7.626586937600e+00, 
	7.809907451970e+00, 8.103828076900e+00, 8.523462328100e+00, 8.837711987200e+00, 9.069391819700e+00, 
	9.453966232100e+00, 9.811341293900e+00, 1.007547756600e+01, 1.051899338240e+01, 1.103612197100e+01, 
	1.159456297600e+01, 1.275882742500e+01, 1.404562318300e+01, 1.568133735500e+01, 1.767458900300e+01, 
	2.084616483400e+01, 3.067695344500e+01, 5.150537778500e+01, 8.171424182000e+01, 1.067416142690e+02, 
	1.572090493500e+02, 2.769888663800e+02, 3.866502134400e+02, 6.465304645000e+02, 1.321672199840e+03, 
	1.779201988600e+03, 1.991389028400e+03, 2.106617901900e+03, 1.573202640600e+03, 9.590751361000e+02, 
	6.023958598500e+02, 3.956966321000e+02, 3.899680123798e+02, 3.217258286720e+02, 2.924124531910e+02, 
	2.679300485891e+02, 2.272082937000e+02, 2.345666193160e+02, 2.019154315000e+02, 1.944688754000e+02, 
	1.368584828000e+02, 1.743233793000e+02, 1.801728823000e+02, 2.299152513380e+02, 2.390115865030e+02, 
	1.299851230000e+02, 2.632008447060e+02, 2.827047823226e+02, 3.111678755797e+02, 3.576048650960e+02, 
	4.244642009961e+02, 4.984201317965e+02, 6.007858217810e+02, 9.215761672599e+02};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetNPCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NP).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref(172, 0.000000000000e+00);

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetNDCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::ND).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref(172, 0.000000000000e+00);

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetNTCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NT).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref(172, 0.000000000000e+00);

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetNACrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NA).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref(172, 0.000000000000e+00);

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetNFTOTCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NFTOT).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref {2.350255970000e+00, 2.420903920000e+00, 2.415081980000e+00, 
	2.286206960000e+00, 2.237148050000e+00, 2.250340940000e+00, 2.136674880000e+00, 1.891438010000e+00, 
	1.698135970000e+00, 1.706519010000e+00, 1.771293040000e+00, 1.831783060000e+00, 1.894363050000e+00, 
	1.934142950000e+00, 1.974167940000e+00, 1.954396960000e+00, 1.936439990000e+00, 1.864397050000e+00, 
	1.787876960000e+00, 1.738963010000e+00, 1.700963020000e+00, 1.685464020000e+00, 1.651312950000e+00, 
	1.585983040000e+00, 1.559703950000e+00, 1.573289040000e+00, 1.561470030000e+00, 1.552503940000e+00, 
	1.542135950000e+00, 1.516837000000e+00, 1.490543960000e+00, 1.495951060000e+00, 1.514603020000e+00, 
	1.536977050000e+00, 1.549541000000e+00, 1.558411000000e+00, 1.540469050000e+00, 1.562018040000e+00, 
	1.614138960000e+00, 1.566985010000e+00, 1.585826040000e+00, 1.647958040000e+00, 1.776383040000e+00, 
	1.791007040000e+00, 1.867076990000e+00, 2.180797100000e+00, 2.099561930000e+00, 2.261956930000e+00, 
	2.556533100000e+00, 2.069562910000e+00, 3.567950960000e+00, 2.461177110000e+00, 3.916994090000e+00, 
	4.753939150000e+00, 5.927555080000e+00, 5.561376090000e+00, 8.282878880000e+00, 5.670394900000e+00, 
	4.424879070000e+00, 1.091884990000e+01, 8.033204080000e+00, 8.562432290000e+00, 1.694275090000e+01, 
	1.741609950000e+01, 1.573558040000e+01, 2.318301960000e+01, 4.827920150000e+01, 7.792392730000e+01, 
	9.183061980000e+01, 2.621068950000e+01, 3.446514130000e+01, 3.375743870000e+01, 2.050579070000e+01, 
	1.236817960000e+00, 1.862063050000e+00, 7.095921990000e+00, 8.480430840000e-01, 3.572027970000e+01, 
	1.008491040000e+01, 5.923875050000e+01, 4.917329030000e+01, 1.580063930000e+02, 6.824520870000e+01, 
	2.585159000000e+02, 5.701860900000e+00, 4.340898040000e+00, 2.012705990000e+02, 1.283372970000e+01, 
	7.107427120000e+00, 7.007001880000e+00, 7.381894110000e+00, 7.903581140000e+00, 8.530845640000e+00, 
	9.212067600000e+00, 1.007479000000e+01, 1.099526020000e+01, 1.132968040000e+01, 1.168396000000e+01, 
	1.225648020000e+01, 1.341782000000e+01, 1.423760030000e+01, 1.464216040000e+01, 1.530541990000e+01, 
	1.609510990000e+01, 1.695903020000e+01, 1.790805050000e+01, 1.895232960000e+01, 2.017974090000e+01, 
	2.110337070000e+01, 2.163130980973e+01, 2.264954111777e+01, 2.372941502415e+01, 2.454736146700e+01, 
	2.587926821680e+01, 2.780610609400e+01, 2.922154969900e+01, 3.010071134440e+01, 3.088130980410e+01, 
	3.141529534330e+01, 3.225991661690e+01, 3.345211917230e+01, 3.433328299220e+01, 3.497434908780e+01, 
	3.604800210350e+01, 3.703024720590e+01, 3.775234624230e+01, 3.894680217130e+01, 4.032744644900e+01, 
	4.191714119100e+01, 4.482280741500e+01, 4.772617622700e+01, 5.163367863700e+01, 5.618099678400e+01, 
	6.316221921400e+01, 8.306872609500e+01, 1.216163211930e+02, 1.745298643300e+02, 2.154963737200e+02, 
	2.997240065200e+02, 4.883527480800e+02, 6.553876933300e+02, 1.047410262350e+03, 2.038570448490e+03, 
	2.700670105400e+03, 2.972065974500e+03, 3.100860098900e+03, 2.399016617600e+03, 1.443033877500e+03, 
	9.079797482100e+02, 7.134133372000e+02, 6.305396114998e+02, 5.483738691820e+02, 5.145306724170e+02, 
	4.922989000116e+02, 4.591169281000e+02, 4.739319009710e+02, 4.402422297000e+02, 4.586286546000e+02, 
	4.052069167000e+02, 4.812832303000e+02, 3.593812410000e+02, 5.776384389270e+02, 6.213716457450e+02, 
	5.249649040000e+02, 7.195840739800e+02, 7.906366584280e+02, 8.906830733950e+02, 1.047636717057e+03, 
	1.267191868362e+03, 1.505481682906e+03, 1.831153391792e+03, 2.838643662625e+03};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetNUSIGFCrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::NUSIGF).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref {1.288118360000e+01, 1.252699470000e+01, 1.202330590000e+01, 
	1.080385590000e+01, 1.002067470000e+01, 9.495697020000e+00, 8.501502040000e+00, 7.238233570000e+00, 
	6.330739020000e+00, 6.142384050000e+00, 6.131842610000e+00, 6.151956080000e+00, 6.209856990000e+00, 
	6.235605720000e+00, 6.306510930000e+00, 6.160966400000e+00, 5.998360630000e+00, 5.707031730000e+00, 
	5.436612610000e+00, 5.257878300000e+00, 5.117915150000e+00, 5.049915790000e+00, 4.911979680000e+00, 
	4.688170910000e+00, 4.599024300000e+00, 4.628949640000e+00, 4.585376740000e+00, 4.544206620000e+00, 
	4.501314160000e+00, 4.422282220000e+00, 4.336975570000e+00, 4.341151710000e+00, 4.389626500000e+00, 
	4.451958660000e+00, 4.487673760000e+00, 4.513107780000e+00, 4.460800650000e+00, 4.522784230000e+00, 
	4.673390390000e+00, 4.536631110000e+00, 4.591061590000e+00, 4.770635130000e+00, 5.142148020000e+00, 
	5.184313770000e+00, 5.404336450000e+00, 6.312282090000e+00, 6.077026840000e+00, 6.546980380000e+00, 
	7.399495600000e+00, 5.989997390000e+00, 1.032674600000e+01, 7.123353000000e+00, 1.133685400000e+01, 
	1.375915810000e+01, 1.715589140000e+01, 1.609603310000e+01, 2.397264670000e+01, 1.641125680000e+01, 
	1.280634210000e+01, 3.142231940000e+01, 2.306519700000e+01, 2.446602060000e+01, 4.856719210000e+01, 
	5.007815170000e+01, 4.500380330000e+01, 6.658537290000e+01, 1.388816990000e+02, 2.232697600000e+02, 
	2.644507450000e+02, 7.380773160000e+01, 9.878594970000e+01, 9.758954620000e+01, 5.732230760000e+01, 
	3.570949080000e+00, 5.287783150000e+00, 2.049436000000e+01, 2.444416050000e+00, 1.018980480000e+02, 
	2.882005690000e+01, 1.692948300000e+02, 1.403314820000e+02, 4.522236020000e+02, 1.944377140000e+02, 
	7.403392940000e+02, 1.638468550000e+01, 1.249708370000e+01, 5.743364870000e+02, 3.673122790000e+01, 
	2.040924640000e+01, 2.013440130000e+01, 2.122264290000e+01, 2.273043060000e+01, 2.454057880000e+01, 
	2.650550650000e+01, 2.899300960000e+01, 3.164662550000e+01, 3.261050420000e+01, 3.363161090000e+01, 
	3.528165820000e+01, 3.862806320000e+01, 4.098999400000e+01, 4.215542980000e+01, 4.406583400000e+01, 
	4.634021760000e+01, 4.882817080000e+01, 5.156042480000e+01, 5.456676860000e+01, 5.809933470000e+01, 
	6.075714110000e+01, 6.227621003220e+01, 6.520571568280e+01, 6.831166370400e+01, 7.066410717430e+01, 
	7.449445105720e+01, 8.003379700800e+01, 8.410262855180e+01, 8.662952171910e+01, 8.887252930680e+01, 
	9.040655469610e+01, 9.283308088840e+01, 9.625819771790e+01, 9.878975225300e+01, 1.006310690620e+02, 
	1.037140904260e+02, 1.065342545460e+02, 1.086073174590e+02, 1.120375117650e+02, 1.159997226990e+02, 
	1.205640854720e+02, 1.288999326520e+02, 1.372324690880e+02, 1.484352573600e+02, 1.614758406000e+02, 
	1.814751999600e+02, 2.385261036100e+02, 3.488822955990e+02, 5.002372431100e+02, 6.174030329400e+02, 
	8.582072888500e+02, 1.397291315900e+03, 1.874562298600e+03, 2.994707128500e+03, 5.826352415700e+03, 
	7.717676283900e+03, 8.492978058000e+03, 8.860587019000e+03, 6.857546352500e+03, 4.126266947700e+03, 
	2.598012442000e+03, 2.043570764100e+03, 1.806394192541e+03, 1.572147432686e+03, 1.475767957970e+03, 
	1.412714336092e+03, 1.318647020600e+03, 1.361317475980e+03, 1.265622689000e+03, 1.318834424500e+03, 
	1.166127014000e+03, 1.385031507000e+03, 1.036130251000e+03, 1.662026369589e+03, 1.788268603008e+03, 
	1.514619387000e+03, 2.071515496770e+03, 2.276329471917e+03, 2.564697978633e+03, 3.017022360468e+03, 
	3.649678110849e+03, 4.336259712176e+03, 5.274542288630e+03, 8.176984572900e+03};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetCHICrossSectionResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> xs = library.getNuclide("Pu239")->getXSSet(XSKind::CHI).getXS(5.50000000e+02, 2.51750000e+02).getValues();

	std::vector<double> ref {8.082575730000e-06, 4.209186950000e-05, 6.258555370000e-05, 
	4.768497310000e-04, 1.337711470000e-03, 4.988725760000e-03, 1.275756860000e-02, 1.097499950000e-02, 
	1.487907120000e-02, 4.317126050000e-02, 6.205504760000e-02, 7.931021600000e-02, 9.172122930000e-02, 
	4.833929990000e-02, 4.871755840000e-02, 9.511250260000e-02, 8.771246670000e-02, 4.008704050000e-02, 
	3.735477100000e-02, 3.452953320000e-02, 3.173023830000e-02, 2.896333860000e-02, 7.142603400000e-02, 
	1.913514730000e-02, 1.702905260000e-02, 1.509286460000e-02, 1.329487470000e-02, 3.091816980000e-02, 
	7.819732650000e-03, 6.820607930000e-03, 1.554419290000e-02, 1.267189530000e-02, 2.178892260000e-03, 
	4.917320800000e-03, 2.259662840000e-03, 1.680009880000e-03, 1.750122410000e-03, 4.306926280000e-04, 
	7.885260860000e-04, 1.800211610000e-04, 2.388237340000e-04, 6.693486940000e-04, 1.141501200000e-04, 
	2.566542830000e-04, 1.166882360000e-04, 8.568809430000e-05, 8.907747540000e-05, 2.190587840000e-05, 
	5.549037450000e-05, 5.830296690000e-06, 3.391897920000e-05, 5.781465920000e-06, 1.300756500000e-05, 
	1.662082920000e-06, 4.311856630000e-06, 4.452577290000e-06, 1.782040610000e-06, 2.868935330000e-06, 
	1.148904400000e-06, 3.234452830000e-06, 1.034782490000e-06, 7.747054840000e-07, 1.016082480000e-06, 
	4.789860100000e-07, 9.406109310000e-08, 3.248195530000e-07, 1.016229940000e-07, 4.648064690000e-08, 
	6.940836530000e-08, 2.145519320000e-08, 1.729362250000e-08, 1.388303070000e-08, 2.625612260000e-08, 
	1.372742990000e-08, 1.624951020000e-08, 1.418393670000e-08, 1.238731610000e-08, 1.082389640000e-08, 
	9.462779890000e-09, 1.201985440000e-08, 1.271646610000e-08, 7.560688080000e-09, 8.026674440000e-09, 
	4.054192540000e-09, 2.108616390000e-09, 2.453956590000e-09, 2.104361800000e-09, 3.368195280000e-09, 
	1.853458160000e-09, 6.602958740000e-10, 1.894604250000e-09, 2.559765460000e-10, 1.185596950000e-09, 
	1.496243410000e-10, 9.571972100000e-10, 8.375947850000e-11, 2.079740130000e-10, 8.590739920000e-11, 
	3.224328580000e-10, 3.818076690000e-10, 4.911421960000e-11, 1.301964090000e-10, 1.451236490000e-10, 
	1.436972760000e-10, 1.344042380000e-10, 1.331319080000e-10, 1.241383660000e-10, 1.383085170000e-10, 
	3.816587320000e-11, 5.324730590000e-11, 1.058474630000e-10, 4.885012880000e-11, 5.613439230000e-11, 
	9.671297790000e-11, 9.596895500000e-11, 2.937921430000e-11, 3.955020340000e-11, 1.899690300000e-11, 
	1.896714040000e-11, 3.784499450000e-11, 3.772595430000e-11, 1.447828490000e-11, 2.168440600000e-11, 
	3.461262870000e-11, 1.439198930000e-11, 2.011920140000e-11, 3.154615110000e-11, 2.860436190000e-11, 
	2.853392000000e-11, 7.102660820000e-11, 1.415248910000e-11, 8.454513480000e-11, 1.402921700000e-11, 
	1.046577890000e-10, 1.105431650000e-10, 1.162171330000e-10, 5.425016690000e-11, 2.027117020000e-11, 
	6.996660890000e-11, 4.415491240000e-11, 1.200896330000e-11, 5.452699750000e-11, 3.971024900000e-11, 
	7.263021780000e-12, 1.912242760000e-11, 2.631501270000e-11, 4.195749300000e-11, 3.656487270000e-11, 
	4.032149610000e-11, 1.167454240000e-11, 2.589235770000e-11, 2.582191580000e-11, 7.732777090000e-12, 
	2.444549770000e-11, 1.925417120000e-11, 6.409210840000e-12, 1.920133670000e-11, 3.835494420000e-12, 
	1.277353920000e-11, 1.148113290000e-11, 1.019348490000e-11, 1.018221970000e-11, 8.900197420000e-12, 
	6.352003990000e-12, 6.347603430000e-12, 6.343202870000e-12, 6.338802310000e-12, 6.334401750000e-12, 
	3.925120210000e-12, 2.404882720000e-12, 2.530769000000e-12, 3.794833370000e-12};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST(DLRTests, GetLambdas)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    std::vector<double> lambdas = library.getNuclide("Pu239")->getLambdas();

	std::vector<double> ref {1.248109990000e-02, 2.994666990000e-02, 1.071553010000e-01, 
	3.176192940000e-01, 1.352380040000e+00, 1.069116020000e+01};

    EXPECT_TRUE(Numerics::areVectorsEqual(lambdas, ref, 1.0E-9));
}

TEST(DLRTests, GetCrossSectionMatrixSetL0NonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"H1_H2O"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    size_t size = library.getNuclide("H1_H2O")->getXSMatrixSet(XSMatrixKind::SCAT00).getSize();	

    EXPECT_EQ(size, 6);
}

TEST(DLRTests, GetCrossSectionMatrixSetL1NonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"H1_H2O"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    size_t size = library.getNuclide("H1_H2O")->getXSMatrixSet(XSMatrixKind::SCAT01).getSize();	

    EXPECT_EQ(size, 6);
}

TEST(DLRTests, GetCrossSectionMatrixSetL2NonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"H1_H2O"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    size_t size = library.getNuclide("H1_H2O")->getXSMatrixSet(XSMatrixKind::SCAT02).getSize();	

    EXPECT_EQ(size, 6);
}

TEST(DLRTests, GetCrossSectionMatrixSetL3NonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"H1_H2O"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    size_t size = library.getNuclide("H1_H2O")->getXSMatrixSet(XSMatrixKind::SCAT03).getSize();	

    EXPECT_EQ(size, 6);
}

TEST(DLRTests, GetCrossSectionMatrixSetL0Resonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    size_t size = library.getNuclide("Pu239")->getXSMatrixSet(XSMatrixKind::SCAT00).getSize();	

    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetCrossSectionMatrixSetL1Resonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    size_t size = library.getNuclide("Pu239")->getXSMatrixSet(XSMatrixKind::SCAT01).getSize();	

    EXPECT_EQ(size, 95);
}

TEST(DLRTests, GetCrossSectionMatrixL0NonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"H1_H2O"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    Eigen::MatrixXd mat = library.getNuclide("H1_H2O")->getXSMatrixSet(XSMatrixKind::SCAT00).getXSMatrix(5.00000000E+02, Numerics::DINF).getValues();
	std::vector<double> vec = Numerics::eigenVecTOStdVec(mat.diagonal(1)); 

	std::vector<double> ref {6.883744900000e-02, 4.055498910000e-02, 1.013163030000e-01, 
	9.724315260000e-02, 1.468839050000e-01, 1.694681050000e-01, 1.044330000000e-01, 1.210964990000e-01, 
	2.497445940000e-01, 2.691532970000e-01, 3.088020980000e-01, 3.517333870000e-01, 2.088197020000e-01, 
	2.389791010000e-01, 4.829565880000e-01, 5.019624230000e-01, 2.942464950000e-01, 3.355380000000e-01, 
	3.541243970000e-01, 3.738617900000e-01, 3.937926890000e-01, 1.131834030000e+00, 4.220669870000e-01, 
	5.145782830000e-01, 5.423709750000e-01, 5.721907020000e-01, 1.642192010000e+00, 6.095988750000e-01, 
	7.393177750000e-01, 2.127753020000e+00, 2.694916010000e+00, 8.653280140000e-01, 2.991733070000e+00, 
	2.033988000000e+00, 2.305538890000e+00, 3.483594890000e+00, 1.296676990000e+00, 3.247550960000e+00, 
	9.743509890000e-01, 1.596794960000e+00, 5.506048200000e+00, 1.419201970000e+00, 4.571987150000e+00, 
	2.953299050000e+00, 3.150810000000e+00, 4.555425170000e+00, 1.612604020000e+00, 5.551917080000e+00, 
	8.185305000000e-01, 6.426856040000e+00, 1.574717040000e+00, 4.970698830000e+00, 8.513321280000e-01, 
	2.750081060000e+00, 3.410284040000e+00, 1.749835970000e+00, 3.503191950000e+00, 1.753152010000e+00, 
	6.381822110000e+00, 3.042315010000e+00, 3.348673110000e+00, 6.093376160000e+00, 4.564762120000e+00, 
	1.399132010000e+00, 6.459274770000e+00, 2.936254980000e+00, 1.908854010000e+00, 3.510272030000e+00, 
	1.338294030000e+00, 1.269850970000e+00, 1.120376940000e+00, 2.332988020000e+00, 1.388404970000e+00, 
	1.874202970000e+00, 1.851387980000e+00, 1.851552010000e+00, 1.851724030000e+00, 1.851899030000e+00, 
	2.710944890000e+00, 3.443108080000e+00, 2.582899090000e+00, 3.444736000000e+00, 2.180059910000e+00, 
	1.390841960000e+00, 1.877758030000e+00, 1.855164050000e+00, 3.534724950000e+00, 2.454298020000e+00, 
	1.083757040000e+00, 3.613332030000e+00, 5.825092200000e-01, 3.130494120000e+00, 4.670931990000e-01, 
	3.377502920000e+00, 3.440298140000e-01, 1.104313020000e+00, 4.746120870000e-01, 1.753255960000e+00, 
	2.030280110000e+00, 3.203321100000e-01, 1.019919040000e+00, 1.093894960000e+00, 1.129030940000e+00, 
	1.121286990000e+00, 1.180147050000e+00, 1.170711990000e+00, 1.376531960000e+00, 4.315727060000e-01, 
	6.759383080000e-01, 1.283457990000e+00, 6.171507840000e-01, 7.755128150000e-01, 1.312780020000e+00, 
	1.328408000000e+00, 4.620741010000e-01, 7.101570960000e-01, 3.707804980000e-01, 4.390471880000e-01, 
	7.721205950000e-01, 7.084571120000e-01, 3.207153980000e-01, 5.479075910000e-01, 7.576804760000e-01, 
	3.383274080000e-01, 5.445790890000e-01, 7.488527890000e-01, 6.535820960000e-01, 6.769745950000e-01, 
	1.531851050000e+00, 3.372462990000e-01, 2.042181020000e+00, 3.571211100000e-01, 2.703464030000e+00, 
	2.727325920000e+00, 3.209131960000e+00, 1.795128940000e+00, 8.516064880000e-01, 3.009614940000e+00, 
	1.953310970000e+00, 6.940763000000e-01, 3.164061070000e+00, 2.239815950000e+00, 5.641934280000e-01, 
	1.887099980000e+00, 2.154339080000e+00, 3.217237000000e+00, 2.993918900000e+00, 3.730993990000e+00, 
	1.468104960000e+00, 3.839663980000e+00, 3.727631090000e+00, 1.544978020000e+00, 5.099802970000e+00, 
	3.936886070000e+00, 1.885483980000e+00, 5.916197780000e+00, 1.421121000000e+00, 5.580854890000e+00, 
	4.663660050000e+00, 4.846532820000e+00, 5.532897000000e+00, 5.599832060000e+00, 4.998246190000e+00, 
	6.009489060000e+00, 6.709751130000e+00, 7.575026990000e+00, 8.632983210000e+00, 6.979266170000e+00, 
	6.306743140000e+00, 8.376496320000e+00, 1.071757030000e+01};

    EXPECT_TRUE(Numerics::areVectorsEqual(vec, ref, 1.0E-9));
}

TEST(DLRTests, GetCrossSectionMatrixL1NonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"H1_H2O"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    Eigen::MatrixXd mat = library.getNuclide("H1_H2O")->getXSMatrixSet(XSMatrixKind::SCAT01).getXSMatrix(5.00000000E+02, Numerics::DINF).getValues();
	std::vector<double> vec = Numerics::eigenVecTOStdVec(mat.diagonal(1)); 

	std::vector<double> ref {6.489767130000e-02, 3.876321020000e-02, 9.556920080000e-02, 
	9.081669150000e-02, 1.358737050000e-01, 1.553968940000e-01, 9.785878660000e-02, 1.154944000000e-01, 
	2.326238010000e-01, 2.456603050000e-01, 2.815468010000e-01, 3.204008940000e-01, 1.945832070000e-01, 
	2.276414040000e-01, 4.493596850000e-01, 4.564000960000e-01, 2.737650870000e-01, 3.195126060000e-01, 
	3.372046050000e-01, 3.559769990000e-01, 3.749485020000e-01, 1.029392000000e+00, 3.846805990000e-01, 
	4.901266100000e-01, 5.165830250000e-01, 5.450015070000e-01, 1.494078040000e+00, 5.555511710000e-01, 
	7.041962150000e-01, 1.935871010000e+00, 2.295732980000e+00, 7.726190090000e-01, 2.721762900000e+00, 
	1.809569950000e+00, 2.096081970000e+00, 3.096779110000e+00, 1.180439950000e+00, 2.998399020000e+00, 
	9.071367980000e-01, 1.532878040000e+00, 4.902916910000e+00, 1.264572020000e+00, 4.158977990000e+00, 
	2.624994040000e+00, 2.863401890000e+00, 4.048200130000e+00, 1.467093940000e+00, 4.995993140000e+00, 
	7.456237080000e-01, 5.792205810000e+00, 1.402308940000e+00, 4.521532060000e+00, 7.838571070000e-01, 
	2.619478940000e+00, 3.135011910000e+00, 1.627753970000e+00, 3.258752110000e+00, 1.630833980000e+00, 
	5.682460780000e+00, 2.646286960000e+00, 3.042926070000e+00, 5.300074100000e+00, 3.868566040000e+00, 
	1.273177030000e+00, 5.774487970000e+00, 2.558875080000e+00, 1.775517940000e+00, 3.258836030000e+00, 
	1.252423050000e+00, 1.226343990000e+00, 1.086379050000e+00, 2.230770110000e+00, 1.322211030000e+00, 
	1.795501950000e+00, 1.763005970000e+00, 1.763162020000e+00, 1.763326050000e+00, 1.763492940000e+00, 
	2.551148890000e+00, 3.165163990000e+00, 2.374397990000e+00, 3.166661020000e+00, 2.015911100000e+00, 
	1.324534060000e+00, 1.798908000000e+00, 1.766602990000e+00, 3.288079980000e+00, 2.260601040000e+00, 
	1.032209040000e+00, 3.395196910000e+00, 5.509179830000e-01, 2.982491970000e+00, 4.316520990000e-01, 
	3.104358910000e+00, 3.159787060000e-01, 1.050454020000e+00, 4.507187900000e-01, 1.644541030000e+00, 
	1.849128960000e+00, 2.973352970000e-01, 9.656671290000e-01, 1.021662000000e+00, 1.049039010000e+00, 
	1.039018990000e+00, 1.090407010000e+00, 1.078403000000e+00, 1.260686990000e+00, 3.994551000000e-01, 
	6.331264970000e-01, 1.184175010000e+00, 5.679115060000e-01, 7.187880280000e-01, 1.200641990000e+00, 
	1.199517010000e+00, 4.222078030000e-01, 6.571655870000e-01, 3.444632890000e-01, 4.121862050000e-01, 
	7.163565750000e-01, 6.494324210000e-01, 2.974832950000e-01, 5.122073890000e-01, 6.983166930000e-01, 
	3.127985000000e-01, 5.079330800000e-01, 6.892431970000e-01, 5.968534950000e-01, 6.176586750000e-01, 
	1.366598960000e+00, 3.022925850000e-01, 1.811092970000e+00, 3.153370920000e-01, 2.347152950000e+00, 
	2.230747940000e+00, 2.533950090000e+00, 1.414273980000e+00, 7.004591230000e-01, 2.405098920000e+00, 
	1.490949030000e+00, 5.562676190000e-01, 2.454881910000e+00, 1.617429020000e+00, 4.358280000000e-01, 
	1.518295050000e+00, 1.604060050000e+00, 2.196074010000e+00, 1.901736020000e+00, 2.220860960000e+00, 
	9.266765120000e-01, 2.433495040000e+00, 2.080807920000e+00, 9.429286720000e-01, 2.930336950000e+00, 
	1.931980970000e+00, 1.053738000000e+00, 3.088360070000e+00, 7.539879080000e-01, 3.020394090000e+00, 
	2.115374090000e+00, 2.135407920000e+00, 2.304400920000e+00, 2.191863060000e+00, 1.970873950000e+00, 
	2.330033060000e+00, 2.351171020000e+00, 2.312143090000e+00, 2.152879000000e+00, 1.566761020000e+00, 
	1.544770000000e+00, 1.962419990000e+00, 1.698181990000e+00};

    EXPECT_TRUE(Numerics::areVectorsEqual(vec, ref, 1.0E-9));
}

TEST(DLRTests, GetCrossSectionMatrixL2NonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"H1_H2O"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    Eigen::MatrixXd mat = library.getNuclide("H1_H2O")->getXSMatrixSet(XSMatrixKind::SCAT02).getXSMatrix(5.00000000E+02, Numerics::DINF).getValues();
	std::vector<double> vec = Numerics::eigenVecTOStdVec(mat.diagonal(1)); 

	std::vector<double> ref {5.742473160000e-02, 3.532680120000e-02, 8.466509730000e-02, 
	7.872983810000e-02, 1.153284010000e-01, 1.293434950000e-01, 8.546549830000e-02, 1.047471990000e-01, 
	2.004785980000e-01, 2.022978070000e-01, 2.312747990000e-01, 2.626420860000e-01, 1.678453980000e-01, 
	2.059078960000e-01, 3.863210980000e-01, 3.725081980000e-01, 2.353359010000e-01, 2.887994950000e-01, 
	3.047777120000e-01, 3.217019140000e-01, 3.388352990000e-01, 8.413115740000e-01, 3.159514960000e-01, 
	4.432567060000e-01, 4.671527150000e-01, 4.928844870000e-01, 1.222090960000e+00, 4.561955030000e-01, 
	6.368734840000e-01, 1.583508970000e+00, 1.601079940000e+00, 6.056641940000e-01, 2.226025100000e+00, 
	1.404332040000e+00, 1.710443020000e+00, 2.398650880000e+00, 9.669064880000e-01, 2.534306050000e+00, 
	7.812039850000e-01, 1.409543040000e+00, 3.818542960000e+00, 9.864494200000e-01, 3.400625940000e+00, 
	2.032511950000e+00, 2.334378000000e+00, 3.132941960000e+00, 1.199893950000e+00, 3.986005070000e+00, 
	6.121646170000e-01, 4.642941000000e+00, 1.092321990000e+00, 3.696800950000e+00, 6.589919920000e-01, 
	2.369520900000e+00, 2.623395920000e+00, 1.398720030000e+00, 2.800168040000e+00, 1.401357050000e+00, 
	4.425111770000e+00, 1.945721980000e+00, 2.480180030000e+00, 3.896758080000e+00, 2.661705970000e+00, 
	1.042111990000e+00, 4.540266990000e+00, 1.890362980000e+00, 1.525305990000e+00, 2.787844900000e+00, 
	1.090608950000e+00, 1.141939040000e+00, 1.020190000000e+00, 2.034315110000e+00, 1.195391060000e+00, 
	1.643895030000e+00, 1.593618040000e+00, 1.593758940000e+00, 1.593907000000e+00, 1.594058040000e+00, 
	2.248115060000e+00, 2.648585080000e+00, 1.986883040000e+00, 2.649840120000e+00, 1.709375980000e+00, 
	1.197492960000e+00, 1.647014980000e+00, 1.596871970000e+00, 2.825360060000e+00, 1.900024060000e+00, 
	9.335107210000e-01, 2.982980970000e+00, 4.909692110000e-01, 2.699573040000e+00, 3.666614890000e-01, 
	2.607275010000e+00, 2.650215030000e-01, 9.493482110000e-01, 4.059545100000e-01, 1.443240050000e+00, 
	1.522397990000e+00, 2.553246020000e-01, 8.649523850000e-01, 8.890966180000e-01, 9.030323030000e-01, 
	8.894112710000e-01, 9.277920130000e-01, 9.118500950000e-01, 1.053087950000e+00, 3.415628970000e-01, 
	5.553364160000e-01, 1.006144050000e+00, 4.799130860000e-01, 6.170759800000e-01, 1.001896980000e+00, 
	9.739711880000e-01, 3.520385030000e-01, 5.632650260000e-01, 2.977904980000e-01, 3.642486930000e-01, 
	6.178399920000e-01, 5.460023280000e-01, 2.565797870000e-01, 4.490149920000e-01, 5.944569110000e-01, 
	2.680411930000e-01, 4.434008000000e-01, 5.853204730000e-01, 4.985862080000e-01, 5.154523850000e-01, 
	1.086809040000e+00, 2.431910930000e-01, 1.425366040000e+00, 2.460640070000e-01, 1.767223000000e+00, 
	1.465482000000e+00, 1.538359050000e+00, 8.624116780000e-01, 4.770500960000e-01, 1.542896030000e+00, 
	8.634809260000e-01, 3.659895960000e-01, 1.515228990000e+00, 8.490782980000e-01, 2.737593950000e-01, 
	1.044180990000e+00, 9.430363180000e-01, 1.074728010000e+00, 8.052434920000e-01, 8.412641290000e-01, 
	4.362784030000e-01, 1.193354010000e+00, 8.005855080000e-01, 4.648694100000e-01, 1.329293010000e+00, 
	6.499325040000e-01, 4.913814070000e-01, 1.315160990000e+00, 3.421317930000e-01, 1.440196990000e+00, 
	7.457516190000e-01, 7.382631900000e-01, 7.380623820000e-01, 6.420704130000e-01, 6.183050270000e-01, 
	7.443885210000e-01, 6.443386080000e-01, 5.005297060000e-01, 2.994430070000e-01, 2.159259020000e-01, 
	3.773635030000e-01, 5.339012150000e-01, 3.447180090000e-01};

    EXPECT_TRUE(Numerics::areVectorsEqual(vec, ref, 1.0E-9));
}

TEST(DLRTests, GetCrossSectionMatrixL3NonResonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"H1_H2O"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    Eigen::MatrixXd mat = library.getNuclide("H1_H2O")->getXSMatrixSet(XSMatrixKind::SCAT03).getXSMatrix(5.00000000E+02, Numerics::DINF).getValues();
	std::vector<double> vec = Numerics::eigenVecTOStdVec(mat.diagonal(1)); 

	std::vector<double> ref {4.717973990000e-02, 3.052468040000e-02, 6.970927120000e-02, 
	6.240085140000e-02, 8.795432750000e-02, 9.510169920000e-02, 6.865470110000e-02, 8.972281220000e-02, 
	1.571857040000e-01, 1.456252040000e-01, 1.656540930000e-01, 1.873272060000e-01, 1.318154040000e-01, 
	1.755664940000e-01, 3.015193940000e-01, 2.633483110000e-01, 1.836404060000e-01, 2.459374070000e-01, 
	2.595250010000e-01, 2.738732100000e-01, 2.884423140000e-01, 5.977874990000e-01, 2.267519980000e-01, 
	3.778289850000e-01, 3.981530070000e-01, 4.201320110000e-01, 8.698028920000e-01, 3.272542950000e-01, 
	5.428935290000e-01, 1.127107980000e+00, 7.854257820000e-01, 3.967905040000e-01, 1.583956000000e+00, 
	8.950874810000e-01, 1.208708050000e+00, 1.522166970000e+00, 6.901329160000e-01, 1.917899010000e+00, 
	6.122097970000e-01, 1.235402940000e+00, 2.466047050000e+00, 6.392961140000e-01, 2.418530940000e+00, 
	1.288766030000e+00, 1.646407960000e+00, 1.984292980000e+00, 8.538153170000e-01, 2.702500100000e+00, 
	4.402407110000e-01, 3.190666910000e+00, 7.056564090000e-01, 2.628777980000e+00, 4.950234000000e-01, 
	2.021497010000e+00, 1.946560030000e+00, 1.090685960000e+00, 2.183413030000e+00, 1.092728020000e+00, 
	2.856949090000e+00, 1.097617980000e+00, 1.748432040000e+00, 2.197945120000e+00, 1.254891990000e+00, 
	7.433406110000e-01, 2.993935110000e+00, 1.078966980000e+00, 1.188642980000e+00, 2.156094070000e+00, 
	8.712862130000e-01, 1.021657940000e+00, 9.253007170000e-01, 1.758820060000e+00, 1.018504020000e+00, 
	1.430449960000e+00, 1.357220050000e+00, 1.357339980000e+00, 1.357465980000e+00, 1.357594970000e+00, 
	1.832857010000e+00, 1.965188030000e+00, 1.474228020000e+00, 1.966122030000e+00, 1.300444010000e+00, 
	1.020298960000e+00, 1.433166980000e+00, 1.359995010000e+00, 2.203042030000e+00, 1.421659950000e+00, 
	7.959907050000e-01, 2.421508070000e+00, 4.087171850000e-01, 2.306467060000e+00, 2.824977040000e-01, 
	1.971725940000e+00, 2.000855060000e-01, 8.129240870000e-01, 3.457544150000e-01, 1.177940960000e+00, 
	1.111073020000e+00, 2.012148950000e-01, 7.314813730000e-01, 7.168297770000e-01, 7.150861020000e-01, 
	6.980484130000e-01, 7.212088110000e-01, 7.017862800000e-01, 7.942795160000e-01, 2.686085100000e-01, 
	4.558899100000e-01, 7.836514120000e-01, 3.705526890000e-01, 4.898676870000e-01, 7.583938840000e-01, 
	7.036470170000e-01, 2.670058010000e-01, 4.479408860000e-01, 2.403583970000e-01, 3.046652970000e-01, 
	4.973143040000e-01, 4.213702980000e-01, 2.068424970000e-01, 3.715400100000e-01, 4.694659110000e-01, 
	2.141027000000e-01, 3.650254910000e-01, 4.613058870000e-01, 3.826147020000e-01, 3.952980940000e-01, 
	7.686275840000e-01, 1.760427950000e-01, 9.964718820000e-01, 1.699301000000e-01, 1.150742050000e+00, 
	7.268849020000e-01, 6.485952140000e-01, 3.813400860000e-01, 2.733407910000e-01, 8.020215030000e-01, 
	3.677645920000e-01, 2.090408060000e-01, 7.880682950000e-01, 3.195028900000e-01, 1.552255000000e-01, 
	6.838238240000e-01, 4.888857010000e-01, 4.007253940000e-01, 2.194383000000e-01, 1.764983980000e-01, 
	1.853511040000e-01, 5.508363840000e-01, 2.295127060000e-01, 2.270417060000e-01, 5.780513880000e-01, 
	1.401122060000e-01, 2.254666980000e-01, 5.265929100000e-01, 1.539034990000e-01, 6.907625200000e-01, 
	1.936780960000e-01, 1.847193990000e-01, 1.494196950000e-01, 9.553685780000e-02, 1.356823000000e-01, 
	1.878943000000e-01, 1.066090990000e-01, 9.836249980000e-03, -9.808535870000e-02, -5.547484010000e-02, 
	8.671393990000e-02, 1.701948940000e-01, 9.301538020000e-02};

    EXPECT_TRUE(Numerics::areVectorsEqual(vec, ref, 1.0E-9));
}

TEST(DLRTests, GetCrossSectionMatrixL0Resonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    Eigen::MatrixXd mat = library.getNuclide("Pu239")->getXSMatrixSet(XSMatrixKind::SCAT00).getXSMatrix(9.00000000E+02, 1.00279404E+02).getValues();
	std::vector<double> vec = Numerics::eigenVecTOStdVec(mat.diagonal(1)); 

	std::vector<double> ref {1.451736240000e-01, 1.019773860000e-01, 2.006407530000e-01, 
	1.530127230000e-01, 1.883632240000e-01, 1.683332030000e-01, 1.067039070000e-01, 1.456258150000e-01, 
	1.831201170000e-01, 1.309466660000e-01, 1.325839160000e-01, 1.484079510000e-01, 1.570227300000e-01, 
	3.052425380000e-01, 3.803117280000e-01, 2.731451090000e-01, 2.205147300000e-01, 4.098471110000e-01, 
	4.338147640000e-01, 4.634223580000e-01, 5.066210030000e-01, 6.166875360000e-01, 2.598617370000e-01, 
	7.314467430000e-01, 7.240201230000e-01, 7.070741650000e-01, 9.906740780000e-01, 3.402704300000e-01, 
	6.418282990000e-01, 1.101453780000e+00, 6.361072060000e-01, 3.044146300000e-01, 1.073066773210e+00, 
	4.113882310500e-01, 6.696504804000e-01, 7.260544296000e-01, 4.024783740000e-01, 1.222176747800e+00, 
	4.547332448000e-01, 1.367027015500e+00, 1.296898147400e+00, 3.032666973000e-01, 9.663469407000e-01, 
	3.328319244000e-01, 4.985219040000e-01, 5.114319478000e-01, 3.515278493000e-01, 1.061812567600e+00, 
	2.897725442000e-01, 2.058091655000e+00, 2.420940991000e-01, 8.888262738000e-01, 3.066577315000e-01, 
	2.075247230000e+00, 5.936549004000e-01, 4.535804951000e-01, 9.771516220000e-01, 5.773313940000e-01, 
	9.283642190000e-01, 2.396582137000e-01, 4.413653204000e-01, 4.685485935000e-01, 2.985539880000e-01, 
	2.586000858000e-01, 1.149093954000e+00, 2.841535505000e-01, 7.930636730000e-01, 7.467914370000e-01, 
	2.757542430000e-01, 5.725546930000e-01, 8.306076480000e-01, 1.466062134300e+00, 3.743681997000e-01, 
	8.812800253000e-01, 7.222095739000e-01, 7.721359687400e-01, 8.713312035000e-01, 7.422648218000e-01, 
	8.743062880000e-01, 5.563329356000e-01, 3.384859560000e-01, 2.814207976000e-01, 1.820214100000e-01, 
	3.936195005000e-01, 8.323827905000e-01, 7.205706530000e-01, 2.043632420000e-01, 3.101555838000e-01, 
	4.630534202000e-01, 1.139277118900e+00, 3.410682716000e-01, 2.149967928000e+00, 4.708454343000e-01, 
	3.287013356000e+00, 3.713068480000e-01, 3.870400910000e+00, 1.615419980000e+00, 4.089980130000e+00, 
	1.651711940000e+00, 6.341552140000e-01, 3.855832100000e+00, 2.766374110000e+00, 2.509978060000e+00, 
	2.433695080000e+00, 2.483650920000e+00, 2.406210900000e+00, 2.558996920000e+00, 1.192617060000e+00, 
	2.664026020000e+00, 3.540606020000e+00, 1.715270040000e+00, 2.653043030000e+00, 3.363480090000e+00, 
	2.541544910000e+00, 1.275097010000e+00, 2.494185920000e+00, 1.304685950000e+00, 1.504909990000e+00, 
	2.662411930000e+00, 2.337883950000e+00, 1.076972960000e+00, 1.813207030000e+00, 2.521511080000e+00, 
	1.118790030000e+00, 1.750404000000e+00, 2.432555910000e+00, 2.081724880000e+00, 2.152854920000e+00, 
	3.798012020000e+00, 8.869063850000e-01, 4.691595080000e+00, 8.055304290000e-01, 4.995463850000e+00, 
	2.052026990000e+00, 1.893211960000e+00, 1.545416950000e+00, 1.665307040000e+00, 4.801681040000e+00, 
	2.298609020000e+00, 1.484688040000e+00, 6.024712090000e+00, 3.096613880000e+00, 1.272531030000e+00, 
	4.458773140000e+00, 4.129217150000e+00, 3.467207910000e+00, 1.537727950000e+00, 1.343158010000e+00, 
	7.206603880000e-01, 2.055751090000e+00, 1.589846010000e+00, 8.017141220000e-01, 2.462730880000e+00, 
	1.505851980000e+00, 8.718969230000e-01, 2.495007990000e+00, 5.958036180000e-01, 2.369786980000e+00, 
	1.625079990000e+00, 1.607900980000e+00, 1.698585990000e+00, 1.583173990000e+00, 1.396373030000e+00, 
	1.627766970000e+00, 1.636700030000e+00, 1.623535990000e+00, 1.564512970000e+00, 1.171394940000e+00, 
	1.139394040000e+00, 1.473531960000e+00, 1.409037950000e+00};

    EXPECT_TRUE(Numerics::areVectorsEqual(vec, ref, 1.0E-9));
}

TEST(DLRTests, GetCrossSectionMatrixL1Resonant)
{	
    Library library;
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
	library.setXSLibraryPath(refLibPath);

    std::vector<std::string> nucVec = {"Pu239"};
	std::vector < std::shared_ptr<Nuclide> > nuclides = library.readNuclides(nucVec);
    Eigen::MatrixXd mat = library.getNuclide("Pu239")->getXSMatrixSet(XSMatrixKind::SCAT01).getXSMatrix(9.00000000E+02, 1.00279404E+02).getValues();
	std::vector<double> vec = Numerics::eigenVecTOStdVec(mat.diagonal(1)); 

	//PrintFuncs::createCppVector(vec, "%13.12e");

	std::vector<double> ref {5.518682670000e-02, 3.594385090000e-02, 6.433157620000e-02, 
	4.009336610000e-02, 3.918724130000e-02, 2.814282100000e-02, 1.758809200000e-02, 2.552001920000e-02, 
	3.354626150000e-02, 2.366414110000e-02, 2.222497200000e-02, 1.915073390000e-02, 1.226634440000e-02, 
	1.581882500000e-02, 1.400793440000e-02, 7.254477590000e-03, 3.868573810000e-03, 5.558215550000e-03, 
	9.505683560000e-03, 1.438424270000e-02, 1.915855520000e-02, 3.012711370000e-02, 1.569265500000e-02, 
	4.804251720000e-02, 3.929188850000e-02, 2.813378350000e-02, 2.884934280000e-02, -1.744213860000e-03, 
	-4.957551140000e-02, -2.713896890000e-02, -1.126980040000e-02, -3.220964600000e-02, -1.469738438500e-01, 
	-5.963118010000e-02, -9.926181848000e-02, -1.091014075300e-01, -7.832333001000e-02, -2.324890991000e-01, 
	-1.076018094200e-01, -4.001964680000e-01, -2.700890434000e-01, -7.279444673000e-02, -2.931626086000e-01, 
	-1.019013652200e-01, -1.538463821000e-01, -1.573451976000e-01, -1.080789183000e-01, -3.261948604000e-01, 
	-9.046374290000e-02, -6.429629397000e-01, -7.558054200000e-02, -2.843421532000e-01, -9.559595030000e-02, 
	-5.915112650000e-01, -1.809258683000e-01, -1.355457305000e-01, -3.074934780000e-01, -1.566669570000e-01, 
	-2.709394540000e-01, -6.182240670000e-02, -1.309241315000e-01, -1.322422902000e-01, -7.388672630000e-02, 
	-7.406140900000e-02, -3.319916430000e-01, -7.029927160000e-02, -1.886592210000e-01, -2.153754983000e-01, 
	-7.244694990000e-02, -1.387589120000e-01, -2.320300043000e-01, -4.498614672000e-01, -1.188792935100e-01, 
	-2.940456620600e-01, -2.389705906700e-01, -2.562559122900e-01, -2.824879657000e-01, -2.348762560000e-01, 
	-2.203991120000e-01, -1.811456680800e-01, -8.491420750000e-02, -6.831857940000e-02, -2.458485900000e-02, 
	-1.166961568000e-01, -2.645284813000e-01, -2.151153234000e-01, -2.806534600000e-02, -9.696932710000e-02, 
	-1.456031406000e-01, -3.578677809000e-01, -1.061623453000e-01, -6.678296180000e-01, -7.233757990000e-02, 
	-5.095177590000e-01, -4.095524270000e-02, -3.866418900000e-01, -1.529067010000e-01, -5.440143940000e-01, 
	-3.854624030000e-01, -6.014151130000e-02, -9.990709280000e-02, -3.732270000000e-01, -3.970383110000e-01, 
	-4.030098920000e-01, -4.109733100000e-01, -4.005039040000e-01, -4.420089130000e-01, -7.671771200000e-02, 
	1.389966010000e-01, -2.736246880000e-01, -1.126085970000e-01, -7.772113200000e-03, -2.940747140000e-01, 
	-3.678140940000e-01, -3.694618120000e-02, 1.670649050000e-01, 1.383713930000e-01, 2.594357130000e-01, 
	2.871530060000e-01, 1.052600000000e-01, 1.316640970000e-01, 3.096651140000e-01, 2.416004990000e-01, 
	1.343978940000e-01, 3.015537860000e-01, 2.544155120000e-01, 1.432067010000e-01, 1.745263930000e-01, 
	-1.400800940000e-01, 1.479243020000e-02, -9.002155070000e-02, -1.358378030000e-02, -2.451359930000e-01, 
	-4.154787960000e-01, -3.851478100000e-01, -2.696813050000e-01, -7.198078190000e-02, -3.726347090000e-01, 
	-3.487651050000e-01, -3.724806010000e-03, -2.294269060000e-01, -4.373485150000e-01, 1.951167920000e-02, 
	4.631780980000e-01, -8.374138180000e-02, -4.013685880000e-01, -2.493301030000e-01, -2.067680950000e-01, 
	-2.817790020000e-02, -4.164253920000e-02, -1.461952030000e-01, 1.101872980000e-02, -2.659079990000e-02, 
	-1.328690050000e-01, 1.991955940000e-02, -1.544716950000e-02, 1.845045950000e-02, 1.339323970000e-01, 
	-6.523542850000e-02, -5.249124020000e-02, -6.311765310000e-02, -6.479769950000e-02, -1.590156000000e-02, 
	1.067129990000e-02, -2.055820080000e-02, -5.781238150000e-02, -9.999395910000e-02, -6.598231940000e-02, 
	5.770838820000e-03, 3.010321040000e-02, -6.031832100000e-02};

    EXPECT_TRUE(Numerics::areVectorsEqual(vec, ref, 1.0E-9));
}

TEST(DLRTests, RemoveLibrary)
{	
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
    EXPECT_TRUE(File::removeFile(refLibPath));
}