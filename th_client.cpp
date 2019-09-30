#include "th_client.h"
#include <string>

THClient::THClient(int client,
                   FTP &ftp,
                   FactoryCommand &factory,
                   Socket &skt) : keep_talking(true),
                                  client(client),
                                  ftp(ftp),
                                  factory(factory),
                                  skt(skt),
                                  protocol(skt) {}

void THClient::run() {
  this->protocol.send(this->client, this->ftp.newClient());
  while (keep_talking) {
    std::string cmd;
    if (this->protocol.receive(this->client, cmd) == 0)
      return;
    if (this->protocol.send(this->client, this->execute_command(cmd)) == 0)
      return;
  }
}

THClient::~THClient() {}

std::string THClient::execute_command(std::string received) {
  std::string arg = "";
  std::cout << received << "\n";
  size_t space_pos = received.find(" ");
  std::cout << space_pos << "\n";
  std::string cmd = received.substr(0, space_pos);
  if (space_pos != std::string::npos)
    arg = received.substr(space_pos+1);
  std::cout << received << "\n";
  std::cout << cmd << "\n";
  std::cout << arg << "\n";
  return this->factory.getCommands()[cmd]->execute(this->client, arg);
}