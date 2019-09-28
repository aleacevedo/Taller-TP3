#ifndef KEY_NOT_FOUND_ERROR_H_
#define KEY_NOT_FOUND_ERROR_H_

#include <exception>
#include <string>

class KeyNotFoundError : public std::exception {
 private:
  std::string msg_error;

 public:
  explicit KeyNotFoundError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~KeyNotFoundError() noexcept {};
};

#endif  //  KEY_NOT_FOUND_ERROR_H_
