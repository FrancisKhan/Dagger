#ifndef FILE_TOOLS_H
#define FILE_TOOLS_H

#include <string>
#include <exception>
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "inputParser.h"

namespace fs = std::experimental::filesystem;

namespace File
{
    inline std::string getCurrentPath()
    {
        return fs::current_path();
    }

    inline std::string getParentFolder(const std::string& path)
    {
        std::string result("");
	    std::size_t found = path.find_last_of("/\\");
	
	    if (found != std::string::npos)
	    {
		    result = path.substr(0, found);
	    }

        return result;
    }

    inline std::string getFileExtension(const std::string& path)
    {
        std::string result("");
	    std::size_t found = path.find_last_of(".\\");
	
	    if (found != std::string::npos)
	    {
		    result = path.substr(found + 1);
	    }

        return result;
    }

    inline bool createFile(const std::string& inputFile)
    {
        std::string parentFolder = getParentFolder(inputFile);

        if (!fs::exists(parentFolder))
	    {
            fs::create_directories(parentFolder);
        }

        std::ofstream file {inputFile};
        return true;
    }

    inline bool removeFile(const std::string& file)
    {
        bool result = false;

        if (fs::exists(file))
	    {
            fs::remove_all(file);
            result = true;
        }

        return result;
    }

    inline bool moveFile(const std::string& inputFile, const std::string& targetFolder)
    {
        fs::path sourceFile{fs::u8path(inputFile)};
        fs::path targetParent{fs::u8path(targetFolder)};

        auto target = targetParent / sourceFile.filename(); // sourceFile.filename() returns "sourceFile.ext".

        try
        {
            fs::create_directories(targetParent); // Recursively create target directory if not existing.
            fs::copy_file(sourceFile, target, fs::copy_options::overwrite_existing);
            removeFile(sourceFile);
        }
        catch (std::exception& e) // Not using fs::filesystem_error since std::bad_alloc can throw too.  
        {
            std::cout << e.what();
        }

        return true;
    }

    inline std::vector<std::string> readTextFile(const std::string& inputFile)
	{
        std::vector<std::string> data;

        std::ifstream fileData;
        fileData.open(inputFile);
        if (!fileData) 
        {
            throw std::runtime_error("ERROR: Unable to open file");
        }
        
        std::string line;
        while (std::getline(fileData, line))
        {
            data.push_back(InputParser::removeSpaces(line));
        }

        fileData.close();
        return data;
	}

    inline void compressFile(const std::string& data, std::vector<std::string>& content)
	{
		// read filename from the function argument
        std::ofstream file(data, std::ios_base::out | std::ios_base::binary);
        boost::iostreams::filtering_streambuf<boost::iostreams::output> outbuf;
        outbuf.push(boost::iostreams::gzip_compressor());
        outbuf.push(file);
        std::ostream out(&outbuf); // convert streambuf to ostream
        
        for(const auto& i : content) // write data content
            out << i << "\n";
        
        // cleanup
        boost::iostreams::close(outbuf);
        file.close();
	}

    inline std::vector<std::string> decompressFile(const std::string& inputFile)
	{
        std::vector<std::string> result;

        if(fs::exists(inputFile) && (getFileExtension(inputFile) == "gz"))
	    {
            // read from the function argument, assume it's gzipped
            std::ifstream file(inputFile, std::ios_base::in | std::ios_base::binary);
            boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf;
            inbuf.push(boost::iostreams::gzip_decompressor());
            inbuf.push(file);
            std::istream instream(&inbuf); // convert streambuf to istream

            std::string line;
            while (std::getline(instream, line))
                result.push_back(InputParser::removeSpaces(line));

            file.close(); // cleanup
        }
        else
        {
            throw std::runtime_error("ERROR: Unable to open file");
        }

        return result;
	}

    // This method is needed because Visual Studio Code runs the tests from 
    // the base folder, while make or ctest runs from the tests folder.
    // Absolute path seem not to work with WLS as well
    inline std::string getPrePath() 
    {
        std::string path = getCurrentPath();

        if(path.substr(path.size() -5, path.size()) == "tests")
        {
            return std::string("./../");
        }
        else
        {
            return std::string("./");
        }
    }
}

#endif