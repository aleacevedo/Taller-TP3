#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <string>
#include "common_socket.h"

class Protocol {
  Socket &skt;

 public:
  explicit Protocol(Socket &skt);
  int send(int to, std::string msg);
  int receive(int from, std::string &received);
  int send(std::string msg);
  int receive(std::string &received);
  void quit(int client);
  ~Protocol();
};

#endif  //  PROTOCOL_H_
