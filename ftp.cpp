#include "ftp.h"
#include <iostream>
#include "custom_errors.h"

FTP::FTP(std::string conf_file_path) : myPot(conf_file_path),
                                       myDir(),
                                       logged() {}

std::string FTP::user(int client, std::string user) {
  if (this->logged.find(client) != this->logged.end())
    return this->myPot.get_msg_pass_required() + "\n";
  if (this->myPot.get_user().compare(user) != 0)
    return this->myPot.get_msg_not_logged() + "\n";
  this->logged[client] = false;
  return this->myPot.get_msg_pass_required() + "\n";
}

std::string FTP::pass(int client, std::string pass) {
  if (this->logged.find(client) == this->logged.end())
    return this->myPot.get_msg_login_fail() + "\n";
  if (this->myPot.get_password().compare(pass) != 0)
    return this->myPot.get_msg_login_fail() + "\n";
  this->logged[client] = true;
  return this->myPot.get_msg_login_success() + "\n";
}

std::string FTP::syst(int client) {
  if (!this->is_logged(client))
    return this->myPot.get_msg_not_logged() + "\n";
  return this->myPot.get_system_info() + "\n";
}

std::string FTP::list(int client) {
  std::string response;
  if (!this->is_logged(client))
    return this->myPot.get_msg_not_logged() + "\n";
  response = this->myPot.get_msg_list_begin() + "\n";
  response += this->myDir.list();
  response += this->myPot.get_msg_list_end() + "\n";
  return response;
}

std::string FTP::pwd(int client) {
  if (!this->is_logged(client))
    return this->myPot.get_msg_not_logged() + "\n";
  return this->myPot.get_current_dir() + "\n";
}

std::string FTP::mkd(int client, std::string dir) {
  if (!this->is_logged(client))
    return this->myPot.get_msg_not_logged() + "\n";
  try {
    this->myDir.add(FAKE_INFO + dir);
    return this->myPot.get_msg_mkd_success() + " " + dir + "\n";
  } catch(DirExistError &e) {
    return this->myPot.get_msg_mkd_fail() + "\n";
  }
}

std::string FTP::rmd(int client, std::string dir) {
  if (!this->is_logged(client))
    return this->myPot.get_msg_not_logged() + "\n";
  try {
    this->myDir.remove(FAKE_INFO + dir);
    return this->myPot.get_msg_rmd_success() + "\n";
  } catch(DirNotExistError &e) {
    return this->myPot.get_msg_rmd_fail() + "\n";
  }
}

FTP::~FTP() {}

bool FTP::is_logged(int client) {
  return this->logged.find(client) != this->logged.end()
         && this->logged[client];
}
