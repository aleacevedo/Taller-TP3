#include "socket.h"
#include <iostream>
#include "custom_errors.h"

Socket::Socket(std::string service) : skt(),
                                       hints(),
                                       ptr(),
                                       is_server(false) {
  this->is_server = true;
  this->hints.ai_family = AF_INET;
  this->hints.ai_socktype = SOCK_STREAM;
  this->hints.ai_flags = AI_PASSIVE;
  this->getAddrInfo(service);
  this->skt = socket(this->ptr->ai_family,
                this->ptr->ai_socktype,
                this->ptr->ai_protocol);
  if (this->skt == -1) {
    freeaddrinfo(this->ptr);
    throw SocketError("Error creating socket");
  }
}

Socket::Socket(std::string host, std::string service) {
  struct addrinfo *directions = this->ptr;
  this->is_server = false;
  this->hints.ai_family = AF_INET;
  this->hints.ai_socktype = SOCK_STREAM;
  this->hints.ai_flags = 0;
  this->getAddrInfo(host, service);
  for (; directions != NULL; directions = directions->ai_next) {
    this->skt = socket(this->ptr->ai_family,
                  this->ptr->ai_socktype,
                  this->ptr->ai_protocol);
    if (this->skt == -1) continue;
    return;
  }
  if (this->skt == -1) {
    freeaddrinfo(this->ptr);
    throw SocketError("Error creating socket");
  }
}

void Socket::to_listen() {
  if (!this->is_server) throw SocketError("It is not server");
  if (bind(this->skt, this->ptr->ai_addr, this->ptr->ai_addrlen) == -1)
    throw SocketError("Error binding: ");
  if (listen(this->skt, POOL_SIZE) == -1)
    throw SocketError("Error listening: ");
}

int Socket::to_accept() {
  if (!this->is_server) throw SocketError("It is not server");
  int connection = accept(this->skt, NULL, NULL);
  if (connection == -1)
    throw SocketError("Error accepting: ");
  return connection;
}

int Socket::to_receive(std::string &buffer, int size) {
  int received = 0;
  char *buff = new char[size+1]();
  if (this->is_server) throw SocketError("It is server");
  while (received < size) {
    int s = recv(this->skt, buff + received, size - received, 0);
    if (s == 0)
      return 0;
    if (s == -1) {
      throw SocketError("Error receiving: ");
    }
    received += s;
  }
  buffer = std::string(buff);
  delete[] buff;
  return received;
}

int Socket::to_receive(int skt, std::string &buffer, int size) {
  int received = 0;
  char *buff = new char[size+1]();
  if (!this->is_server) throw SocketError("It is not server");
  while (received < size) {
    int s = recv(skt, buff + received, size - received, 0);
    if (s == 0)
      return 0;
    if (s == -1) {
      throw SocketError("Error receiving: ");
    }
    received += s;
  }
  buffer = std::string(buff);
  delete[] buff;
  return received;
}

int Socket::to_send(std::string msg, int size) {
  int sent = 0;
  while (sent < size) {
    int s = send(this->skt, msg.substr(sent).c_str(), size - sent, 0);
    sent += s;
    if (s == 0)
      return 0;
    if (s == -1)
      throw SocketError("Error sending: ");
  }
  return sent;
}

int Socket::to_send(int skt, std::string msg, int size) {
  int sent = 0;
  while (sent < size) {
    int s = send(skt, msg.substr(sent).c_str(), size - sent, 0);
    sent += s;
    if (s == 0)
      return 0;
    if (s == -1)
      throw SocketError("Error sending: ");
  }
  return sent;
}

bool Socket::get_is_server() {
  return this->is_server;
}

void Socket::close_skt(int skt) {
  shutdown(skt, SHUT_RDWR);
  close(skt);
}

Socket::~Socket() {
  freeaddrinfo(this->ptr);
  shutdown(this->skt, SHUT_RDWR);
  close(this->skt);
}

void Socket::getAddrInfo(std::string service) {
  int resAddr;
  if ((resAddr = getaddrinfo(NULL, service.c_str(),
                    &(this->hints),
                    &(this->ptr))) != 0)
    throw GetAddrInfoError(gai_strerror(resAddr));
}

void Socket::getAddrInfo(std::string host, std::string service) {
  int resAddr;
  if ((resAddr = getaddrinfo(host.c_str(), service.c_str(),
                    &(this->hints),
                    &(this->ptr))) != 0)
    throw GetAddrInfoError(gai_strerror(resAddr));
}