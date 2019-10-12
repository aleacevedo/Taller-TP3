#include "server_command.h"
#include <iterator>
#include "common_custom_errors.h"
#include "common_ftp_declarations.h"

#define NOT_LOGGED 0
#define WRONG_USER 1
#define GOOD_USER 2
#define LOGGED 3

AllCommands::AllCommands(int *auth,
                         Directory &dir,
                         HoneyPot &hp) : commands(),
                                         welcome_command(hp),
                                         unk_command(hp) {
  this->commands[USER_CMD] = new UserCommand(hp, auth);
  this->commands[PASS_CMD] = new PassCommand(hp, auth);
  this->commands[SYST_CMD] = new SystCommand(hp, auth);
  this->commands[LIST_CMD] = new ListCommand(hp, auth, dir);
  this->commands[PWD_CMD] = new PWDCommand(hp, auth);
  this->commands[MKD_CMD] = new MKDCommand(hp, auth, dir);
  this->commands[RMD_CMD] = new RMDCommand(hp, auth, dir);
  this->commands[HELP_CMD] = new HelpCommand(hp, auth, this->commands);
  this->commands[UNK_CMD] = new UNKCommand(hp);
  this->commands[QUIT_CMD] = new QuitCommand(hp);
}

AllCommands::AllCommands(AllCommands&& other) : commands(other.commands),
                                    welcome_command(other.welcome_command),
                                    unk_command(other.unk_command) {
  other.commands.clear();
}

Command* AllCommands::get_commands(std::string received) {
  std::string key_command = received.substr(0, received.find(" "));
  try {
    return this->commands.at(key_command);
  } catch(std::exception &e) {
    return &(this->unk_command);
  }
}

Command* AllCommands::get_welcome() {
  return &(this->welcome_command);
}

std::string get_param(std::string received) {
  if (received.find(" ") == std::string::npos)
    throw CommandError("Params not found");
  return received.substr(received.find(" ")+1);
}

AllCommands::~AllCommands() {
  std::map<std::string, Command*>::iterator it = this->commands.begin();
  for (; it != this->commands.end(); ++it)
    delete it->second;
}

WelcomeCommand::WelcomeCommand(HoneyPot &hp) : hp(hp) {}
std::string WelcomeCommand::execute(std::string receive) {
  std::string response = NEW_CLI_CODE;
  return response + " " + this->hp.get_msg_new_client();
}
WelcomeCommand::~WelcomeCommand() {}

UserCommand::UserCommand(HoneyPot &hp, int *auth) : hp(hp), auth(auth) {}
std::string UserCommand::execute(std::string received) {
  try {
    std::string user = get_param(received);
    std::string response ="";
    if (user == this->hp.get_user()) {
      response = USER_CODE;
      *this->auth = GOOD_USER;
      return response + " " + this->hp.get_msg_pass_required();
    }
    *this->auth = WRONG_USER;
    response = USER_CODE;
    return response + " " + this->hp.get_msg_pass_required();
  } catch (CommandError &e) {
    return e.what();
  }
}
UserCommand::~UserCommand() {}
PassCommand::PassCommand(HoneyPot &hp, int *auth) : hp(hp), auth(auth) {}
std::string PassCommand::execute(std::string received) {
  try {
    std::string response ="";
    if (*this->auth == GOOD_USER) {
      std::string pass = get_param(received);
      if (pass == this->hp.get_password()) {
        *this->auth = LOGGED;
        response = LOG_SUCC_CODE;
        return response + " " +this->hp.get_msg_login_success();
      }
      *this->auth = NOT_LOGGED;
      response = LOG_FAIL_CODE;
      return response + " " + this->hp.get_msg_login_fail();
    }
    if (*this->auth == WRONG_USER) {
      *this->auth = NOT_LOGGED;
      response = LOG_FAIL_CODE;
      return response + " " + this->hp.get_msg_login_fail();
    }
    response += NOT_LOG_CODE;
    return response + " " + this->hp.get_msg_not_logged();
  } catch (CommandError &e) {
    return e.what();
  }
}
PassCommand::~PassCommand() {}

SystCommand::SystCommand(HoneyPot &hp, int *auth) : hp(hp), auth(auth) {}
std::string SystCommand::execute(std::string received) {
  std::string response = NOT_LOG_CODE;
  if (*this->auth != LOGGED) {
    *this->auth = NOT_LOGGED;
    return response + " " + this->hp.get_msg_not_logged();
  }
  response = SYS_CODE;
  return response + " " + this->hp.get_system_info();
}
SystCommand::~SystCommand() {}

