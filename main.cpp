#include <iostream>

#include "honey_pot.h"
#include "directory.h"
#include "custom_errors.h"
#include "socket.h"

int main(int argc, char* argv[]) {
  std::string receive;
  try {
    std::cout << "Empiezo \n";
    std::string service("8182");
    Socket skt(service);
    std::cout << "Inicializado \n";
    skt.to_listen();
    std::cout << "Escuchando \n";
    int client = skt.to_accept();
    std::cout << "Cliente aceptado \n";
    skt.to_receive(client, receive, 10);
    std::cout << "Recibi " << receive << "\n";
    skt.to_send(client, receive, 10);
  } catch (FileError &e) {
    std::cout << e.what();
  } catch (KeyNotFoundError &e) {
    std::cout << e.what();
  } catch(DirNotExistError &e) {
    std::cout << e.what();
  } catch(DirExistError &e) {
    std::cout << e.what();
  } catch(std::exception &e) {
    std::cout << e.what();
  } catch(...) {
    std::cout << "Unknown Error";
  }
}
