#ifndef FTP_H_
#define FTP_H_

#include <map>
#include <string>
#include "honey_pot.h"
#include "directory.h"

#define FAKE_INFO "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 "

class FTP {
  HoneyPot myPot;
  Directory myDir;
  std::map<int, bool> logged;
 public:
  explicit FTP(std::string conf_file_pahth);
  std::string user(int client, std::string user);
  std::string pass(int client, std::string pass);
  std::string syst(int client);
  std::string list(int cient);
  std::string pwd(int client);
  std::string mkd(int client, std::string dir);
  std::string rmd(int client, std::string dir);
  ~FTP();
 private:
  bool is_logged(int client);
};

#endif  //  FTP_H_
