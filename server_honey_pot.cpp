#include "server_honey_pot.h"
#include "common_custom_errors.h"

HoneyPot::HoneyPot(std::string file_path) : conf_file(file_path),
                                            configs() {
  std::string key;
  std::string value;
  while (this->conf_file.get_pair(key, value) != 1) {
    configs[key] = value;
  }
}

std::string HoneyPot::get_user() {
  return this->get_conf(USER_KEY);
}
std::string HoneyPot::get_password() {
  return this->get_conf(PASS_KEY);
}
std::string HoneyPot::get_msg_new_client() {
  return this->get_conf(MSG_NEW_CLIENT_KEY);
}
std::string HoneyPot::get_msg_not_logged() {
  return this->get_conf(MSG_NOT_LOG_KEY);
}
std::string HoneyPot::get_msg_pass_required() {
  return this->get_conf(MSG_PASS_REQUIRED_KEY);
}
std::string HoneyPot::get_msg_login_success() {
  return this->get_conf(MSG_LOGIN_SUCC_KEY);
}
std::string HoneyPot::get_msg_login_fail() {
  return this->get_conf(MSG_LOGIN_FAIL_KEY);
}
std::string HoneyPot::get_system_info() {
  return this->get_conf(SYS_INFO_KEY);
}
std::string HoneyPot::get_current_dir() {
  return this->get_conf(CURRENT_DIR_KEY);
}
std::string HoneyPot::get_msg_list_begin() {
  return this->get_conf(MSG_LIST_BEGIN_KEY);
}
std::string HoneyPot::get_msg_list_end() {
  return this->get_conf(MSG_LIST_END_KEY);
}
std::string HoneyPot::get_msg_mkd_success() {
  return this->get_conf(MSG_MKD_SUCC_KEY);
}
std::string HoneyPot::get_msg_mkd_fail() {
  return this->get_conf(MSG_MKD_FAIL_KEY);
}
std::string HoneyPot::get_msg_rmd_success() {
  return this->get_conf(MSG_RMD_SUCC_KEY);
}
std::string HoneyPot::get_msg_rmd_fail() {
  return this->get_conf(MSG_RMD_FAIL_KEY);
}
std::string HoneyPot::get_msg_unknown_cmd() {
  return this->get_conf(MSG_UNKNOW_KEY);
}
std::string HoneyPot::get_msg_quit() {
  return this->get_conf(MSG_QUIT_KEY);
}

HoneyPot::~HoneyPot() {}

std::string HoneyPot::get_conf(const std::string &key) {
  try {
    return this->configs.at(key);
  } catch (const std::out_of_range &e) {
    throw KeyNotFoundError(std::string(key + " not found").c_str());
  }
}
