#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include <set>
#include <string>
#include <mutex>

class Directory {
  std::set<std::string> directories;
  std::mutex dir_mutex;

 public:
  Directory();
  void add(std::string name);
  void remove(std::string name);
  std::string list();
  ~Directory();
};

#endif  //  DIRECTORY_H_
