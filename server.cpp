#include <iostream>
#include <string>
#include "common_custom_errors.h"
#include "server_ftp_factory.h"
#include "server_ftp.h"

std::string  obtain_input() {
  std::string input;
  std::cout << "Ingrese el caracter q para salir\n";
  std::cin >> input;
  return input;
}

int main(int argc, char* argv[]) {
  FTPFactory ftpFact("entradas/config.cfg");
  FTP ftp(ftpFact.generateFTP());
  std::cout << ftp.execute("USER admin") << "\n";
  std::cout << ftp.execute("PASS 1234") << "\n";
  std::cout << ftp.execute("MKD dir1") << "\n";
  std::cout << ftp.execute("MKD dir2") << "\n";
  std::cout << ftp.execute("LIST") << "\n";
  std::cout << ftp.execute("RMD dir1") << "\n";
  std::cout << ftp.execute("LIST") << "\n";
  std::cout << ftp.execute("RMD dir1") << "\n";
}
