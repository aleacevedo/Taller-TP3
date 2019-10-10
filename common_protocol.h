#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <string>
#include "common_socket.h"

class Protocol {
  Socket &skt;

 public:
  explicit Protocol(Socket &skt);
  int send(std::string msg);
  int receive(std::string &received);
  ~Protocol();
};

#endif  //  PROTOCOL_H_
