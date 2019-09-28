#include "file_error.h"
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <strings.h>

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