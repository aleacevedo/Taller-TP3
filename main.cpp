#include <iostream>

#include "honey_pot.h"
#include "directory.h"
#include "custom_errors.h"
#include "socket.h"
#include "command.h"

int main(int argc, char* argv[]) {
  FactoryCommand fact("entradas/config.cfg");
  std::cout << fact.getCommands()["SYST"]->execute(1, "") << "\n";
  std::cout << fact.getCommands()["USER"]->execute(1, "admin") << "\n";
  std::cout << fact.getCommands()["PASS"]->execute(1, "l33tP4s5") << "\n";
  std::cout << fact.getCommands()["SYST"]->execute(1, "") << "\n";
  std::cout << fact.getCommands()["LIST"]->execute(1, "") << "\n";
  std::cout << fact.getCommands()["MKD"]->execute(1, "newDir1") << "\n";
  std::cout << fact.getCommands()["MKD"]->execute(1, "newDir1") << "\n";
  std::cout << fact.getCommands()["MKD"]->execute(1, "newDir2") << "\n";
  std::cout << fact.getCommands()["LIST"]->execute(1, "") << "\n";
  std::cout << fact.getCommands()["RMD"]->execute(1, "newDir1") << "\n";
  std::cout << fact.getCommands()["RMD"]->execute(1, "newDir1") << "\n";
  std::cout << fact.getCommands()["LIST"]->execute(1, "") << "\n";
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
