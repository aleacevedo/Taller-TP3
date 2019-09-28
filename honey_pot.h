#ifndef FTP_H_
#define FTP_H_

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "key_def.h"

#define KEY_DELIMITER '='
#define LINE_DELIMITER '\n'

class HoneyPot {
  std::ifstream conf_file;
  std::map<std::string, std::string> configs;

 public:
  HoneyPot(std::string file_path);
  void load_confs();
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
  int read_one_pair(std::string &key, std::string &value);
  std::string get_conf(const std::string &key);
};

#endif  //  FTP_H_
