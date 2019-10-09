#include "server_command.h"
#include <iterator>
#include "common_custom_errors.h"

AllCommands::AllCommands(int &auth, Directory &dir, HoneyPot &hp) : commands() {
  this->commands["NEWCLIENT"] = new NewClientCommand(hp);
  this->commands["USER"] = new UserCommand(hp, auth);
  this->commands["PASS"] = new PassCommand(hp, auth);
  this->commands["SYST"] = new SystCommand(hp, auth);
  this->commands["LIST"] = new ListCommand(hp, auth, dir);
  this->commands["PWD"] = new PWDCommand(hp, auth);
  this->commands["MKD"] = new MKDCommand(hp, auth, dir);
  this->commands["RMD"] = new RMDCommand(hp, auth, dir);
  this->commands["UNKNOW"] = new UNKCommand(hp);
  this->commands["QUIT"] = new QuitCommand(hp);
}

AllCommands::AllCommands(AllCommands&& other) : commands(other.commands) {}

Command* AllCommands::getCommands(std::string received) {
  std::string key_command = received.substr(0, received.find(" "));
  try {
    return this->commands.at(key_command);
  } catch(std::exception &e) {
    return this->commands.at("UNKNOW");
  }
}

void AllCommands::operator= (const AllCommands& other) {
  this->commands = other.commands;
}

AllCommands::~AllCommands() {
  std::map<std::string, Command*>::iterator it = this->commands.begin();
  for (; it != this->commands.end(); ++it)
    delete it->second;
}

NewClientCommand::NewClientCommand(HoneyPot &hp) : hp(hp) {}
std::string NewClientCommand::execute(std::string receive) {
  return this->hp.get_msg_new_client();
}
NewClientCommand::~NewClientCommand() {}

UserCommand::UserCommand(HoneyPot &hp, int &auth) : hp(hp), auth(auth) {}
std::string UserCommand::execute(std::string received) {
  std::string user = received.substr(received.find(" "));
  if (user == this->hp.get_user()) {
    auth = 1;
    return this->hp.get_msg_pass_required();
  }
  auth = 0;
  return this->hp.get_msg_not_logged();
}
UserCommand::~UserCommand() {}

PassCommand::PassCommand(HoneyPot &hp, int &auth) : hp(hp), auth(auth) {}
std::string PassCommand::execute(std::string received) {
  if (auth == 1) {
    std::string pass = received.substr(received.find(" "));
    if (pass == this->hp.get_password()) {
      auth = 2;
      return this->hp.get_msg_login_success();
    }
    return this->hp.get_msg_login_fail();
  }
  return this->hp.get_msg_not_logged();
}
PassCommand::~PassCommand() {}

SystCommand::SystCommand(HoneyPot &hp, int &auth) : hp(hp), auth(auth) {}
std::string SystCommand::execute(std::string received) {
  if (this->auth != 2) return this->hp.get_msg_not_logged();
  return this->hp.get_system_info();
}
SystCommand::~SystCommand() {}

ListCommand::ListCommand(HoneyPot &hp, int &auth, Directory &dir) : hp(hp),
                                                                  auth(auth),
                                                                  dir(dir) {}
std::string ListCommand::execute(std::string received) {
  if (this->auth != 2) return this->hp.get_msg_not_logged();
  std::string response = this->hp.get_msg_list_begin();
  response = response + this->dir.list();
  response = response + this->hp.get_msg_list_end();
  return response;

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
PWDCommand::PWDCommand(HoneyPot &hp, int &auth) : hp(hp), auth(auth) {}
std::string PWDCommand::execute(std::string received) {
  return this->hp.get_current_dir();
}
PWDCommand::~PWDCommand() {}

MKDCommand::MKDCommand(HoneyPot &hp, int &auth, Directory &dir) : hp(hp),
                                                                  auth(auth),
                                                                  dir(dir) {}
std::string MKDCommand::execute(std::string received) {
  if (this->auth != 2) return this->hp.get_msg_not_logged();
  std::string toAdd = received.substr(received.find(" "));
  try {
    this->dir.add(FAKE_INFO + toAdd);
    return this->hp.get_msg_mkd_success();
  } catch(DirExistError &e) {
    return this->hp.get_msg_mkd_fail();
  }
}
MKDCommand::~MKDCommand() {}

RMDCommand::RMDCommand(HoneyPot &hp, int &auth, Directory &dir) : hp(hp),
                                                                  auth(auth),
                                                                  dir(dir) {}
std::string RMDCommand::execute(std::string received) {
  if (this->auth != 2) return this->hp.get_msg_not_logged();
  std::string toAdd = received.substr(received.find(" "));
  try {
    this->dir.remove(FAKE_INFO + toAdd);
    return this->hp.get_msg_rmd_success();
  } catch(DirNotExistError &e) {
    return this->hp.get_msg_rmd_fail();
  }
}
RMDCommand::~RMDCommand() {}

UNKCommand::UNKCommand(HoneyPot &hp) : hp(hp) {}
std::string UNKCommand::execute(std::string received) {
  return this->hp.get_msg_unknown_cmd();
}
UNKCommand::~UNKCommand() {}


QuitCommand::QuitCommand(HoneyPot &hp) : hp(hp) {}
std::string QuitCommand::execute(std::string received) {
  return this->hp.get_msg_quit();
}
QuitCommand::~QuitCommand() {}
