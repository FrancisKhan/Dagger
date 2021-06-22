#ifndef INPUT_H
#define INPUT_H

#include "Reactor.h"
#include "Library.h"
#include "numeric_tools.h"

class Input
{
    typedef std::pair<unsigned, unsigned> us_pair;

public:
    Input(Reactor &reactor, Library &library) : 
	m_reactor(reactor), m_library(library), m_inputPath("") {}
	void printData();
	void getArguments(int argc, char** argv);
	
private:									  
    Reactor &m_reactor;
	Library &m_library;
	std::string m_inputPath;
};

#endif