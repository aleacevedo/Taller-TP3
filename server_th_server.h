#ifndef TH_SERVER_H_
#define TH_SERVER_H_

#include <string>
#include <vector>
#include "server_th_client.h"
#include "server_thread.h"
#include "server_ftp.h"
#include "server_command.h"
#include "common_socket.h"
#include "common_protocol.h"


class THServer : public Thread {
  bool keep_alive;
  Socket skt;
  Protocol proto;
  FTP ftp;
  FactoryCommand fact;
  std::vector<THClient*> clients;

 public:
  explicit THServer(std::string config_file_path, std::string service);
  virtual void run();
  void stop();
  virtual ~THServer();
 private:
  void stop_dead_clients();
  void stop_all_clients();
};

#endif  //  TH_SERVER_H_