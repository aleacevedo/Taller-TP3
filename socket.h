#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define POOL_SIZE 20

class Socket {
  int skt;
  struct addrinfo hints;
  struct addrinfo *ptr;
  bool is_server;

 public:
  Socket(std::string service);
  Socket(std::string host, std::string service);
  void to_listen();
  int to_accept();
  int to_receive(std::string &buffer, int size);
  int to_send(std::string msg, int size);
  int to_receive(int skt, std::string &buffer, int size);
  int to_send(int skt, std::string msg, int size);
  bool get_is_server();
  ~Socket();
 private:
  void getAddrInfo(std::string service);
  void getAddrInfo(std::string host, std::string service);
};

#endif  //  SOCKET_H_
