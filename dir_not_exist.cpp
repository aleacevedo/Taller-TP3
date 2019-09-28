#include "dir_not_exist_error.h"

DirNotExistError::DirNotExistError(std::string msg) noexcept {
  this->msg_error = msg + "\n Directory not exist error \n";
}

const char* DirNotExistError::what() const noexcept {
  return this->msg_error.c_str();
}