ListCommand::ListCommand(HoneyPot &hp, int *auth, Directory &dir) : hp(hp),
                                                                  auth(auth),
                                                                  dir(dir) {}
std::string ListCommand::execute(std::string received) {
  std::string response = NOT_LOG_CODE;
  if (*this->auth != LOGGED) {
    *this->auth = NOT_LOGGED;
    return response + " " + this->hp.get_msg_not_logged();
  }  response = LIST_BEG_CODE;
  response += " " + this->hp.get_msg_list_begin() + "\n";
  response += this->dir.list();
  response += LIST_END_CODE;
  response += " " + this->hp.get_msg_list_end();
  return response;
}
ListCommand::~ListCommand() {}
PWDCommand::PWDCommand(HoneyPot &hp, int *auth) : hp(hp), auth(auth) {}
std::string PWDCommand::execute(std::string received) {
  std::string response = NOT_LOG_CODE;
  if (*this->auth != 2) {
    *this->auth = 0;
    return response + " " + this->hp.get_msg_not_logged();
  }  response = PWD_CODE;
  return response + " " + this->hp.get_current_dir();
}
PWDCommand::~PWDCommand() {}
HelpCommand::HelpCommand(HoneyPot &hp, int *auth,
                        std::map<std::string, Command*> &commands) : hp(hp),
                                                                  auth(auth),
                                                        commands(commands) {}
std::string HelpCommand::execute(std::string received) {
  std::string response = NOT_LOG_CODE;
  if (*this->auth != LOGGED) {
    *this->auth = NOT_LOGGED;
    return response + " " + this->hp.get_msg_not_logged();
  }
  response = HELP_CODE;
  return response + " " + this->get_commands();
}
std::string HelpCommand::get_commands() {
  std::string aux = "";
  std::map<std::string, Command*>::iterator it = this->commands.begin();
  for (; it != this->commands.end(); ++it)
    aux += it->first + " ";
  aux.pop_back();
  return aux;
}
HelpCommand::~HelpCommand() {}

MKDCommand::MKDCommand(HoneyPot &hp, int *auth, Directory &dir) : hp(hp),
                                                                  auth(auth),
                                                                  dir(dir) {}
std::string MKDCommand::execute(std::string received) {
  std::string response = NOT_LOG_CODE;
  try {
    std::string response = NOT_LOG_CODE;
    if (*this->auth != LOGGED) {
      *this->auth = NOT_LOGGED;
      return response + " " + this->hp.get_msg_not_logged();
    }
    std::string toAdd = get_param(received);
    try {
      this->dir.add(FAKE_INFO + toAdd);
      response =  MKD_SUCC_CODE;
      response += " \"" + toAdd + "\"";
      return response + " " +this->hp.get_msg_mkd_success();
    } catch(DirExistError &e) {
      response = MKD_FAIL_CODE;
      return response + " " + this->hp.get_msg_mkd_fail();
    }
  } catch (CommandError &e) {
    return response + " " + this->hp.get_msg_mkd_fail();
  }
}
MKDCommand::~MKDCommand() {}

RMDCommand::RMDCommand(HoneyPot &hp, int *auth, Directory &dir) : hp(hp),
                                                                  auth(auth),
                                                                  dir(dir) {}
std::string RMDCommand::execute(std::string received) {
  std::string response = NOT_LOG_CODE;
  try {
    if (*this->auth != LOGGED) {
      *this->auth = NOT_LOGGED;
      return response + " " + this->hp.get_msg_not_logged();
    }
    std::string toRmv = received.substr(received.find(" ") + 1);
    try {
      this->dir.remove(FAKE_INFO + toRmv);
      response = RMD_SUCC_CODE;
      response += " \"" + toRmv + "\"";
      return response + " " + this->hp.get_msg_rmd_success();
    } catch(DirNotExistError &e) {
      response = RMD_FAIL_CODE;
      return response + " " + this->hp.get_msg_rmd_fail();
    }
  } catch (CommandError &e) {
      return this->hp.get_msg_rmd_fail();
  }
}
RMDCommand::~RMDCommand() {}

UNKCommand::UNKCommand(HoneyPot &hp) : hp(hp) {}
std::string UNKCommand::execute(std::string received) {
  std::string response = UNK_CODE;
  return response + " " + this->hp.get_msg_unknown_cmd();
}
UNKCommand::~UNKCommand() {}


QuitCommand::QuitCommand(HoneyPot &hp) : hp(hp) {}
std::string QuitCommand::execute(std::string received) {
  std::string response = QUIT_CODE;
  return response + " " +this->hp.get_msg_quit();
}
QuitCommand::~QuitCommand() {}
