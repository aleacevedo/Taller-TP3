#include <iostream>

#include "honey_pot.h"
#include "directory.h"
#include "custom_errors.h"

int main(int argc, char* argv[]) {
  try {
    Directory dir;
    dir.add("First directory");
    dir.add("Second directory");
    std::cout << dir.list();
    dir.remove("First dire ctory");
    std::cout << dir.list();
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
