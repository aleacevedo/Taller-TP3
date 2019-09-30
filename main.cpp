#include <iostream>

#include "honey_pot.h"
#include "directory.h"
#include "custom_errors.h"
#include "socket.h"
#include "command.h"
#include "th_client.h"

int main(int argc, char* argv[]) {
  try {
    FTP ftp("entradas/config.cfg");
    FactoryCommand fact(ftp);
    Socket skt("8182");
    skt.to_listen();
    int client = skt.to_accept();
    THClient th(client, ftp, fact, skt);
    th.run();
    std::cout << "esperando el join";
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
    std::cout << e.what();
  } catch(...) {
    std::cout << "Unknown Error";
  }
}
