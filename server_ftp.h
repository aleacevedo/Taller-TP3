#ifndef FTP_H_
#define FTP_H_

#include <map>
#include <string>
#include "server_command_factory.h"
#include "server_command.h"


class FTP {
  int* auth;
  AllCommands my_commands;
 public:
  explicit FTP(CommandFactory &commandFactory);
  FTP(FTP&& FTP);
  std::string welcome();
  std::string execute(std::string received);
  ~FTP();
};

#endif  //  FTP_H_
