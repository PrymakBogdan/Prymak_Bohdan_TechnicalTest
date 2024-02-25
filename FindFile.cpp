#include "FindFile.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <stack>
#include <mutex>
#include <condition_variable>
using namespace std::filesystem;
std::mutex mtx;
std::condition_variable cv;
static int activeThreads = 0;

void makeList(std::stack <std::string> & list, path currentPath, path & fileDirectory, std::string & fileName)
{
  try 
  {
    for (const auto& entry : directory_iterator(currentPath)) 
    {
      path dir = entry.path();

      if (entry.is_directory()) 
        list.push(dir.string());
      else
      {
        if (entry.path().filename() == fileName)
        {
          fileDirectory = dir;
          return;
        }
      }
    }
  }
  catch (const filesystem_error& e) {}
}


void findFileInDir(path dirPath, path & fileDirectory, std::string & fileName)
{
  std::stack <std::string> dirList;
  makeList(dirList, dirPath, fileDirectory, fileName);

  while (dirList.size() != 0 && fileDirectory == "")
  {
    findFileInDir(dirList.top(), fileDirectory,fileName);
    dirList.pop();
  }

  activeThreads--;
  cv.notify_one();
}



std::string findFile(std::string & fileName)
{
  path rootDirectory = "/";
  path fileDirectory = "";
  std::stack <std::string> rootList;

  makeList(rootList, rootDirectory, fileDirectory, fileName);
 
  std::vector <std::thread> threads;
  const int maxThreads = 8;

  while (rootList.size() > 0 && fileDirectory == "")
  {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&]{ return activeThreads < maxThreads; });
    threads.emplace_back(std::thread(findFileInDir, rootList.top(), std::ref(fileDirectory), std::ref(fileName)));
    rootList.pop();
  }

  for (auto& thread : threads) 
      thread.join();

  return fileDirectory.string();
}
