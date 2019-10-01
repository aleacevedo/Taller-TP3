#ifndef FTP_H_
#define FTP_H_

#include <map>
#include <string>
#include "server_honey_pot.h"
#include "server_directory.h"
#include "common_protocol.h"

#define FAKE_INFO "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 "

class FTP {
  HoneyPot myPot;
  Directory myDir;
  std::map<int, bool> logged;
  Protocol &protocol;
 public:
  explicit FTP(std::string conf_file_pahth, Protocol &protocol);
  int newClient(int client);
  int user(int client, std::string user);
  int pass(int client, std::string pass);
  int syst(int client);
  int list(int cient);
  int pwd(int client);
  int mkd(int client, std::string dir);
  int rmd(int client, std::string dir);
  int unknow(int client);
  int quit(int client);
  ~FTP();
 private:
  bool is_logged(int client);
};

#endif  //  FTP_H_
