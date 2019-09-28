#ifndef DIR_NOT_EXIST_ERROR_H_
#define DIR_NOT_EXIST_ERROR_H_

#include <exception>
#include <string>

class DirNotExistError : public std::exception {

 private:
  std::string msg_error;

 public:
  explicit DirNotExistError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~DirNotExistError() noexcept {};
};

#endif  //  DIR_NOT_EXIST_ERROR_H_
