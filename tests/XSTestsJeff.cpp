#include "gtest/gtest.h"
#include "file_tools.h"
#include "network_tools.h"
#include "Library.h"
#include "additionalPrintFuncs.h"


class XSTestsJeff : public ::testing::Test 
{
 protected:
	static std::string* url_;
	static std::string* target_;
	static Library* library_;
	static std::vector<std::string>* nucVec_;
	static std::vector < std::shared_ptr<Nuclide> >* nuclides_;

  	static void SetUpTestSuite() 
	{
    	library_ = new Library;
		url_ = new std::string("http://www.polymtl.ca/merlin/downloads/libraries/ascii/draglibshem281_Jeff3.3.gz");
    	target_ =  new std::string(File::getPrePath() + "draglibshem281_Jeff3.3.gz");
		library_->downloadLibrary(*url_, *target_);
		library_->setXSLibraryPath(*target_);
		nucVec_ = new std::vector<std::string> {"U238"};
		nuclides_ = new std::vector < std::shared_ptr<Nuclide> > {library_->readNuclides(*nucVec_)};
  	}

	static void TearDownTestSuite() 
	{
    	delete library_;
		delete url_;
		delete target_;
		delete nucVec_;
		delete nuclides_;
    	library_ = nullptr;
		url_ = nullptr;
		target_ = nullptr;
		nucVec_ = nullptr;
		nuclides_ = nullptr;
  	}

	virtual void SetUp() {}
  	virtual void TearDown() {}
};

Library* XSTestsJeff::library_ = nullptr;
std::string* XSTestsJeff::url_ = nullptr;
std::string* XSTestsJeff::target_ = nullptr;
std::vector<std::string>* XSTestsJeff::nucVec_ = nullptr;
std::vector < std::shared_ptr<Nuclide> >* XSTestsJeff::nuclides_ = nullptr;

TEST_F(XSTestsJeff, GetNuclides)
{	
    size_t numberOfNuclides = library_->getNumberOfNuclidesRead();
    EXPECT_EQ(numberOfNuclides, 1);
}

