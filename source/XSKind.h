#ifndef XSKIND_H
#define XSKIND_H

#include <iostream>

enum class XSKind {NTOT0, NINEL, N2N, N3N, N4N, NNP, 
                   NG, NP, ND, NT, NA, NFTOT, NUSIGF, 
                   CHI, NU, SCATT01};

inline std::ostream& operator << (std::ostream& stm, XSKind xsKind)
{
    switch(xsKind)
    {
        case XSKind::NTOT0   : return stm << "NTOT0";
        case XSKind::NINEL   : return stm << "NINEL";
        case XSKind::N2N     : return stm << "N2N";
        case XSKind::N3N     : return stm << "N3N";
        case XSKind::N4N     : return stm << "N4N";
        case XSKind::NNP     : return stm << "NNP";
        case XSKind::NG      : return stm << "NG";
        case XSKind::NP      : return stm << "NP";
        case XSKind::ND      : return stm << "ND";
        case XSKind::NT      : return stm << "NT";
        case XSKind::NA      : return stm << "NA";
        case XSKind::NFTOT   : return stm << "NFTOT";
        case XSKind::NUSIGF  : return stm << "NUSIGF";
        case XSKind::CHI     : return stm << "CHI";
        case XSKind::NU      : return stm << "NU";
        case XSKind::SCATT01 : return stm << "SCATT01";
        default : return stm << "XSKind{" << int(xsKind) << "}"; 
    }
}

inline std::string get_name(XSKind xsKind) 
{
  switch (xsKind) 
  {
    case XSKind::NTOT0   : return std::string("NTOT0");
    case XSKind::NINEL   : return std::string("NINEL");
    case XSKind::N2N     : return std::string("N2N");
    case XSKind::N3N     : return std::string("N3N");
    case XSKind::N4N     : return std::string("N4N");
    case XSKind::NNP     : return std::string("NNP");
    case XSKind::NG      : return std::string("NG");
    case XSKind::NP      : return std::string("NP");
    case XSKind::ND      : return std::string("ND");
    case XSKind::NT      : return std::string("NT");
    case XSKind::NA      : return std::string("NA");
    case XSKind::NFTOT   : return std::string("NFTOT");
    case XSKind::NUSIGF  : return std::string("NUSIGF");
    case XSKind::CHI     : return std::string("CHI");
    case XSKind::NU      : return std::string("NU");
    case XSKind::SCATT01 : return std::string("SCATT01");
    default : return std::string("");
  }
}

inline XSKind operator++(XSKind& x) 
{ 
    return x = (XSKind)(((int)(x) + 1)); 
}

inline XSKind operator*(XSKind c) 
{
    return c;
}

inline XSKind begin(XSKind r) 
{
    return XSKind::NTOT0;
}

inline XSKind end(XSKind r)   
{
    return XSKind(int(XSKind::SCATT01) + 1);
}

#endif