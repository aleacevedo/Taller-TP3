#ifndef FILE_ERROR_H_
#define FILE_ERROR_H_

#include <exception>

#define BUF_LEN 256

class FileError : public std::exception {
 private:
  char msg_error[BUF_LEN];

 public:
  explicit FileError(const char* fmt, ...) noexcept;
  virtual const char *what() const noexcept;
  virtual ~FileError() noexcept {};
};

#endif  //  FILE_ERROR_H_