TEST_F(XSTestsJeff, GetLibraryNuclides)
{	
    std::vector<std::string> nuclideVec = library_->getLibraryNuclides();

	std::vector<std::string> refVec {"Ag107", "Ag109", "Ag111", "Al27", 
    "Am241", "Am242", "Am242m", "Am243", "As75", "Au197", "B10", "B11", 
    "Ba134", "Ba135", "Ba136", "Ba137", "Ba138", "Ba140", "Be9", "Bi209", 
    "Bk249", "Br79", "Br81", "C0", "C0_GR", "Ca40", "Ca42", "Ca43", "Ca44", 
    "Ca46", "Ca48", "Cd106", "Cd108", "Cd110", "Cd111", "Cd112", "Cd113", 
    "Cd114", "Cd115m", "Cd116", "Ce140", "Ce141", "Ce142", "Ce143", 
    "Cf249", "Cf250", "Cf251", "Cf252", "Cf253", "Cl35", "Cl37", "Cm241", 
    "Cm242", "Cm243", "Cm244", "Cm245", "Cm246", "Cm247", "Cm248", "Co59", 
    "Cr50", "Cr51", "Cr52", "Cr53", "Cr54", "Cs133", "Cs134", "Cs135", 
    "Cs136", "Cs137", "Cu63", "Cu65", "DEPL-CHAIN", "Dy160", "Dy161", 
    "Dy162", "Dy163", "Dy164", "Dy165", "Er166", "Er167", "Er168", 
    "Er170", "Eu151", "Eu152", "Eu153", "Eu154", "Eu155","Eu156", "Eu157", 
    "F19", "Fe54", "Fe56", "Fe57", "Fe58", "Ga69", "Ga71", "Gd152", 
    "Gd154", "Gd155", "Gd156", "Gd157", "Gd158", "Gd160", "Ge72", "Ge73", 
    "Ge74", "Ge76", "H1", "H1_CH2", "H1_H2O", "H1_ZRH", "H2", "H2_D2O", 
    "H3", "He3", "He4", "Hf174", "Hf176", "Hf177", "Hf178", "Hf179", 
    "Hf180", "Ho165", "I127", "I129", "I130", "I131", "I135", "In113", 
    "In115", "K39", "K40", "K41", "Kr80", "Kr82", "Kr83", "Kr84", 
    "Kr85", "Kr86", "La138", "La139", "La140", "Li6", "Li7", "Lu176", 
    "Mg24", "Mg25", "Mg26", "Mn55", "Mo100", "Mo92", "Mo94", "Mo95", 
    "Mo96", "Mo97", "Mo98", "Mo99", "N14", "N15", "Na23", "Nb93", 
    "Nb94", "Nb95", "Nd142", "Nd143", "Nd144", "Nd145", "Nd146", "Nd147", 
    "Nd148", "Nd150", "Ni58", "Ni60", "Ni61", "Ni62", "Ni64", "Np236", 
    "Np237", "Np238", "Np239", "O16", "O17", "P31", "Pa231", "Pa233", 
    "Pb204", "Pb206", "Pb207", "Pb208", "Pd104", "Pd105", "Pd106", 
    "Pd107", "Pd108", "Pd110", "Pm147", "Pm148", "Pm148m", "Pm149", "Pm151", 
    "Pr141", "Pr142", "Pr143", "Pu236", "Pu237", "Pu238", "Pu239", 
    "Pu240", "Pu241", "Pu242", "Pu243", "Pu244", "Rb85", "Rb87", "Re187", 
    "Rh103", "Rh105", "Ru100", "Ru101", "Ru102", "Ru103", "Ru104", "Ru105", 
    "Ru106", "Ru99", "S32", "S33", "S34", "S36", "Sb121", "Sb123", 
    "Sb124", "Sb125", "Sb126", "Se76", "Se77", "Se78", "Se79", "Se80", 
    "Se82", "Si28", "Si29", "Si30", "Sm147", "Sm148", "Sm149", "Sm150", 
    "Sm151", "Sm152", "Sm153", "Sm154", "Sn112", "Sn114", "Sn115", 
    "Sn116", "Sn117", "Sn118", "Sn119", "Sn120", "Sn122", "Sn123", "Sn124", 
    "Sn125", "Sn126", "Sr86", "Sr87", "Sr88", "Sr89", "Sr90", "Ta181", 
    "Tb159", "Tb160", "Tc99", "Te122", "Te123", "Te124", "Te125", 
    "Te126", "Te127m", "Te128", "Te129m", "Te130", "Te131m", "Te132", 
    "Th230", "Th232", "Th233", "Ti46", "Ti47", "Ti48", "Ti49", "Ti50", 
    "U232", "U233", "U234", "U235", "U236", "U237", "U238", "V48", "V49", 
    "V50", "V51", "W182", "W183", "W184", "W186", "Xe128", "Xe129", "Xe130", 
    "Xe131", "Xe132", "Xe133", "Xe134", "Xe135", "Xe136", "Y89", "Y90", 
    "Y91", "Zn66", "Zn67", "Zn68", "Zn70", "Zr90", "Zr91", "Zr92", 
    "Zr93", "Zr94", "Zr95", "Zr96"};

    bool areEqual = std::equal(refVec.begin(), refVec.end(), nuclideVec.begin());
    EXPECT_TRUE(areEqual);
}


TEST_F(XSTestsJeff, GetTotalCrossSectionSetResonant)
{	
    size_t size = library_->getNuclide("U238")->getXSSet(XSKind::NTOT0).getSize();
    EXPECT_EQ(size, 95);
}

