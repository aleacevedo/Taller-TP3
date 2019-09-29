#include "command.h"
#include <iterator>

FactoryCommand::FactoryCommand(std::string conf_file_paht) : commands(),
                                                  ftp(conf_file_paht) {
  this->commands["USER"] = new UserCommand(this->ftp);
  this->commands["PASS"] = new PassCommand(this->ftp);
  this->commands["SYST"] = new SystCommand(this->ftp);
  this->commands["LIST"] = new ListCommand(this->ftp);
  //  this->commands["HELP"] = new UserCommand(this->ftp);
  this->commands["PWD"] = new PWDCommand(this->ftp);
  this->commands["MKD"] = new MKDCommand(this->ftp);
  this->commands["RMD"] = new RMDCommand(this->ftp);
}

std::map<std::string, Command*> FactoryCommand::getCommands() {
  return  this->commands;
}

FactoryCommand::~FactoryCommand() {
  std::map<std::string, Command*>::iterator it = this->commands.begin();
  for (; it != this->commands.end(); ++it)
    delete it->second;
}

UserCommand::UserCommand(FTP &ftp) : ftp(ftp) {}
std::string UserCommand::execute(int client, std::string user) {
  return this->ftp.user(client, user);
}
UserCommand::~UserCommand() {}

PassCommand::PassCommand(FTP &ftp) : ftp(ftp) {}
std::string PassCommand::execute(int client, std::string pass) {
  return this->ftp.pass(client, pass);
}
PassCommand::~PassCommand() {}

SystCommand::SystCommand(FTP &ftp) : ftp(ftp) {}
std::string SystCommand::execute(int client, std::string null) {
  return this->ftp.syst(client);
}
SystCommand::~SystCommand() {}

ListCommand::ListCommand(FTP &ftp) : ftp(ftp) {}
std::string ListCommand::execute(int client, std::string null) {
  return this->ftp.list(client);
}
ListCommand::~ListCommand() {}
/*
HelpCommand::UserCommand(FTP &ftp) : ftp(ftp) {}
std::string HelpCommand::execute(int client) {
  return this->ftp.user(client, "");
}
std::string HelpCommand::execute(int client, std::string user) {
  return this->ftp.user(client, user);
}
HelpCommand::~HelpCommand() {}
*/
PWDCommand::PWDCommand(FTP &ftp) : ftp(ftp) {}
std::string PWDCommand::execute(int client, std::string null) {
  return this->ftp.pwd(client);
}
PWDCommand::~PWDCommand() {}

MKDCommand::MKDCommand(FTP &ftp) : ftp(ftp) {}
std::string MKDCommand::execute(int client, std::string dir) {
  return this->ftp.mkd(client, dir);
}
MKDCommand::~MKDCommand() {}

RMDCommand::RMDCommand(FTP &ftp) : ftp(ftp) {}
std::string RMDCommand::execute(int client, std::string user) {
  return this->ftp.rmd(client, user);
}
RMDCommand::~RMDCommand() {}
