#include "common_custom_errors.h"
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <string.h>

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

FileError::FileError(std::string msg) noexcept {
  int _errno = errno;
  this->msg_error = msg + " " + strerror(_errno);
}

const char* FileError::what() const noexcept {
  return this->msg_error.c_str();
}

KeyNotFoundError::KeyNotFoundError(const std::string msg) noexcept {
  this->msg_error = msg + "\n Key not found error. \n";
}

const char* KeyNotFoundError::what() const noexcept {
  return this->msg_error.c_str();
}

GetAddrInfoError::GetAddrInfoError(std::string msg) noexcept {
  this->msg_error = msg + "\n Get addr info error error \n";
}

const char* GetAddrInfoError::what() const noexcept {
  return this->msg_error.c_str();
}

SocketError::SocketError(std::string msg) noexcept {
  int _errno = errno;
  this->msg_error = msg + " " + strerror(_errno);
}

const char* SocketError::what() const noexcept {
  return this->msg_error.c_str();
}
