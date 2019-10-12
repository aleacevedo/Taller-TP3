#include <iostream>
#include "client_protocol.h"
#include "common_socket.h"

#define IP_POS 1
#define SERVICE_POS 2

int main(int argc, char* argv[]) {
  if (argc < 3) return 1;
  const std::string ip = argv[IP_POS];
  const std::string service = argv[SERVICE_POS];
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
      if (std::cin.eof()) {
        break;
      }
      if (prot.send(input) == 0)
        break;
    }
    skt.to_close();
  } catch(std::exception &e) {
  } catch(...) {
  }
}
