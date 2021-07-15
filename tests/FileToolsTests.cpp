#include <iostream>

#include "gtest/gtest.h"
#include "file_tools.h"

TEST(FileToolsTests, GetCurrentPath)
{	
    std::string refString = "/home/why/DragLibReader";
    EXPECT_EQ(File::getCurrentPath(), refString);
}

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
    std::string targetFolder = File::getCurrentPath() +"/neutron_libraries/";
    File::moveFile(newFile, targetFolder);
    std::string fileToRemove = File::getCurrentPath() +"/neutron_libraries/newFile.txt";
    EXPECT_TRUE(File::removeFile(fileToRemove));
}

TEST(FileToolsTests, getFileExtension)
{	
    std::string newFile = File::getCurrentPath() + "/newFile.txt";
    std::string extension = File::getFileExtension(newFile);
    EXPECT_EQ(extension, "txt");
}

TEST(FileToolsTests, CompressFile)
{	
    std::string newFile = "/home/why/DragLibReader/newfile.txt";
    // std::string newFile = File::getCurrentPath() + "/newFile.txt";
    //File::createFile(newFile);
    File::compressFile(newFile);
    // bool comparison = File::getFileExtension(newFile)
    // std::string fileToRemove = File::getCurrentPath() +"/neutron_libraries/newFile.txt";
    // EXPECT_TRUE(File::removeFile(fileToRemove));
}

TEST(FileToolsTests, DecompressFile)
{	
    std::string newFile = "/home/why/DragLibReader/newfile.gz";
    // std::string newFile = File::getCurrentPath() + "/newFile.txt";
    //File::createFile(newFile);
    File::decompressFile(newFile);
    // bool comparison = File::getFileExtension(newFile)
    // std::string fileToRemove = File::getCurrentPath() +"/neutron_libraries/newFile.txt";
    // EXPECT_TRUE(File::removeFile(fileToRemove));
}