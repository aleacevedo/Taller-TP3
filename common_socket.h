#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define POOL_SIZE 20
#define MAX_RECEPTION 100

class Socket {
  int skt;
  struct addrinfo hints;
  struct addrinfo *ptr;
  bool is_server;

 public:
  Socket(std::string service);
  Socket(std::string host, std::string service);
  Socket(int skt);
  void to_listen();
  int to_accept();
  void to_connect();
  int to_receive(std::string &buffer, int size);
  int to_send(std::string msg, int size);
  bool get_is_server();
  void to_close();
  ~Socket();
 private:
  void getAddrInfo(std::string service);
  void getAddrInfo(std::string host, std::string service);
  void create_skt();
};

#endif  //  SOCKET_H_
