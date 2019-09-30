#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <string>
#include "socket.h"

class Protocol {
  Socket &skt;

 public:
  explicit Protocol(Socket &skt);
  int send(int to, std::string msg);
  int receive(int from, std::string &received);
  ~Protocol();
};

#endif  //  PROTOCOL_H_
