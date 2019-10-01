#ifndef TH_CLIENT_H_
#define TH_CLIENT_H_

#include <string>
#include "thread.h"
#include "ftp.h"
#include "command.h"
#include "socket.h"
#include "protocol.h"


class THClient : public Thread {
  bool keep_talking;
  int client;
  FactoryCommand &factory;
  Protocol &protocol;

 public:
  explicit THClient(int client, FactoryCommand &factory, Protocol &protocol);
  virtual void run();
  void stop();
  bool is_keep_talking();
  virtual ~THClient();
 private:
  int execute_command(std::string cmd);
};

#endif  //  TH_CLIENT_H_
