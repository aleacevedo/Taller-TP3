#include "server_ftp.h"


FTP::FTP(CommandFactory& commandFactory) : auth(0),
                                           myCommands(
                                              commandFactory.generateCommands(
                                                this->auth)) {}

FTP::FTP(FTP&& other) : auth(other.auth),
                        myCommands(std::move(other.myCommands)) {}

std::string FTP::execute(std::string received) {
  return this->myCommands->getCommands(received)->execute(received);
}

FTP::~FTP() {
  delete myCommands;
}
