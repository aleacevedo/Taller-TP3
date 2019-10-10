#include "client_protocol.h"
#include <iostream>
#include "common_ftp_declarations.h"

ClientProtocol::ClientProtocol(Socket &skt) : protocol(skt) {}

int ClientProtocol::send(std::string msg) {
  return this->protocol.send(msg);
}

int ClientProtocol::receive(std::string &buffer) {
  if (this->protocol.receive(buffer) == 0)
    return 0;
  std::string code = this->get_code(buffer);
  std::cout << "MESSAGE CODE " << code << " \n";
  if (code == LIST_BEG_CODE)
    if (this->receive_list(buffer) == 0) return 0;
  if (code == QUIT_CODE)
    return 0;
  return 1;
}

ClientProtocol::~ClientProtocol() {}

int ClientProtocol::receive_list(std::string &buffer) {
  std::string aux = "";
  while (true) {
    std::string code = this->get_code(aux);
    if (code == LIST_END_CODE)
      return 1;
    if (this->protocol.receive(aux) == 0)
      return 0;
    buffer += aux;
  }
}

std::string ClientProtocol::get_code(std::string received) {
  if (received.find(" ") != std::string::npos) {
    return received.substr(0, received.find(" "));
  }
  return "";
}
