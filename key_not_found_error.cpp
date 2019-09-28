#include "key_not_found_error.h"

KeyNotFoundError::KeyNotFoundError(const std::string msg) noexcept {
  this->msg_error = msg + "\n Key not found error. \n";
}

const char* KeyNotFoundError::what() const noexcept {
  return this->msg_error.c_str();
}
