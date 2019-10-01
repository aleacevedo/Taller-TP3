#include <iostream>
#include <string>
#include "server_th_server.h"
#include "common_custom_errors.h"

std::string  obtain_input() {
  std::string input;
  std::cout << "Ingrese el caracter q para salir\n";
  std::cin >> input;
  return input;
}

int main(int argc, char* argv[]) {
  try {
    THServer th("entradas/config.cfg", "81");
    th.start();
    while (obtain_input().compare("q") != 0) {}
    th.stop();
    th.join();
  } catch (FileError &e) {
    std::cout << e.what();
  } catch (KeyNotFoundError &e) {
    std::cout << e.what();
  } catch(DirNotExistError &e) {
    std::cout << e.what();
  } catch(DirExistError &e) {
    std::cout << e.what();
  } catch(std::exception &e) {
    std::cout << "ERROR EN EL MAIN \n";
    std::cout << e.what();
  } catch(...) {
    std::cout << "Unknown Error\n";
  }
}