TEST_F(XSTestsJeff, GetTotalCrossSectionResonant)
{	
    std::vector<double> xs = library_->getNuclide("U238")->getXSSet(XSKind::NTOT0).getXSNoInterp(5.50000000e+02, 2.11442700E+03).getValues();

	std::vector<double> ref {6.029476170000e+00, 5.881498810000e+00, 5.768144130000e+00, 
	5.790030960000e+00, 5.937067990000e+00, 6.140167240000e+00, 6.392859940000e+00, 6.656351090000e+00, 
	6.943700790000e+00, 7.400411130000e+00, 7.822620870000e+00, 7.976419930000e+00, 7.904613020000e+00, 
	7.689349170000e+00, 7.436029910000e+00, 7.220180030000e+00, 7.054195880000e+00, 6.981239800000e+00, 
	6.964743140000e+00, 6.960277080000e+00, 6.994120120000e+00, 7.079311850000e+00, 7.214608190000e+00, 
	7.490795140000e+00, 7.912363050000e+00, 8.317371370000e+00, 8.598070140000e+00, 8.817614560000e+00, 
	9.032415390000e+00, 9.362133030000e+00, 9.812334060000e+00, 1.018651010000e+01, 1.053104970000e+01, 
	1.088920970000e+01, 1.121870990000e+01, 1.149349980000e+01, 1.166233979993e+01, 1.188170049985e+01, 
	1.215642020007e+01, 1.243334030014e+01, 1.272920010067e+01, 1.293625040037e+01, 1.312992999977e+01, 
	1.332325039892e+01, 1.345388020038e+01, 1.360724040083e+01, 1.373984959900e+01, 1.381394969896e+01, 
	1.387218010032e+01, 1.396143999971e+01, 1.398813990007e+01, 1.547315960114e+01, 1.509389990013e+01, 
	1.522796029878e+01, 1.538089959522e+01, 1.491407040013e+01, 1.571451050184e+01, 1.659783000151e+01, 
	1.539844969754e+01, 1.576979010190e+01, 2.077676091928e+01, 1.988874080888e+01, 2.377421081755e+01, 
	2.088392932096e+01, 2.750675956862e+01, 2.209551039943e+01, 2.067281989940e+01, 2.440073032906e+01, 
	1.370042979705e+01, 3.088681089071e+01, 1.823172001460e+01, 2.115653981378e+01, 2.392599019607e+01, 
	1.402314960135e+01, 1.634756990565e+01, 3.300529105078e+01, 1.915624990323e+01, 2.103848019998e+01, 
	4.136359901534e+01, 6.539716837039e+01, 1.217336030049e+01, 4.151966068538e+01, 8.152473952823e+01, 
	1.722468999946e+01, 7.740382906404e+01, 1.014798970001e+01, 1.241204019992e+01, 1.431854959989e+01, 
	1.741618919969e+01, 2.394488280862e+02, 7.463173859962e+00, 1.048773960012e+01, 1.435908979946e+01, 
	1.955607990000e+01, 2.176992990000e+01, 2.484507940000e+01, 3.114934920000e+01, 4.532788850000e+01, 
	6.961025240000e+01, 1.137780000000e+02, 2.328343960000e+02, 7.700623780000e+02, 2.741506100000e+03, 
	6.367414060000e+03, 2.641060060000e+03, 6.860238040000e+02, 1.663881070000e+02, 6.247089000000e+01, 
	3.096548080000e+01, 1.671954920000e+01, 9.333869930000e+00, 8.134860990000e+00, 6.854716780000e+00, 
	6.607109070000e+00, 6.703678130000e+00, 7.000299930000e+00, 7.102163790000e+00, 7.181916240000e+00, 
	7.361938000000e+00, 7.567536830000e+00, 7.733056070000e+00, 7.885723110000e+00, 8.101371770000e+00, 
	8.277697560000e+00, 8.321398740000e+00, 8.362700460000e+00, 8.416728020000e+00, 8.481490140000e+00, 
	8.587967870000e+00, 8.694229130000e+00, 8.834015850000e+00, 8.959670070000e+00, 9.003357890000e+00, 
	9.055213930000e+00, 9.106151580000e+00, 9.156287190000e+00, 9.200594900000e+00, 9.240388870000e+00, 
	9.637275700000e+00, 9.587693210000e+00, 9.498893740000e+00, 9.599293710000e+00, 1.052538010000e+01, 
	1.040087030000e+01, 1.065205000000e+01, 1.085649010000e+01, 1.107269950000e+01, 1.130513950000e+01, 
	1.169513030000e+01, 1.222885990000e+01, 1.283588980000e+01, 1.354901030000e+01, 1.430562970000e+01, 
	1.538910010000e+01, 1.783992960000e+01, 2.478993990000e+01, 4.131727980000e+01, 7.037507630000e+01, 
	1.168236010000e+02, 2.089049990000e+02, 3.944840090000e+02, 6.959465940000e+02, 1.111644040000e+03, 
	1.682441040000e+03, 2.496347900000e+03, 3.757621090000e+03, 5.445871090000e+03, 3.712372070000e+03, 
	2.441188960000e+03, 1.611215940000e+03, 1.038308960000e+03, 6.476494140000e+02, 3.638818970000e+02, 
	1.831851040000e+02, 9.402496340000e+01, 5.238943860000e+01, 3.255258180000e+01, 2.176635930000e+01, 
	1.621339990000e+01, 1.363572980000e+01, 1.180451010000e+01, 1.079411980000e+01, 1.031602000000e+01, 
	9.953874590000e+00, 9.763960840000e+00, 9.626824380000e+00, 9.522292140000e+00, 9.449649810000e+00, 
	9.338050840000e+00, 9.233957290000e+00, 9.141599660000e+00, 9.071522710000e+00, 9.144431110000e+00, 
	9.520883560000e+00, 9.052723880000e+00, 9.027511600000e+00, 9.038266180000e+00, 9.053281780000e+00, 
	9.073708530000e+00, 9.113916400000e+00, 9.163941380000e+00, 9.193201070000e+00, 9.204999920000e+00, 
	9.209576610000e+00, 9.212958340000e+00, 9.219652180000e+00, 9.226462360000e+00, 9.230675700000e+00, 
	9.236600880000e+00, 9.246878620000e+00, 9.266112330000e+00, 9.283451080000e+00, 9.293474200000e+00, 
	9.304021840000e+00, 9.317505840000e+00, 9.332994460000e+00, 9.349225040000e+00, 9.369789120000e+00, 
	9.393123630000e+00, 9.413064000000e+00, 9.429149630000e+00, 9.445143700000e+00, 9.457831380000e+00, 
	9.465126040000e+00, 9.474570270000e+00, 9.485477450000e+00, 9.495383260000e+00, 9.505557060000e+00, 
	9.516495700000e+00, 9.525351520000e+00, 9.530775070000e+00, 9.535091400000e+00, 9.538804050000e+00, 
	9.542232510000e+00, 9.545970920000e+00, 9.554496770000e+00, 9.563065530000e+00, 9.567014690000e+00, 
	9.570751190000e+00, 9.575080870000e+00, 9.580368040000e+00, 9.586526870000e+00, 9.593865390000e+00, 
	9.605040550000e+00, 9.623229030000e+00, 9.655099870000e+00, 9.698951720000e+00, 9.730148320000e+00, 
	9.749882700000e+00, 9.772492410000e+00, 9.799481390000e+00, 9.832232480000e+00, 9.868133540000e+00, 
	9.905947690000e+00, 9.941533090000e+00, 9.970927240000e+00, 1.000185590000e+01, 1.004026600000e+01, 
	1.008301540000e+01, 1.012862210000e+01, 1.017763710000e+01, 1.024819180000e+01, 1.033493610000e+01, 
	1.042076970000e+01, 1.050824830000e+01, 1.060574250000e+01, 1.071808820000e+01, 1.084307770000e+01, 
	1.097879030000e+01, 1.112609200000e+01, 1.128546240000e+01, 1.145733360000e+01, 1.164403440000e+01, 
	1.184840300000e+01, 1.211113740000e+01, 1.251037410000e+01, 1.309052850000e+01, 1.387199020000e+01, 
	1.494766520000e+01, 1.664204030000e+01, 2.127573010000e+01};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST_F(XSTestsJeff, GetCaptureCrossSectionSetResonant)
{	
    size_t size = library_->getNuclide("U238")->getXSSet(XSKind::NG).getSize();
    EXPECT_EQ(size, 95);
}

TEST_F(XSTestsJeff, GetCaptureCrossSectionResonant)
{	
    std::vector<double> xs = library_->getNuclide("U238")->getXSSet(XSKind::NG).getXSNoInterp(2.93000000E+02, 1.50000000E+00).getValues();

	std::vector<double> ref {5.643711770000e-04, 7.306690090000e-04, 1.015761980000e-03, 
	1.202126960000e-03, 1.128538050000e-03, 8.901382100000e-04, 5.739667100000e-04, 3.873856040000e-04, 
	3.726400030000e-04, 8.218010770000e-04, 2.797269960000e-03, 8.096413690000e-03, 1.754817930000e-02, 
	2.971009910000e-02, 4.454971850000e-02, 5.797261000000e-02, 7.238595190000e-02, 8.211775120000e-02, 
	8.635865900000e-02, 9.622917320000e-02, 1.124501970000e-01, 1.257881970000e-01, 1.214224990000e-01, 
	1.140479970000e-01, 1.129674990000e-01, 1.050202030000e-01, 1.021154000000e-01, 1.009657980000e-01, 
	1.008822020000e-01, 1.026417020000e-01, 1.071949010000e-01, 1.117213000000e-01, 1.173940970000e-01, 
	1.259761010000e-01, 1.364973040000e-01, 1.471266000000e-01, 1.488361026659e-01, 1.604961942228e-01, 
	1.798072927756e-01, 2.025223077075e-01, 2.362551056597e-01, 2.661110890499e-01, 2.994446163950e-01, 
	3.326415057652e-01, 3.535518991384e-01, 3.696408133955e-01, 3.832513961082e-01, 3.912284906891e-01, 
	3.975928992199e-01, 4.073436021068e-01, 4.377822992607e-01, 4.743037676907e-01, 4.749784277855e-01, 
	5.241611007458e-01, 4.995333333111e-01, 5.363708015809e-01, 5.194623287142e-01, 5.470844962031e-01, 
	5.860780826261e-01, 5.614734279605e-01, 5.114982369077e-01, 6.305629922536e-01, 6.209548781800e-01, 
	5.467393069255e-01, 5.337865758257e-01, 4.952673203455e-01, 4.731164979771e-01, 6.268390165273e-01, 
	8.773843020487e-01, 6.032949187597e-01, 6.247419898826e-01, 7.435563258451e-01, 5.433097376323e-01, 
	5.779736958010e-01, 5.911859764318e-01, 5.671670853871e-01, 6.376079565398e-01, 6.297904964488e-01, 
	1.028368110146e+00, 1.145393357256e+00, 3.695431820996e-01, 9.729152397268e-01, 1.787350848173e+00, 
	8.314585899616e-01, 1.819258939093e+00, 1.339144925244e-01, 1.393153916694e-01, 3.141433960202e-01, 
	5.321424584619e-01, 6.651443822546e+00, 5.564791962355e-01, 4.345537963501e-01, 1.177374005376e+00, 
	2.897998090000e+00, 3.744370940000e+00, 4.990163800000e+00, 7.749260900000e+00, 1.442455010000e+01, 
	2.641646000000e+01, 4.727967830000e+01, 8.788002010000e+01, 2.367606960000e+02, 1.258349980000e+03, 
	5.129301760000e+03, 1.282410030000e+03, 2.457510990000e+02, 9.206130980000e+01, 5.012105180000e+01, 
	2.847920990000e+01, 1.593531040000e+01, 7.561204910000e+00, 5.332249160000e+00, 3.210258960000e+00, 
	2.629970070000e+00, 1.554268000000e+00, 9.481887220000e-01, 8.494206070000e-01, 7.828783990000e-01, 
	6.616771220000e-01, 5.495383740000e-01, 4.798491900000e-01, 4.257695970000e-01, 3.667469920000e-01, 
	3.275843860000e-01, 3.196089860000e-01, 3.126094940000e-01, 3.041422960000e-01, 2.950403090000e-01, 
	2.828232050000e-01, 2.731175120000e-01, 2.659187020000e-01, 2.632367910000e-01, 2.635197040000e-01, 
	2.645699980000e-01, 2.666206060000e-01, 2.697541120000e-01, 2.735948860000e-01, 2.788830100000e-01, 
	6.351330280000e-01, 4.385921060000e-01, 3.111529950000e-01, 3.320105970000e-01, 1.005285020000e+00, 
	5.463216900000e-01, 6.407788990000e-01, 7.253859040000e-01, 8.204209210000e-01, 9.285408260000e-01, 
	1.121418000000e+00, 1.402956010000e+00, 1.743891950000e+00, 2.165447000000e+00, 2.632615090000e+00, 
	3.353607890000e+00, 4.990894790000e+00, 1.003300950000e+01, 2.261611940000e+01, 4.468796920000e+01, 
	7.634467320000e+01, 1.238570020000e+02, 2.002420040000e+02, 3.282062990000e+02, 5.444697270000e+02, 
	9.330435790000e+02, 1.674696040000e+03, 3.262850100000e+03, 6.176044920000e+03, 3.255733890000e+03, 
	1.668550050000e+03, 9.192072140000e+02, 5.334531250000e+02, 3.305513000000e+02, 2.080971070000e+02, 
	1.306062930000e+02, 8.053742980000e+01, 4.751491170000e+01, 2.873302080000e+01, 1.750987050000e+01, 
	1.129528050000e+01, 8.203102110000e+00, 5.845514770000e+00, 4.447789190000e+00, 3.733079910000e+00, 
	3.156693940000e+00, 2.835854050000e+00, 2.590920930000e+00, 2.396061900000e+00, 2.253719090000e+00, 
	2.021101950000e+00, 1.783189060000e+00, 1.537894960000e+00, 1.306064960000e+00, 1.173334960000e+00, 
	1.444808960000e+00, 8.726407290000e-01, 7.809740900000e-01, 7.130326030000e-01, 6.669852140000e-01, 
	6.212573050000e-01, 5.618749260000e-01, 5.117704870000e-01, 4.910205010000e-01, 4.841392040000e-01, 
	4.817248880000e-01, 4.799366890000e-01, 4.764494900000e-01, 4.732887150000e-01, 4.714539950000e-01, 
	4.688811000000e-01, 4.647127990000e-01, 4.582301970000e-01, 4.533852040000e-01, 4.509702920000e-01, 
	4.489467140000e-01, 4.467081130000e-01, 4.449441130000e-01, 4.439097050000e-01, 4.436199070000e-01, 
	4.446451070000e-01, 4.466046990000e-01, 4.490872030000e-01, 4.520390030000e-01, 4.549258950000e-01, 
	4.566160140000e-01, 4.591726060000e-01, 4.624516960000e-01, 4.654535060000e-01, 4.688706990000e-01, 
	4.729554950000e-01, 4.762445990000e-01, 4.782544080000e-01, 4.799227120000e-01, 4.815145130000e-01, 
	4.830037060000e-01, 4.846121970000e-01, 4.883274140000e-01, 4.922961000000e-01, 4.941374960000e-01, 
	4.958871900000e-01, 4.980311100000e-01, 5.006875990000e-01, 5.037822720000e-01, 5.075193050000e-01, 
	5.135372280000e-01, 5.237014890000e-01, 5.428379180000e-01, 5.715184810000e-01, 5.932118890000e-01, 
	6.075888280000e-01, 6.244291070000e-01, 6.452705860000e-01, 6.713286040000e-01, 7.007470130000e-01, 
	7.325752970000e-01, 7.632024290000e-01, 7.889441250000e-01, 8.164039250000e-01, 8.509324790000e-01, 
	8.898025750000e-01, 9.317588810000e-01, 9.773231740000e-01, 1.043576960000e+00, 1.125792030000e+00, 
	1.207782980000e+00, 1.291841030000e+00, 1.385949970000e+00, 1.494737030000e+00, 1.616075990000e+00, 
	1.748039960000e+00, 1.891443970000e+00, 2.046623950000e+00, 2.213959930000e+00, 2.395587920000e+00, 
	2.594222070000e+00, 2.849174020000e+00, 3.235632900000e+00, 3.794891120000e+00, 4.543770790000e+00, 
	5.565834050000e+00, 7.155279160000e+00, 1.133734040000e+01};

    EXPECT_TRUE(Numerics::areVectorsEqual(xs, ref, 1.0E-9));
}

TEST_F(XSTestsJeff, GetCrossSectionMatrixSetL0Resonant)
{	
    size_t size = library_->getNuclide("U238")->getXSMatrixSet(XSMatrixKind::SCAT00).getSize();	
    EXPECT_EQ(size, 95);
}

TEST_F(XSTestsJeff, GetCrossSectionMatrixL0Resonant)
{	
    Eigen::MatrixXd mat = library_->getNuclide("U238")->getXSMatrixSet(XSMatrixKind::SCAT00).getXSMatrixNoInterp(9.00000000E+02, 2.11442700E+03).getValues();
	std::vector<double> vec = Numerics::eigenVecTOStdVec(mat.diagonal(1)); 

	// PrintFuncs::createCppVector(vec, "%13.12e");

	std::vector<double> ref {1.110035550000e-01, 2.329197080000e-01, 1.679653080000e-01, 
	1.475068780000e-01, 1.797772650000e-01, 1.830834600000e-01, 1.827283050000e-01, 1.802528500000e-01, 
	2.325887080000e-01, 1.699369250000e-01, 1.778911650000e-01, 1.782254130000e-01, 1.794444170000e-01, 
	1.941299140000e-01, 2.869739230000e-01, 3.838130240000e-01, 3.477593660000e-01, 8.221194740000e-01, 
	1.284136300000e+00, 7.891222830000e-01, 9.047046900000e-01, 1.004729750000e+00, 1.358725910000e+00, 
	9.114969970000e-01, 8.777418140000e-01, 8.880853060000e-01, 1.686237340000e+00, 1.153432370000e+00, 
	1.935759900000e+00, 1.237772350000e+00, 1.147900340000e+00, 1.133644220000e+00, 9.116095900000e-01, 
	6.825250980000e-01, 4.733963910000e-01, 6.198982000000e-01, 1.382443260508e+00, 4.395866742071e-01, 
	6.524906999813e-01, 4.799215900038e-01, 5.004931029975e-01, 1.019749152134e+00, 5.252021889858e-01, 
	1.062717989916e+00, 1.075267020079e+00, 8.186818909261e-01, 1.652076980704e+00, 2.284982949409e+00, 
	2.577658041524e+00, 1.162748949932e+00, 6.208161880098e-01, 8.288380089989e-01, 1.389248979809e+00, 
	1.333979050051e+00, 5.900052810118e-01, 6.472094021239e-01, 5.266357708677e-01, 7.108929828954e-01, 
	6.512208999139e-01, 5.576832900165e-01, 8.739447941390e-01, 1.077466979707e+00, 3.817209050781e+00, 
	6.911640271667e-01, 6.716496119171e-01, 1.085727049644e+00, 4.839141960206e-01, 3.004127002373e+00, 
	1.630911969901e+00, 5.561000214524e-01, 4.776766889175e-01, 6.834027294434e-01, 4.279686080306e-01, 
	7.689679231680e-01, 8.672646290276e-01, 9.888469261261e-01, 8.594769100545e-01, 8.011277029794e-01, 
	7.544989871032e-01, 3.857465070140e-01, 5.305972150034e-01, 6.731720766978e-01, 3.868848988422e-01, 
	5.850899160311e-01, 3.361423037973e-01, 6.133361899986e-01, 8.072202839930e-01, 3.042165110000e+00, 
	1.847887959993e+00, 1.479009112773e-01, 3.774037262277e-01, 8.172008900067e-01, 9.728916397050e-01, 
	9.833767890000e+00, 7.450306890000e+00, 1.490042020000e+01, 1.168848040000e+01, 1.279240990000e+01, 
	1.289817050000e+01, 1.704898070000e+01, 3.836944960000e+01, 1.026297990000e+02, 5.960084230000e+02, 
	3.964089050000e+02, 2.142109070000e+02, 7.963670350000e+01, 2.562401960000e+01, 6.362060070000e+00, 
	1.079363940000e+00, 3.173879090000e-01, 6.359112260000e-01, 1.637660980000e+00, 1.257699970000e+00, 
	3.263005970000e+00, 7.149289250000e-01, 3.486340050000e+00, 2.494997020000e+00, 5.109445100000e+00, 
	1.614146950000e+00, 3.544334890000e+00, 2.020749090000e+00, 3.719317910000e+00, 8.850393890000e-01, 
	4.259197240000e+00, 4.039895060000e+00, 5.923412800000e+00, 4.326447960000e+00, 4.749077800000e+00, 
	1.931069020000e+00, 4.414416790000e+00, 1.093623040000e+00, 5.716616150000e+00, 5.218443870000e+00, 
	4.644567010000e+00, 5.362852100000e+00, 4.062688830000e+00, 5.258607860000e+00, 6.226116180000e+00, 
	2.733675960000e+00, 3.975349900000e+00, 3.412704940000e+00, 3.736161950000e+00, 7.640131710000e-01, 
	2.173305030000e+00, 4.788801190000e+00, 4.162020210000e+00, 5.858343120000e+00, 5.051576140000e+00, 
	3.382707120000e+00, 4.442020890000e+00, 4.732656960000e+00, 5.496686940000e+00, 7.258346080000e+00, 
	5.630942820000e+00, 3.794219020000e+00, 3.987725970000e+00, 6.852002140000e+00, 9.499110220000e+00, 
	9.667233470000e+00, 1.020921990000e+01, 1.193850040000e+01, 1.370582010000e+01, 1.862064930000e+01, 
	2.530933000000e+01, 4.571121980000e+01, 1.897285000000e+02, 6.495902250000e+01, 3.311228940000e+01, 
	2.232885930000e+01, 1.553497980000e+01, 1.177211000000e+01, 1.103973010000e+01, 8.446941380000e+00, 
	5.092237950000e+00, 2.005651950000e+00, 1.191604020000e+00, 1.813439970000e+00, 1.800657030000e+00, 
	2.505966900000e+00, 2.765137910000e+00, 1.830749990000e+00, 3.736248970000e+00, 3.148598910000e+00, 
	2.477572920000e+00, 5.173394200000e+00, 2.194705010000e+00, 4.704909800000e+00, 4.808172230000e+00, 
	2.970509050000e+00, 3.254853960000e+00, 1.839481000000e+00, 1.935729980000e+00, 8.987243770000e-01, 
	2.725352050000e+00, 3.274986980000e+00, 1.309049960000e+00, 2.759593010000e+00, 2.140496020000e+00, 
	2.217197900000e+00, 9.258934260000e-01, 1.188776970000e+00, 1.234027980000e+00, 1.251626010000e+00, 
	1.278067950000e+00, 3.131851910000e+00, 1.048660040000e+00, 1.872542980000e+00, 2.238332030000e+00, 
	3.292496920000e+00, 3.001050000000e+00, 1.452626940000e+00, 2.444586040000e+00, 2.555754900000e+00, 
	2.970387940000e+00, 2.350311990000e+00, 2.555003880000e+00, 2.515624050000e+00, 1.896800990000e+00, 
	1.836799030000e+00, 2.154525040000e+00, 2.490221020000e+00, 1.533606050000e+00, 1.994824050000e+00, 
	2.986689090000e+00, 2.081355090000e+00, 2.492461920000e+00, 2.214227910000e+00, 2.584105970000e+00, 
	1.525658970000e+00, 1.616168980000e+00, 1.355486040000e+00, 1.253049020000e+00, 1.268942950000e+00, 
	1.465314030000e+00, 3.277265070000e+00, 1.090651040000e+00, 1.287389990000e+00, 1.368567940000e+00, 
	1.551841020000e+00, 1.823227050000e+00, 1.913048980000e+00, 2.163988110000e+00, 2.870847940000e+00, 
	2.836795090000e+00, 2.317747120000e+00, 1.441923980000e+00, 1.068573950000e+00, 2.674792050000e+00, 
	2.127315040000e+00, 2.455089090000e+00, 2.040143010000e+00, 2.004148010000e+00, 1.923576950000e+00, 
	1.842946050000e+00, 1.845852020000e+00, 2.428634880000e+00, 2.146687030000e+00, 2.078895090000e+00, 
	2.029495950000e+00, 2.053101060000e+00, 2.486430880000e+00, 2.003489020000e+00, 1.914484980000e+00, 
	2.030493020000e+00, 2.058667900000e+00, 2.011765000000e+00, 1.917117000000e+00, 1.907407050000e+00, 
	1.867619990000e+00, 1.847823020000e+00, 1.798460960000e+00, 1.780938030000e+00, 1.727548000000e+00, 
	1.989313960000e+00, 1.918544050000e+00, 1.665030960000e+00, 1.522343040000e+00, 1.502802010000e+00, 
	1.437505960000e+00, 1.416105990000e+00};

    EXPECT_TRUE(Numerics::areVectorsEqual(vec, ref, 1.0E-9));
}