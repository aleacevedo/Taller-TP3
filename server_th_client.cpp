#include "server_th_client.h"
#include <string>
#include <exception>

THClient::THClient(int client,
                   FactoryCommand &factory,
                   Protocol &protocol) : keep_talking(true),
                                         client(client),
                                         factory(factory),
                                         protocol(protocol) {
}

void THClient::run() {
  try {
    this->factory.getCommands().at("NEWCLIENT")->execute(this->client, "");
    while (this->keep_talking) {
      std::string cmd;
      if (this->protocol.receive(this->client, cmd) == 0)
        this->keep_talking = false;
      if (this->execute_command(cmd) == 0)
        this->keep_talking = false;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR EN EL THCLIENT " << this->client << "\n";
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
  this->protocol.quit(this->client);
}

THClient::~THClient() {}

int THClient::execute_command(std::string received) {
  std::string arg = "";
  size_t space_pos = received.find(" ");
  std::string cmd = received.substr(0, space_pos);
  if (space_pos != std::string::npos)
    arg = received.substr(space_pos+1);
  try {
    return this->factory.getCommands().at(cmd)->execute(this->client, arg);
  } catch (std::exception &e)  {
    return this->factory.getCommands().at("UNKNOW")->execute(this->client, arg);
  }
}