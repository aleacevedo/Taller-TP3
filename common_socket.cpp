#include "common_socket.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "common_custom_errors.h"

Socket::Socket(const std::string &service) : skt(),
                                       hints(),
                                       ptr(),
                                       is_server(false) {
  memset(&(this->hints), 0, sizeof hints);
  this->is_server = true;
  this->hints.ai_family = AF_INET;
  this->hints.ai_socktype = SOCK_STREAM;
  this->hints.ai_flags = AI_PASSIVE;
  this->getAddrInfo(service);
  this->create_skt();
  if (this->skt == -1) {
    freeaddrinfo(this->ptr);
    throw SocketError("Error creating socket");
  }
}

Socket::Socket(const std::string &host, const std::string &service) : skt(-1),
                                                        hints(),
                                                        ptr(),
                                                        is_server(true) {
  memset(&(this->hints), 0, sizeof hints);
  this->is_server = false;
  this->hints.ai_family = AF_INET;
  this->hints.ai_socktype = SOCK_STREAM;
  this->hints.ai_flags = 0;
  this->getAddrInfo(host, service);
  this->create_skt();
  if (this->skt == -1) {
    freeaddrinfo(this->ptr);
    throw SocketError("Error creating socket");
  }
}

Socket::Socket(int skt) : skt(skt),
                          hints(),
                          ptr(),
                          is_server(false) {}


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

void Socket::to_connect() {
  if (this->is_server) throw SocketError("It is server");
  if (connect(this->skt, this->ptr->ai_addr, this->ptr->ai_addrlen) == -1)
    throw SocketError("Error connecting: ");
}


int Socket::to_receive(std::string &buffer, int size) {
  int total_received = 0;
  int rest = size;
  char buff[MAX_RECEPTION] = "";
  std::string receiving = "";
  buffer = "";
  while (rest > 0) {
    int to_receive = size > 99 ? MAX_RECEPTION - 1 : rest;
    int received = 0;
    while (received < to_receive) {
      int s = recv(this->skt, buff + received, to_receive - received, 0);
      if (s == 0)
        return 0;
      if (s == -1) {
        throw SocketError("Error receiving: ");
      }
      receiving = receiving + std::string(buff);
      received += s;
    }
    rest -= received;
    total_received += received;
  }
  buffer = receiving;
  return total_received;
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

bool Socket::get_is_server() {
  return this->is_server;
}

void Socket::to_close() {
  shutdown(this->skt, SHUT_RDWR);
  close(this->skt);
}

Socket::~Socket() {
  freeaddrinfo(this->ptr);
  this->to_close();
}

void Socket::create_skt() {
  struct addrinfo *directions = this->ptr;
  for (; directions != NULL; directions = directions->ai_next) {
    this->skt = socket(directions->ai_family,
                  directions->ai_socktype,
                  directions->ai_protocol);
    if (this->skt == -1) continue;
    return;
  }
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
  if ((resAddr = getaddrinfo(host.c_str(),
                             service.c_str(),
                             &(this->hints),
                             &(this->ptr))) != 0)
    throw GetAddrInfoError(gai_strerror(resAddr));
}
