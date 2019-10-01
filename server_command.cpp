#include "server_command.h"
#include <iterator>

FactoryCommand::FactoryCommand(FTP &ftp) : commands(),
                                           ftp(ftp) {
  this->commands["NEWCLIENT"] = new NewClientCommand(this->ftp);
  this->commands["USER"] = new UserCommand(this->ftp);
  this->commands["PASS"] = new PassCommand(this->ftp);
  this->commands["SYST"] = new SystCommand(this->ftp);
  this->commands["LIST"] = new ListCommand(this->ftp);
  //  this->commands["HELP"] = new UserCommand(this->ftp);
  this->commands["PWD"] = new PWDCommand(this->ftp);
  this->commands["MKD"] = new MKDCommand(this->ftp);
  this->commands["RMD"] = new RMDCommand(this->ftp);
  this->commands["UNKNOW"] = new UNKCommand(this->ftp);
  this->commands["QUIT"] = new QuitCommand(this->ftp);
}

std::map<std::string, Command*> &FactoryCommand::getCommands() {
  return  this->commands;
}

FactoryCommand::~FactoryCommand() {
  std::map<std::string, Command*>::iterator it = this->commands.begin();
  for (; it != this->commands.end(); ++it)
    delete it->second;
}

NewClientCommand::NewClientCommand(FTP &ftp) : ftp(ftp) {}
int NewClientCommand::execute(int client, std::string user) {
  return this->ftp.newClient(client);
}
NewClientCommand::~NewClientCommand() {}

UserCommand::UserCommand(FTP &ftp) : ftp(ftp) {}
int UserCommand::execute(int client, std::string user) {
  return this->ftp.user(client, user);
}
UserCommand::~UserCommand() {}

PassCommand::PassCommand(FTP &ftp) : ftp(ftp) {}
int PassCommand::execute(int client, std::string pass) {
  return this->ftp.pass(client, pass);
}
PassCommand::~PassCommand() {}

SystCommand::SystCommand(FTP &ftp) : ftp(ftp) {}
int SystCommand::execute(int client, std::string null) {
  return this->ftp.syst(client);
}
SystCommand::~SystCommand() {}

ListCommand::ListCommand(FTP &ftp) : ftp(ftp) {}
int ListCommand::execute(int client, std::string null) {
  return this->ftp.list(client);
}
ListCommand::~ListCommand() {}
/*
HelpCommand::UserCommand(FTP &ftp) : ftp(ftp) {}
int HelpCommand::execute(int client) {
  return this->ftp.user(client, "");
}
int HelpCommand::execute(int client, std::string user) {
  return this->ftp.user(client, user);
}
HelpCommand::~HelpCommand() {}
*/
PWDCommand::PWDCommand(FTP &ftp) : ftp(ftp) {}
int PWDCommand::execute(int client, std::string null) {
  return this->ftp.pwd(client);
}
PWDCommand::~PWDCommand() {}

MKDCommand::MKDCommand(FTP &ftp) : ftp(ftp) {}
int MKDCommand::execute(int client, std::string dir) {
  return this->ftp.mkd(client, dir);
}
MKDCommand::~MKDCommand() {}

RMDCommand::RMDCommand(FTP &ftp) : ftp(ftp) {}
int RMDCommand::execute(int client, std::string user) {
  return this->ftp.rmd(client, user);
}
RMDCommand::~RMDCommand() {}

UNKCommand::UNKCommand(FTP &ftp) : ftp(ftp) {}
int UNKCommand::execute(int client, std::string user) {
  return this->ftp.unknow(client);
}
UNKCommand::~UNKCommand() {}


QuitCommand::QuitCommand(FTP &ftp) : ftp(ftp) {}
int QuitCommand::execute(int client, std::string user) {
  return this->ftp.quit(client);
}
QuitCommand::~QuitCommand() {}
