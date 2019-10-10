#ifndef CUSTOM_ERRORS_H_
#define CUSTOM_ERRORS_H_

#include <exception>
#include <string>

#define BUF_LEN 256

class FileError : public std::exception {
 private:
  std::string msg_error;

 public:
  explicit FileError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~FileError() noexcept {};
};

class KeyNotFoundError : public std::exception {
 private:
  std::string msg_error;

 public:
  explicit KeyNotFoundError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~KeyNotFoundError() noexcept {};
};

class DirNotExistError : public std::exception {
 private:
  std::string msg_error;

 public:
  explicit DirNotExistError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~DirNotExistError() noexcept {};
};

class DirExistError : public std::exception {
 private:
  std::string msg_error;

 public:
  explicit DirExistError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~DirExistError() noexcept {};
};

class GetAddrInfoError : public std::exception {
 private:
  std::string msg_error;

 public:
  explicit GetAddrInfoError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~GetAddrInfoError() noexcept {};
};

class SocketError : public std::exception {
 private:
  std::string msg_error;

 public:
  explicit SocketError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~SocketError() noexcept {};
};

class CommandError : public std::exception {
 private:
  std::string msg_error;

 public:
  explicit CommandError(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  virtual ~CommandError() noexcept {};
};


#endif  //  CUSTOM_ERRORS_H_
