#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <stack>
using namespace std::filesystem;
#ifndef FIND_FILE
#define FIND_FILE

void makeList(std::stack <std::string> & list, path currentPath, path & fileDirectory, std::string & fileName);
void findFileInDir(path dirPath, path & fileDirectory, std::string & fileName);
std::string findFile(std::string & fileName);

#endif