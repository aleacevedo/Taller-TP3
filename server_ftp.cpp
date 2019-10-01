#include "server_ftp.h"
#include <iostream>
#include <exception>
#include "common_custom_errors.h"

FTP::FTP(std::string conf_file_path,
         Protocol &protocol) : myPot(conf_file_path),
                               myDir(),
                               logged(),
                               protocol(protocol) {}

int FTP::newClient(int client) {
  std::string msg = this->myPot.get_msg_new_client() + "\n";
  return this->protocol.send(client, msg);
}

int FTP::user(int client, std::string user) {
  std::string msg;
  if (this->logged.find(client) != this->logged.end()) {
    msg = this->myPot.get_msg_pass_required() + "\n";
  } else if (this->myPot.get_user().compare(user) != 0) {
    msg = this->myPot.get_msg_not_logged() + "\n";
  } else {
    this->logged[client] = false;
    msg = this->myPot.get_msg_pass_required() + "\n";
  }
  return this->protocol.send(client, msg);
}

int FTP::pass(int client, std::string pass) {
  std::string msg;
  if (this->logged.find(client) == this->logged.end()) {
    msg = this->myPot.get_msg_login_fail() + "\n";
  } else if (this->myPot.get_password().compare(pass) != 0) {
    msg = this->myPot.get_msg_login_fail() + "\n";
  } else {
    this->logged[client] = true;
    msg = this->myPot.get_msg_login_success() + "\n";
  }
  return this->protocol.send(client, msg);
}

int FTP::syst(int client) {
  std::string msg;
  if (!this->is_logged(client))
    msg = this->myPot.get_msg_not_logged() + "\n";
  else
    msg = this->myPot.get_system_info() + "\n";
  return this->protocol.send(client, msg);
}

int FTP::list(int client) {
  std::string msg;
  if (!this->is_logged(client)) {
    msg =  this->myPot.get_msg_not_logged() + "\n";
  } else {
    msg = this->myPot.get_msg_list_begin() + "\n";
    msg += this->myDir.list();
    msg += this->myPot.get_msg_list_end() + "\n";
  }
  return this->protocol.send(client, msg);
}

int FTP::pwd(int client) {
  std::string msg;
  if (!this->is_logged(client))
    msg = this->myPot.get_msg_not_logged() + "\n";
  else
    msg = this->myPot.get_current_dir() + "\n";
  return this->protocol.send(client, msg);
}

int FTP::mkd(int client, std::string dir) {
  std::string msg;
  if (!this->is_logged(client))
    msg = this->myPot.get_msg_not_logged() + "\n";
  try {
    this->myDir.add(FAKE_INFO + dir);
    msg = this->myPot.get_msg_mkd_success() + " " + dir + "\n";
  } catch(DirExistError &e) {
    msg = this->myPot.get_msg_mkd_fail() + "\n";
  }
  return this->protocol.send(client, msg);
}

int FTP::rmd(int client, std::string dir) {
  std::string msg;
  if (!this->is_logged(client))
    msg = this->myPot.get_msg_not_logged() + "\n";
  try {
    this->myDir.remove(FAKE_INFO + dir);
    msg = this->myPot.get_msg_rmd_success() + "\n";
  } catch(DirNotExistError &e) {
    msg = this->myPot.get_msg_rmd_fail() + "\n";
  }
  return this->protocol.send(client, msg);
}

int FTP::unknow(int client) {
  std::string msg = this->myPot.get_msg_unknown_cmd() + "\n";
  return this->protocol.send(client, msg);
}

int FTP::quit(int client) {
  if (this->logged.find(client) != this->logged.end())
    this->logged.erase(client);
  std::string msg = this->myPot.get_msg_quit();
  this->protocol.send(client, msg);
  this->protocol.quit(client);
  return 0;
}

FTP::~FTP() {}

bool FTP::is_logged(int client) {
  return this->logged.find(client) != this->logged.end()
         && this->logged[client];
}
