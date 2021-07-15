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

    inline std::string compressFile(const std::string& data)
	{
		namespace bio = boost::iostreams;

		std::stringstream compressed;
		std::stringstream origin(data);

		bio::filtering_streambuf<bio::input> out;
		out.push(bio::gzip_compressor(bio::gzip_params(bio::gzip::best_compression)));
		out.push(origin);
		bio::copy(out, compressed);

		return compressed.str();
	}

	inline std::string decompressFile(const std::string& data)
	{
		namespace bio = boost::iostreams;

		std::stringstream compressed(data);
		std::stringstream decompressed;

		bio::filtering_streambuf<bio::input> out;
		out.push(bio::gzip_decompressor());
		out.push(compressed);
		bio::copy(out, decompressed);

		return decompressed.str();
	}
}

#endif