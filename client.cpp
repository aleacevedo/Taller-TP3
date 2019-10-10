#include <iostream>
#include "client_protocol.h"
#include "common_socket.h"



int main(int argc, char* argv[]) {
  try {
    Socket skt("127.0.0.1", "8050");
    ClientProtocol prot(skt);
    skt.to_connect();
    while (true) {
      std::string input;
      std::string output;
      if (prot.receive(output) == 0)
        break;
      std::cout << output + "\n";
      std::getline(std::cin, input);
      if (prot.send(input) == 0)
        break;
    }
    skt.to_close();
  } catch(std::exception &e) {
    std::cout << "ERROR EN EL MAIN \n";
    std::cout << e.what();
  } catch(...) {
    std::cout << "Unknown Error\n";
  }
}
