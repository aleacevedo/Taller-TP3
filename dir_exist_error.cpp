#include "dir_exist_error.h"

DirExistError::DirExistError(std::string msg) noexcept {
  this->msg_error = msg + "\n Directory alredy exist error \n";
}

const char* DirExistError::what() const noexcept {
  return this->msg_error.c_str();
}
