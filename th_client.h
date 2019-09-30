#ifndef TH_CLIENT_H_
#define TH_CLIENT_H_

#include <thread>
#include <string>
#include "ftp.h"
#include "command.h"
#include "socket.h"
#include "protocol.h"


class THClient : public std::thread {
  bool keep_talking;
  int client;
  FTP &ftp;
  FactoryCommand &factory;
  Socket &skt;
  Protocol protocol;

 public:
  explicit THClient(int client, FTP &ftp, FactoryCommand &factory, Socket &skt);
  virtual void run();
  void stop();
  virtual ~THClient();
 private:
  std::string execute_command(std::string cmd);
};

#endif  //  TH_CLIENT_H_
