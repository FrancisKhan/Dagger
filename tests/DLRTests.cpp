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
    EXPECT_EQ(size, 10);
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

	std::vector<double> ref(172, 0.000000000000e+00);

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

	PrintFuncs::createCppVector(xs, "%13.12e");

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

	//PrintFuncs::createCppVector(lambdas, "%13.12e");

	std::vector<double> ref {1.248109990000e-02, 2.994666990000e-02, 1.071553010000e-01, 
	3.176192940000e-01, 1.352380040000e+00, 1.069116020000e+01};

    EXPECT_TRUE(Numerics::areVectorsEqual(lambdas, ref, 1.0E-9));
}

TEST(DLRTests, RemoveLibrary)
{	
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
    EXPECT_TRUE(File::removeFile(refLibPath));
}