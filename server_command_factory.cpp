#include "server_command_factory.h"
#include "server_command.h"

CommandFactory::CommandFactory(Directory &myDir,
                    std::string config_file_path) : myDir(myDir),
                                                    myHP(config_file_path) {}

AllCommands* CommandFactory::generateCommands(int &auth) {
  return new AllCommands(auth, this->myDir, this->myHP);
}

CommandFactory::~CommandFactory() {}
