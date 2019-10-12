#ifndef COMMAND_FACTORY_H_
#define COMMAND_FACTORY_H_

#include <string>
#include "server_directory.h"
#include "server_honey_pot.h"
#include "server_command.h"

class CommandFactory {
  Directory &myDir;
  HoneyPot myHP;

 public:
  CommandFactory(Directory &myDir, std::string config_file_path);
  AllCommands generate_commands(int *auth);
  ~CommandFactory();
};

#endif  //  COMMAND_FACTORY_H_
