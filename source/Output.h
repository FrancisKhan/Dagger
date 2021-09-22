#ifndef OUTPUT_H
#define OUTPUT_H

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "TraceLevel.h"
#include "Sink.h"

class Output
{
public:
    Output() : logger_(nullptr), outputName_(""), 
	inputPath_(""), inputName_("") {}

    void printStart();
	void printEnd();
	void createLogger(Sink sink, std::string loggerName = "DRAG-LIB-READER");
	std::shared_ptr<spdlog::logger> getLogger();
	void setInputPath(std::string inputPath);
	void setOutputPath(std::string ioutputPathName);
	void setLevel(std::string level);
	TraceLevel getLevel() {return logLevel_;}
	std::string getInputPath() {return inputPath_;}
	std::string getInputName() {return inputName_;}
	std::string getOutputName() {return outputName_;}

	void print(TraceLevel level, std::string str);
	void print(TraceLevel level, std::string str, int input);
	void print(TraceLevel level, std::string str, double input);
	void print(TraceLevel level, std::string str, std::string input);
	void print(TraceLevel level, std::string str, std::string input1, int input2);
	void print(TraceLevel level, std::string str, int input1, double input2);
	void print(TraceLevel level, std::string str, double input1, double input2);
	void print(TraceLevel level, std::string str, std::string input1, std::string input2);
	void print(TraceLevel level, std::string str, int input1, double input2, double input3);
	void print(TraceLevel level, std::string str, std::string input1, double input2, double input3);
	void print(TraceLevel level, std::string str, std::string input1, std::string input2, std::string input3);
	void print(TraceLevel level, std::string str, int input1, int input2, int input3, double input4);
	void print(TraceLevel level, std::string str, std::string input1, std::string input2, std::string input3, std::string input4);
	void print(TraceLevel level, std::string str, std::string input1, std::string input2, std::string input3, 
			   std::string input4, std::string input5);
	void print(TraceLevel level, std::string str, int input1, int input2, int input3, int input4, double input5);
	void print(TraceLevel level, std::string str, int input1, int input2, int input3, double input4, double input5);
	void print(TraceLevel level, std::string str, std::string input1, std::string input2, std::string input3, 
			   std::string input4, std::string input5, std::string input6, std::string input7, std::string input8);

private: 
	void removeOldOutputFile();

	std::shared_ptr<spdlog::logger> logger_;
	std::string outputPath_;
	std::string outputName_;
	std::string inputPath_;
	std::string inputName_;
	std::string outputFullName_;
	TraceLevel logLevel_;
};

extern Output out;

#endif

// trace
// debug
// info
// warn
// error
// critical