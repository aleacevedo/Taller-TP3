#include <iostream>
#include "client_protocol.h"
#include "common_socket.h"



int main(int argc, char* argv[]) {
  if (argc < 3) return 1;
  const std::string ip = argv[1];
  const std::string service = argv[2];
  try {
    Socket skt(ip, service);
    ClientProtocol prot(skt);
    skt.to_connect();
    while (true) {
      std::string input;
      std::string output;
      if (prot.receive(output) == 0) {
        std::cout << output + "\n";
        break;
      }
      std::cout << output + "\n";
      std::getline(std::cin, input);
      if (prot.send(input) == 0)
        break;
    }
    skt.to_close();
  } catch(std::exception &e) {
  } catch(...) {
  }
}
