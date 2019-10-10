#include "server_th_client.h"
#include <string>
#include <exception>

THClient::THClient(int skt,
                   FTPFactory &ftpFactory) : keep_talking(true),
                                             skt(skt),
                                             protocol(this->skt),
                                             myFtp(ftpFactory.generateFTP()) {}

void THClient::run() {
  try {
    std::string welcome = this->myFtp.execute("NEWCLIENT");
    this->protocol.send(welcome);
    while (this->keep_talking) {
      std::string cmd;
      if (this->protocol.receive(cmd) == 0) {
        this->keep_talking = false;
        return;
      }
      std::string response = this->myFtp.execute(cmd);
      if (this->protocol.send(response) == 0) {
        this->keep_talking = false;
        return;
      }
    }
  } catch (std::exception &e) {
    std::cout << e.what();
  } catch (...) {
    std::cout << "UNKNOW ERROR\n";
  }
  this->keep_talking = false;
}

bool THClient::is_keep_talking() {
  return this->keep_talking;
}

void THClient::stop() {
  this->keep_talking = false;
  this->skt.to_close();
}

THClient::~THClient() {}