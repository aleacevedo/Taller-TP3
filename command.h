#ifndef COMMAND_H_
#define COMMAND_H_

#include <map>
#include <string>
#include "ftp.h"

class Command {
 public:
  virtual std::string execute(int client, std::string) = 0;
  virtual ~Command() {};
};

class FactoryCommand {
  std::map<std::string, Command*> commands;
  FTP ftp;
 public:
  FactoryCommand(std::string conf_file_path);
  std::map<std::string, Command*> getCommands();
  ~FactoryCommand();
};

class UserCommand : public Command {
  FTP &ftp;
 public:
  explicit UserCommand(FTP &ftp);
  virtual std::string execute(int client, std::string user);
  ~UserCommand();
};

class PassCommand : public Command {
  FTP &ftp;
 public:
  explicit PassCommand(FTP &ftp);
  virtual std::string  execute(int client, std::string pass);
  ~PassCommand();
};

class SystCommand : public Command {
  FTP &ftp;
 public:
  explicit SystCommand(FTP &ftp);
  virtual std::string  execute(int client, std::string null);
  ~SystCommand();
};

class ListCommand : public Command {
  FTP &ftp;
 public:
  explicit ListCommand(FTP &ftp);
  virtual std::string  execute(int client, std::string null);
  ~ListCommand();
};
/*
class HelpCommand : public Command {
  const FTP &ftp;
 public:
  explicit HelpCommand(const FTP &ftp);
  virtual std::string  execute(int client, std::string null);
  ~HelpCommand();
};
*/
class PWDCommand : public Command {
  FTP &ftp;
 public:
  explicit PWDCommand(FTP &ftp);
  virtual std::string  execute(int client, std::string null);
  ~PWDCommand();
};

class MKDCommand : public Command {
  FTP &ftp;
 public:
  explicit MKDCommand(FTP &ftp);
  virtual std::string  execute(int client, std::string dir);
  ~MKDCommand();
};

class RMDCommand : public Command {
  FTP &ftp;
 public:
  explicit RMDCommand(FTP &ftp);
  virtual std::string  execute(int client, std::string dir);
  ~RMDCommand();
};

#endif  //  COMMAND_H_
