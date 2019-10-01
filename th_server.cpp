#include "th_server.h"

THServer::THServer(std::string config_file_path,
                   std::string service) : keep_alive(true),
                                          skt(service),
                                          proto(skt),
                                          ftp(config_file_path, proto),
                                          fact(ftp),
                                          clients() {
  this->skt.to_listen();
}

void THServer::run() {
  try {
    while (this->keep_alive) {
      this->stop_dead_clients();
      int client = this->skt.to_accept();
      this->clients.push_back(new THClient(client, this->fact, this->proto));
      this->clients.back()->start();
    }
  } catch (std::exception &e) {
    std::cout << "ERROR EN EL THSERVER \n";
    std::cout << e.what();
  } catch (...) {
    std::cout << "UNKNOW ERROR \n";
  }
}

void THServer::stop() {
  this->stop_all_clients();
  this->skt.close_me();
  this->keep_alive = false;
}

THServer::~THServer() {}

void THServer::stop_dead_clients() {
  for (THClient *client : clients) {
    if (!client->is_keep_talking()) {
      client->join();
    }
  }
}

void THServer::stop_all_clients() {
  for (THClient *client : clients) {
    if (client->is_keep_talking()) {
      client->stop();
      client->join();
    }
    delete client;
  }
}



