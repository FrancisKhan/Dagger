#include <iostream>

#include "gtest/gtest.h"
#include "file_tools.h"

TEST(FileToolsTests, CreateRemoveFile)
{	
    std::string newFile = File::getCurrentPath() + "/newFile.txt";
    File::createFile(newFile);
    EXPECT_TRUE(File::removeFile(newFile));
}

TEST(FileToolsTests, MoveFile)
{	
    std::string newFile = File::getCurrentPath() + "/newFile.txt";
    File::createFile(newFile);
    std::string targetFolder = File::getCurrentPath() + "/neutron_libraries/";
    File::moveFile(newFile, targetFolder);
    EXPECT_TRUE(File::removeFile(targetFolder));
}

TEST(FileToolsTests, getFileExtension)
{	
    std::string newFile = File::getCurrentPath() + "/newFile.txt";
    std::string extension = File::getFileExtension(newFile);
    EXPECT_EQ(extension, "txt");
}

TEST(FileToolsTests, CompressDecompressFile)
{	
    std::vector<std::string> refVec{"Text1!", "Text2!", "Text3!"}; 

    std::string newFile = File::getCurrentPath() + "/newFile.gz";
    File::compressFile(newFile, refVec);

    std::vector<std::string> result = File::decompressFile(newFile);
    bool areEqual = std::equal(refVec.begin(), refVec.end(), result.begin());

    File::removeFile(newFile);
    EXPECT_TRUE(areEqual);
}

TEST(testaaa, testaaa1)
{
    std::string line = "->       1      12       0       1                                              ";
    std::string key  = "->       1      12       0       1";
	std::cout << "Test: " << InputParser::isKeywordPresentInString(key, line) << std::endl;
} 