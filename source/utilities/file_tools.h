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
        bool result = false;
        std::string parentFolder = getParentFolder(inputFile);

        if (fs::exists(parentFolder))
	    {
            std::ofstream file {inputFile};
            result = true;
        }

        return result;
    }

    inline bool removeFile(const std::string& file)
    {
        bool result = false;
        
        fs::path filePath{fs::u8path(file)};

        if (fs::exists(filePath))
	    {
            fs::remove(filePath);
            result = true;
        }

        return result;
    }

    inline bool moveFile(const std::string& inputFile, const std::string& targetFolder)
    {
        fs::path sourceFile{fs::u8path(inputFile)};
        fs::path targetParent{fs::u8path(targetFolder)};

        auto target = targetParent / sourceFile.filename(); // sourceFile.filename() returns "sourceFile.ext".

        try // If you want to avoid exception handling, then use the error code overload of the following functions.
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

    inline void compressFile(const std::string& data)
	{
		// read filename from the function argument
        std::ofstream file(data, std::ios_base::out | std::ios_base::binary);
        boost::iostreams::filtering_streambuf<boost::iostreams::output> outbuf;
        outbuf.push(boost::iostreams::gzip_compressor());
        outbuf.push(file);
        // convert streambuf to ostream
        std::ostream out(&outbuf);
        // write some test data
        out << "This is a test text!\n";
        // cleanup
        boost::iostreams::close(outbuf);
        file.close();
	}

	inline void decompressFile(const std::string& data)
	{
		// read from the function argument, assume it's gzipped
        std::ifstream file(data, std::ios_base::in | std::ios_base::binary);
        boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf;
        inbuf.push(boost::iostreams::gzip_decompressor());
        inbuf.push(file);
        // convert streambuf to istream
        std::istream instream(&inbuf);
        // copy everything from instream to 
        std::cout << instream.rdbuf();
        // cleanup
        file.close();
	}
}

#endif