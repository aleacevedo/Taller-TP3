#include <iostream>

#include "honey_pot.h"
#include "directory.h"
#include "custom_errors.h"
#include "socket.h"
#include "ftp.h"

int main(int argc, char* argv[]) {
  FTP ftp_pot("entradas/config.cfg");
  std::cout << ftp_pot.syst(1) << "\n";
  std::cout << ftp_pot.user(1, "admin") << "\n";
  std::cout << ftp_pot.pass(1, "l33tP4s5") << "\n";
  std::cout << ftp_pot.syst(1) << "\n";
  std::cout << ftp_pot.list(1) << "\n";
  std::cout << ftp_pot.mkd(1, "newDir1") << "\n";
  std::cout << ftp_pot.mkd(1, "newDir1") << "\n";
  std::cout << ftp_pot.mkd(1, "newDir2") << "\n";
  std::cout << ftp_pot.list(1) << "\n";
  std::cout << ftp_pot.rmd(1, "newDir1") << "\n";
  std::cout << ftp_pot.rmd(1, "newDir1") << "\n";
  std::cout << ftp_pot.list(1) << "\n";
  try {
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
