#include "server_ftp.h"


FTP::FTP(CommandFactory& commandFactory) : auth(new int(0)),
                                           my_commands(
                                              commandFactory.generate_commands(
                                                this->auth)) {}

FTP::FTP(FTP&& other) : auth(other.auth),
                        my_commands(std::move(other.my_commands)) {
  other.auth = nullptr;
}

std::string FTP::welcome() {
  return this->my_commands.get_welcome()->execute("");
}

std::string FTP::execute(std::string received) {
  return this->my_commands.get_commands(received)->execute(received);
}

FTP::~FTP() {
  delete this->auth;
}
