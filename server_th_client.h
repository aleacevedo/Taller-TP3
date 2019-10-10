#ifndef TH_CLIENT_H_
#define TH_CLIENT_H_

#include <string>
#include <atomic>
#include "server_ftp_factory.h"
#include "server_ftp.h"
#include "common_socket.h"
#include "common_protocol.h"
#include "server_thread.h"


class THClient : public Thread {
  std::atomic<bool> keep_talking;
  Socket skt;
  Protocol protocol;
  FTP myFtp;

 public:
  explicit THClient(int skt, FTPFactory &ftpFactory);
  virtual void run();
  void stop();
  bool is_keep_talking();
  virtual ~THClient();
 private:
  int execute_command(std::string cmd);
};

#endif  //  TH_CLIENT_H_
