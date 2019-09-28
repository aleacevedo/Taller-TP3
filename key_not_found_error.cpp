#include "key_not_found_error.h"
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <strings.h>

KeyNotFoundError::KeyNotFoundError(const char *fmt, ...) noexcept {
  va_list args;
  msg_error[0] = '\n';
  va_start(args, fmt);
  int s = vsnprintf(msg_error+1, BUF_LEN, fmt, args);
  va_end(args);
  strncpy(msg_error+s,  ". Key Not Found Error\n", BUF_LEN-s);
  msg_error[BUF_LEN-1] = 0;
}

const char* KeyNotFoundError::what() const noexcept {
  return this->msg_error;
}