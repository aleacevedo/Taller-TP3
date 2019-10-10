#ifndef TH_SERVER_H_
#define TH_SERVER_H_

#include <string>
#include <vector>
#include <atomic>
#include "server_th_client.h"
#include "server_thread.h"
#include "server_ftp_factory.h"
#include "server_command.h"
#include "common_socket.h"
#include "common_protocol.h"


class THServer : public Thread {
  std::atomic<bool> keep_alive;
  Socket skt;
  std::vector<THClient*> clients;
  FTPFactory ftpFact;

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