#include <iostream>
#include <string>
#include "common_custom_errors.h"
#include "server_th_server.h"

std::string  obtain_input() {
  std::string input;
  std::cout << "Ingrese el caracter q para salir\n";
  std::cin >> input;
  return input;
}

int main(int argc, char* argv[]) {
  try {
    THServer thServer("entradas/config.cfg", "8050");
    thServer.start();
    while (true) {
      if (obtain_input() == "q") {
        thServer.stop();
        break;
      }
    }
    thServer.join();
  } catch(std::exception &e) {
    std::cout << e.what();
  }
}
