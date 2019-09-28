#include "custom_errors.h"
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <strings.h>

DirExistError::DirExistError(std::string msg) noexcept {
  this->msg_error = msg + "\n Directory alredy exist error \n";
}

const char* DirExistError::what() const noexcept {
  return this->msg_error.c_str();
}

DirNotExistError::DirNotExistError(std::string msg) noexcept {
  this->msg_error = msg + "\n Directory not exist error \n";
}

const char* DirNotExistError::what() const noexcept {
  return this->msg_error.c_str();
}

FileError::FileError(const char *fmt, ...) noexcept {
  int _errno = errno;
  va_list args;
  va_start(args, fmt);
  int s = vsnprintf(msg_error, BUF_LEN, fmt, args);
  va_end(args);
  strncpy(msg_error+s,  strerror(_errno), BUF_LEN-s);
  msg_error[BUF_LEN-1] = 0;
}

const char* FileError::what() const noexcept {
  return this->msg_error;
}

KeyNotFoundError::KeyNotFoundError(const std::string msg) noexcept {
  this->msg_error = msg + "\n Key not found error. \n";
}

const char* KeyNotFoundError::what() const noexcept {
  return this->msg_error.c_str();
}
