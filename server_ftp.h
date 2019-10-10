#ifndef FTP_H_
#define FTP_H_

#include <map>
#include <string>
#include "server_command_factory.h"
#include "server_command.h"


class FTP {
  int* auth;
  AllCommands myCommands;
 public:
  explicit FTP(CommandFactory &commandFactory);
  FTP(FTP&& FTP);
  std::string execute(std::string received);
  ~FTP();
};

#endif  //  FTP_H_
