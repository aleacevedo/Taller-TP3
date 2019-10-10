#include "common_protocol.h"
#include <iostream>

Protocol::Protocol(Socket &skt) : skt(skt) {}

int Protocol::send(std::string msg) {
  msg += "\n";
  return this->skt.to_send(msg, msg.size());
}

int Protocol::receive(std::string &received) {
  std::string caracter;
  this->skt.to_receive(caracter, 1);
  while (caracter.compare("\n") != 0) {
      received = received + caracter;
    if (this->skt.to_receive(caracter, 1) == 0) {
      return 0;
    }
  }
  return 1;
}

Protocol::~Protocol() {}
