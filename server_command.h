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
  virtual ~Command() {}
};

class WelcomeCommand : public Command {
  HoneyPot &hp;
 public:
  explicit WelcomeCommand(HoneyPot &hp);
  virtual std::string execute(std::string received);
  ~WelcomeCommand();
};

class UserCommand : public Command {
  HoneyPot &hp;
  int *auth;
 public:
  explicit UserCommand(HoneyPot &hp, int *auth);
  virtual std::string execute(std::string received);
  ~UserCommand();
};

class PassCommand : public Command {
  HoneyPot &hp;
  int *auth;
 public:
  explicit PassCommand(HoneyPot &hp, int *auth);
  virtual std::string  execute(std::string received);
  ~PassCommand();
};

class SystCommand : public Command {
  HoneyPot &hp;
  int *auth;
 public:
  explicit SystCommand(HoneyPot &hp, int *auth);
  virtual std::string  execute(std::string received);
  ~SystCommand();
};

class ListCommand : public Command {
  HoneyPot &hp;
  int *auth;
  Directory &dir;
 public:
  explicit ListCommand(HoneyPot &hp, int *auth, Directory &dir);
  virtual std::string  execute(std::string received);
  ~ListCommand();
};

class HelpCommand : public Command {
  HoneyPot &hp;
  int *auth;
  std::map<std::string, Command*> &commands;
 public:
  explicit HelpCommand(HoneyPot &hp, int *auth,
                      std::map<std::string, Command*> &commands);
  virtual std::string  execute(std::string received);
  std::string get_commands();
  ~HelpCommand();
};

class PWDCommand : public Command {
  HoneyPot &hp;
  int *auth;
 public:
  explicit PWDCommand(HoneyPot &hp, int *auth);
  virtual std::string  execute(std::string received);
  ~PWDCommand();
};

class MKDCommand : public Command {
  HoneyPot &hp;
  int *auth;
  Directory &dir; public:
  explicit MKDCommand(HoneyPot &hp, int *auth, Directory &dir);
  virtual std::string  execute(std::string received);
  ~MKDCommand();
};

class RMDCommand : public Command {
  HoneyPot &hp;
  int *auth;
  Directory &dir; public:
  explicit RMDCommand(HoneyPot &hp, int *auth, Directory &dir);
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


class AllCommands {
  std::map<std::string, Command*> commands;
  WelcomeCommand welcome_command;
  UNKCommand unk_command;
 public:
  AllCommands(int *auth, Directory &dir, HoneyPot &hp);
  AllCommands(AllCommands&& other);
  Command* get_commands(std::string key_command);
  Command* get_welcome();
  ~AllCommands();
};


#endif  //  COMMAND_H_
