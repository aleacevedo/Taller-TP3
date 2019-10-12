#include <iostream>
#include <string>
#include "common_custom_errors.h"
#include "server_th_server.h"

#define SERVICE_POS 1
#define CONFIG_POS 2

std::string  obtain_input() {
  std::string input;
  std::cout << "Ingrese el caracter q para salir\n";
  std::cin >> input;
  return input;
}

int main(int argc, char* argv[]) {
  if (argc < 3) return 1;
  std::string service = argv[SERVICE_POS];
  std::string config_file = argv[CONFIG_POS];
  try {
    THServer thServer(config_file, service);
    thServer.start();
    while (true) {
      if (obtain_input() == "q") {
        thServer.stop();
        break;
      }
    }
    thServer.join();
  } catch(std::exception &e) {
  } catch(...) {
  }
}
