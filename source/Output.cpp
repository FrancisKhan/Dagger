#include "Output.h"

#include <stdio.h>
#include <iostream>
#include <experimental/filesystem>
#include "spdlog/sinks/null_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

Output out;

namespace fs = std::experimental::filesystem;

void Output::printStart()
{
	out.getLogger()->set_pattern("[%D %T] [%n] %v");
	out.getLogger()->critical("Start reading");
    out.getLogger()->critical("DRAGON Library Reader\n");
	out.getLogger()->set_pattern("%v");
}

void Output::printEnd()
{
	out.getLogger()->set_pattern("[%D %T] [%n] %v");
	out.getLogger()->critical("End of reading");
}

void Output::setLevel(std::string level) 
{
	if(level == "CRITICAL")
	{
		logger_->set_level(spdlog::level::critical);
		logLevel_ = TraceLevel::CRITICAL;
	}
	else if(level == "ERR")    
	{
		logger_->set_level(spdlog::level::err);
		logLevel_ = TraceLevel::ERR;
	}
	else if(level == "WARN")
	{
		logger_->set_level(spdlog::level::warn);
		logLevel_ = TraceLevel::WARN;
	}     
	else if(level == "INFO")    
	{
		logger_->set_level(spdlog::level::info);
		logLevel_ = TraceLevel::INFO;
	} 
	else if(level == "DEBUG")    
	{
		logger_->set_level(spdlog::level::debug);
		logLevel_ = TraceLevel::DEBUG;
	}
	else if(level == "TRACE")    
	{
		logger_->set_level(spdlog::level::trace);
		logLevel_ = TraceLevel::TRACE;
	}
	else 
	{
		out.print(TraceLevel::CRITICAL, "Trace Level not recognized");
		out.print(TraceLevel::CRITICAL, "Please use capital letters: CRITICAL, ERR, WARN, INFO, DEBUG or TRACE");
		out.print(TraceLevel::CRITICAL, "Trace Level defaulted to CRITICAL \n");
		logger_->set_level(spdlog::level::critical);
		logLevel_ = TraceLevel::CRITICAL;
	}
}

std::shared_ptr<spdlog::logger> Output::getLogger() 
{
	if (logger_ == nullptr)
		std::cout << "getLogger() nullprt!!" << std::endl;
	
	return logger_;
}

void Output::setInputPath(std::string inputPathName)
{
	std::size_t found = inputPathName.find_last_of("/\\");
	
	if (found != std::string::npos)
	{
		inputPath_ = inputPathName.substr(0, found);
		inputName_ = inputPathName.substr(found + 1);
	}
}

void Output::setOutputPath(std::string outputPathName)
{
	std::size_t found = outputPathName.find_last_of("/\\");
	
	if (found != std::string::npos)
	{
		outputPath_ = outputPathName.substr(0, found);
		outputName_ = outputPathName.substr(found + 1);
	}
	
	outputFullName_ = outputPathName;
	
	removeOldOutputFile();
}

void Output::createLogger(Sink sink, std::string loggerName)
{
	std::shared_ptr<spdlog::logger> logger = spdlog::details::registry::instance().get(loggerName);

	// check whether there is already a logger with the loggerName name
	if((logger != nullptr))
	{
		spdlog::drop(loggerName);
	}
	
	if(sink == Sink::CONSOLE)
	{
		logger_ = spdlog::stdout_color_mt(loggerName);
	}
	else if (sink == Sink::FILE)
	{
		logger_ = spdlog::basic_logger_mt(loggerName, outputFullName_);
	}
	else if (sink == Sink::EMPTY)
	{
		logger_ = spdlog::create<spdlog::sinks::null_sink_st>(loggerName);
	}
	else // BOTH case
	{
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(outputFullName_, true);
		spdlog::sinks_init_list sink_list = {console_sink, file_sink};
		logger_ = std::make_shared<spdlog::logger>(loggerName, sink_list);
	}
	
	logger_->flush_on(spdlog::level::info);
}

void Output::removeOldOutputFile()
{
	if (fs::exists(outputFullName_))
	{
		std::remove(outputFullName_.c_str());
	}
}

void Output::print(TraceLevel level, std::string str)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str);
	else {}
}

void Output::print(TraceLevel level, std::string str, int input)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input);
	else {}
}

void Output::print(TraceLevel level, std::string str, double input)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input);
	else {}
}

void Output::print(TraceLevel level, std::string str, std::string input)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input);
	else {}
}

void Output::print(TraceLevel level, std::string str, int input1, double input2)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2);
	else {}
}

void Output::print(TraceLevel level, std::string str, double input1, double input2)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2);
	else {}
}

void Output::print(TraceLevel level, std::string str, std::string input1, std::string input2)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2);
	else {}
}

void Output::print(TraceLevel level, std::string str, int input1, double input2, double input3)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3);
	else {}
}

void Output::print(TraceLevel level, std::string str, std::string input1, int input2)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2);
	else {}
}

void Output::print(TraceLevel level, std::string str, std::string input1, std::string input2, std::string input3)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3);
	else {}
}


void Output::print(TraceLevel level, std::string str, int input1, int input2, int input3, double input4)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3, input4);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3, input4);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3, input4);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3, input4);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3, input4);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3, input4);
	else {}
}

void print(TraceLevel level, std::string str, std::string input1, double input2, double input3)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3);
	else {}
}

void Output::print(TraceLevel level, std::string str, std::string input1, 
                   std::string input2, std::string input3, std::string input4)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3, input4);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3, input4);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3, input4);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3, input4);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3, input4);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3, input4);
	else {}
}

void Output::print(TraceLevel level, std::string str, std::string input1, 
                   std::string input2, std::string input3, std::string input4, std::string input5)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3, input4, input5);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3, input4, input5);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3, input4, input5);
	else {}
}

void Output::print(TraceLevel level, std::string str, int input1, int input2, int input3, int input4, double input5)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3, input4, input5);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3, input4, input5);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3, input4, input5);
	else {}
}

void Output::print(TraceLevel level, std::string str, int input1, int input2, int input3, double input4, double input5)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3, input4, input5);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3, input4, input5);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3, input4, input5);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3, input4, input5);
	else {}
}

void Output::print(TraceLevel level, std::string str, std::string input1, 
                   std::string input2, std::string input3, std::string input4, std::string input5,
				   std::string input6, std::string input7, std::string input8)
{
	if (level == TraceLevel::CRITICAL)
		out.getLogger()->critical(str, input1, input2, input3, input4, input5, input6, input7, input8);
	else if (level == TraceLevel::ERR)
		out.getLogger()->error(str, input1, input2, input3, input4, input5, input6, input7, input8);
	else if (level == TraceLevel::WARN)
		out.getLogger()->warn(str, input1, input2, input3, input4, input5, input6, input7, input8);
	else if (level == TraceLevel::INFO)
		out.getLogger()->info(str, input1, input2, input3, input4, input5, input6, input7, input8);
	else if(level == TraceLevel::DEBUG)
		out.getLogger()->debug(str, input1, input2, input3, input4, input5, input6, input7, input8);
	else if(level == TraceLevel::TRACE)
		out.getLogger()->trace(str, input1, input2, input3, input4, input5, input6, input7, input8);
	else {}
}