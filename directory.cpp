#include "directory.h"
#include "dir_exist_error.h"
#include "dir_not_exist_error.h"

Directory::Directory() : directories() {}

void Directory::add(std::string name) {
  std::pair<std::set<std::string>::iterator, bool> res;
  this->dir_mutex.lock();
  res = this->directories.insert(name);
  this->dir_mutex.unlock();
  if (!res.second) throw DirExistError("The directory alredy exist");
}

void Directory::remove(std::string name) {
  this->dir_mutex.lock();
  if (this->directories.erase(name) == 0) {
    this->dir_mutex.unlock();
    throw DirNotExistError("Directory not found");
  }
  this->dir_mutex.unlock();
}

std::string Directory::list() {
  std::string list;
  for (std::string dir : this->directories) {
    list = list + dir + '\n';
  }
  return list;
}

Directory::~Directory() {}