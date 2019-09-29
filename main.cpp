#include <iostream>

#include "honey_pot.h"
#include "directory.h"
#include "custom_errors.h"
#include "socket.h"

int main(int argc, char* argv[]) {
  std::string receive;
  try {
    std::cout << "Empiezo \n";
    Socket skt("8182");
        std::cout << "Inicializado \n";

    skt.to_listen();
        std::cout << "Escuchando \n";

    skt.to_accept();
    skt.to_receive(receive, 10);
    skt.to_send(receive, 10);
  } catch (FileError &e) {
    std::cout << e.what();
  } catch (KeyNotFoundError &e) {
    std::cout << e.what();
  } catch(DirNotExistError &e) {
    std::cout << e.what();
  } catch(DirExistError &e) {
    std::cout << e.what();
  }
}
