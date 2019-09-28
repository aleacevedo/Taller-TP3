#include <iostream>

#include "honey_pot.h"
#include "file_error.h"
#include "key_not_found_error.h"

int main(int argc, char* argv[]) {
  try {
    HoneyPot pot("entradas/config.cfg");
    std::cout << pot.get_current_dir();
    std::cout << pot.get_msg_unknown_cmd();
  } catch (FileError &e) {
    std::cout << e.what();
  } catch (KeyNotFoundError &e) {
    std::cout << e.what();
  }
}
