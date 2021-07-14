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