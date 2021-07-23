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

TEST(DLRTests, RemoveLibrary)
{	
    std::string refLibPath = File::getPrePath() + "neutron_libraries/draglibendfb7r0.gz";
    EXPECT_TRUE(File::removeFile(refLibPath));
}