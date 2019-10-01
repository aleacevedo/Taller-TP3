#include "common_protocol.h"
#include <iostream>

Protocol::Protocol(Socket &skt) : skt(skt) {}

int Protocol::send(int to, std::string msg) {
  return this->skt.to_send(to, msg, msg.size());
}

int Protocol::receive(int from, std::string &received) {
  std::string caracter;
  this->skt.to_receive(from, caracter, 1);
  while (caracter.compare("\n") != 0 && caracter.compare("\r") != 0) {
    received = received + caracter;
    if (this->skt.to_receive(from, caracter, 1) == 0)
      return 0;
  }
  return 1;
}

void Protocol::quit(int client) {
  this->skt.close_skt(client);
}

Protocol::~Protocol() {}
