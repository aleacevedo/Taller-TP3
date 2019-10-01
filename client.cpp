#include <iostream>



int main(int argc, char* argv[]) {
  try {
    std::cout << "HOLA MUNDO \n";
  } catch(std::exception &e) {
    std::cout << "ERROR EN EL MAIN \n";
    std::cout << e.what();
  } catch(...) {
    std::cout << "Unknown Error\n";
  }
}
