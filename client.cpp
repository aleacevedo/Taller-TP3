#include <iostream>
#include "common_protocol.h"
#include "common_socket.h"



int main(int argc, char* argv[]) {
  try {
    Socket skt("127.0.0.1", "81");
    Protocol prot(skt);
    skt.to_connect();
    while (true) {
      std::string input;
      std::string output;
      std::cin >> input;
      prot.send(input);
      prot.receive(output);
      std::cout << output;
    }
  } catch(std::exception &e) {
    std::cout << "ERROR EN EL MAIN \n";
    std::cout << e.what();
  } catch(...) {
    std::cout << "Unknown Error\n";
  }
}
