#include <iostream>
#include <string>
#include "FindFile.h"

int main()
{
  std::string fileName = "";
  std::cout << "Enter file name: ";
  std::cin >> fileName;
  std::string pathToFile = findFile(fileName);

  if (pathToFile == "")
    std::cout<<"File not found!"<<std::endl;
  else
    std::cout<<"File path: "<< pathToFile<<std::endl;
    
  return 0;
}