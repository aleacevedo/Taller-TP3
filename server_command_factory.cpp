#include "server_command_factory.h"
#include "server_command.h"

CommandFactory::CommandFactory(Directory &myDir,
                    std::string config_file_path) : myDir(myDir),
                                                    myHP(config_file_path) {}

AllCommands CommandFactory::generate_commands(int *auth) {
  return AllCommands(auth, this->myDir, this->myHP);
}

CommandFactory::~CommandFactory() {}
