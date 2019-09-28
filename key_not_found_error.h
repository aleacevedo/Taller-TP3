#ifndef KEY_NOT_FOUND_ERROR_H_
#define KEY_NOT_FOUND_ERROR_H_

#include <exception>

#define BUF_LEN 256

class KeyNotFoundError : public std::exception {
 private:
  char msg_error[BUF_LEN];

 public:
  explicit KeyNotFoundError(const char* fmt, ...) noexcept;
  virtual const char *what() const noexcept;
  virtual ~KeyNotFoundError() noexcept {};
};

#endif  //  KEY_NOT_FOUND_ERROR_H_
