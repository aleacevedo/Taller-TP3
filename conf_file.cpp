#include "conf_file.h"
#include "file_error.h"

ConfFile::ConfFile(std::string file_path) : my_file(file_path) {
  if (!this->my_file.good()) {
    this->my_file.close();
    throw FileError("Problem opening file \n");
  }
}

int ConfFile::get_pair(std::string &key, std::string &value) {
  std::getline(this->my_file, key, KEY_DELIMITER);
  std::getline(this->my_file, value, LINE_DELIMITER);
  if (this->my_file.eof()) return 1;
  return 0;
}

ConfFile::~ConfFile() {
  this->my_file.close();
}
