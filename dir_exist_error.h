#ifndef DIR_EXIST_ERROR_H_
#define DIR_EXIST_ERROR_H_

#include <exception>
#include <string>

class DirExistError : public std::exception {

 private:
  std::string msg_error;

 public:
  explicit DirExistError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~DirExistError() noexcept {};
};

#endif  //  DIR_EXIST_ERROR_H_
