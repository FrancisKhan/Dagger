#ifndef XSMATRIXKIND_H
#define XSMATRIXKIND_H

#include <iostream>

enum class XSMatrixKind {SCAT00, SCAT01, SCAT02, SCAT03};

inline std::ostream& operator << (std::ostream& stm, XSMatrixKind xsKind)
{
    switch(xsKind)
    {
        case XSMatrixKind::SCAT00  : return stm << "SCAT00";
        case XSMatrixKind::SCAT01  : return stm << "SCAT01";
        case XSMatrixKind::SCAT02  : return stm << "SCAT02";
        case XSMatrixKind::SCAT03  : return stm << "SCAT03";
        default : return stm << "XSMatrixKind{" << int(xsKind) << "}"; 
    }
}

inline std::string get_name(XSMatrixKind xsKind) 
{
  switch (xsKind) 
  {
    case XSMatrixKind::SCAT00  : return std::string("SCAT00");
    case XSMatrixKind::SCAT01  : return std::string("SCAT01");
    case XSMatrixKind::SCAT02  : return std::string("SCAT02");
    case XSMatrixKind::SCAT03  : return std::string("SCAT03");
    default : return std::string("");
  }
}

inline XSMatrixKind operator++(XSMatrixKind& x) 
{ 
    return x = (XSMatrixKind)(((int)(x) + 1)); 
}

inline XSMatrixKind operator*(XSMatrixKind c) 
{
    return c;
}

inline XSMatrixKind begin(XSMatrixKind r) 
{
    return XSMatrixKind::SCAT00;
}

inline XSMatrixKind end(XSMatrixKind r)   
{
    return XSMatrixKind(int(XSMatrixKind::SCAT03) + 1);
}

#endif