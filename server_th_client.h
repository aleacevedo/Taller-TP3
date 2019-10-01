#ifndef TH_CLIENT_H_
#define TH_CLIENT_H_

#include <string>
#include "server_thread.h"
#include "server_ftp.h"
#include "server_command.h"
#include "common_socket.h"
#include "common_protocol.h"


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
