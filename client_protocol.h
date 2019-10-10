#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include "common_socket.h"
#include "common_protocol.h"

class ClientProtocol {
  Protocol protocol;

 public:
  explicit ClientProtocol(Socket &skt);
  int send(std::string msg);
  int receive(std::string &received);
  ~ClientProtocol();
 private:
  int receive_list(std::string &received);
  std::string get_code(std::string received);
};

#endif  //  PROTOCOL_H_
