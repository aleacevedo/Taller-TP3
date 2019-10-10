#include "server_ftp.h"


FTP::FTP(CommandFactory& commandFactory) : auth(new int(0)),
                                           myCommands(
                                              commandFactory.generateCommands(
                                                this->auth)) {}

FTP::FTP(FTP&& other) : auth(other.auth),
                        myCommands(std::move(other.myCommands)) {
  other.auth = nullptr;
}

std::string FTP::execute(std::string received) {
  return this->myCommands.getCommands(received)->execute(received);
}

FTP::~FTP() {
  delete this->auth;
}
