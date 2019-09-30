#include "protocol.h"
#include <iostream>

Protocol::Protocol(Socket &skt) : skt(skt) {}

int Protocol::send(int to, std::string msg) {
  return skt.to_send(to, msg, msg.size());
}

int Protocol::receive(int from, std::string &received) {
  std::string caracter;
  skt.to_receive(from, caracter, 1);
  while (caracter.compare("\n")) {
    received = received + caracter;
    if (skt.to_receive(from, caracter, 1) == 0) 
      return 0;
  }
  return 1;
}

Protocol::~Protocol() {}
