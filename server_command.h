#ifndef COMMAND_H_
#define COMMAND_H_

#include <map>
#include <string>
#include "server_directory.h"
#include "server_honey_pot.h"

#define FAKE_INFO "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 "

class Command {
 public:
  virtual std::string execute(std::string) = 0;
  virtual ~Command() {};
};

class AllCommands {
  std::map<std::string, Command*> commands;
 public:
  AllCommands(int &auth, Directory &dir, HoneyPot &hp);
  AllCommands(AllCommands&& other);
  Command* getCommands(std::string key_command);
  void operator= (const AllCommands& other);
  ~AllCommands();
};

class NewClientCommand : public Command {
  HoneyPot &hp;
 public:
  explicit NewClientCommand(HoneyPot &hp);
  virtual std::string execute(std::string received);
  ~NewClientCommand();
};

class UserCommand : public Command {
  HoneyPot &hp;
  int &auth;
 public:
  explicit UserCommand(HoneyPot &hp, int &auth);
  virtual std::string execute(std::string received);
  ~UserCommand();
};

class PassCommand : public Command {
  HoneyPot &hp;
  int &auth;
 public:
  explicit PassCommand(HoneyPot &hp, int &auth);
  virtual std::string  execute(std::string received);
  ~PassCommand();
};

class SystCommand : public Command {
  HoneyPot &hp;
  int &auth;
 public:
  explicit SystCommand(HoneyPot &hp, int &auth);
  virtual std::string  execute(std::string received);
  ~SystCommand();
};

class ListCommand : public Command {
  HoneyPot &hp;
  int &auth;
  Directory &dir;
 public:
  explicit ListCommand(HoneyPot &hp, int &auth, Directory &dir);
  virtual std::string  execute(std::string received);
  ~ListCommand();
};
/*
class HelpCommand : public Command {
  HoneyPot &hp;
  int &auth;
 public:
  explicit HelpCommand(HoneyPot &hp, int &auth);
  virtual std::string  execute(std::string received);
  ~HelpCommand();
};
*/
class PWDCommand : public Command {
  HoneyPot &hp;
  int &auth;
 public:
  explicit PWDCommand(HoneyPot &hp, int &auth);
  virtual std::string  execute(std::string received);
  ~PWDCommand();
};

class MKDCommand : public Command {
  HoneyPot &hp;
  int &auth;
  Directory &dir; public:
  explicit MKDCommand(HoneyPot &hp, int &auth, Directory &dir);
  virtual std::string  execute(std::string received);
  ~MKDCommand();
};

class RMDCommand : public Command {
  HoneyPot &hp;
  int &auth;
  Directory &dir; public:
  explicit RMDCommand(HoneyPot &hp, int &auth, Directory &dir);
  virtual std::string  execute(std::string received);
  ~RMDCommand();
};

class UNKCommand : public Command {
  HoneyPot &hp;
 public:
  explicit UNKCommand(HoneyPot &hp);
  virtual std::string execute(std::string received);
  ~UNKCommand();
};

class QuitCommand : public Command {
  HoneyPot &hp;
 public:
  explicit QuitCommand(HoneyPot &hp);
  virtual std::string execute(std::string received);
  ~QuitCommand();
};

#endif  //  COMMAND_H_
