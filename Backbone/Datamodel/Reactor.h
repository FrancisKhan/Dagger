#ifndef REACTOR_H
#define REACTOR_H

#include "numeric_tools.h"
#include "KineticsSet.h"

#include <vector>
#include <string>

class Reactor
{
public:
	Reactor() {}
	
	void setKineticsSet(KineticsSet &kineticsSet) 
	{m_kineticsSet = kineticsSet;}

    KineticsSet getKineticsSet() {return m_kineticsSet;}

private:
	KineticsSet m_kineticsSet;
};

#endif