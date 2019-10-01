#ifndef HONEY_POT_H_
#define HONEY_POT_H_

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "server_key_def.h"
#include "server_conf_file.h"


class HoneyPot {
  ConfFile conf_file;
  std::map<std::string, std::string> configs;

 public:
  HoneyPot(std::string file_path);
  std::string get_user();
  std::string get_password();
  std::string get_msg_new_client();
  std::string get_msg_not_logged();
  std::string get_msg_pass_required();
  std::string get_msg_login_success();
  std::string get_msg_login_fail();
  std::string get_system_info();
  std::string get_current_dir();
  std::string get_msg_list_begin();
  std::string get_msg_list_end();
  std::string get_msg_mkd_success();
  std::string get_msg_mkd_fail();
  std::string get_msg_rmd_success();
  std::string get_msg_rmd_fail();
  std::string get_msg_unknown_cmd();
  std::string get_msg_quit();
  ~HoneyPot();

 private:
  std::string get_conf(const std::string &key);
};

#endif  //  HONEY_POT_H_
