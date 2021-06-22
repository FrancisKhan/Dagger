#include "Input.h"
#include "Output.h"
#include "KineticsSet.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace Eigen;
using namespace Numerics;

void Input::getArguments(int argc, char** argv)
{
	if(argc < 3)
	{
		std::cout << "Missing input arguments!" << std::endl;
		exit(-1);
	}
	else if(argc == 4)
	{
        std::string inputStr(argv[1]);
	    m_inputPath = inputStr;
	    out.setInputPath(m_inputPath);
		out.setOutputPath(argv[2]);
		out.createLogger();
		std::string levelStr(argv[3]);
		out.setLevel(levelStr);
		m_reactor.setLogLevel(out.getLevel());
	}
	else
	{
		std::cout << "Too many input arguments!" << std::endl;
		exit(-1);
	}
	
}

void Input::printData()
{
	out.print(TraceLevel::CRITICAL, "Input file: {}/{}",  out.getInputPath(), out.getInputName());
	out.print(TraceLevel::CRITICAL, "Output file: {} \n", out.getOutputName());
}