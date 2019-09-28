#ifndef CONF_FILE_H_
#define CONF_FILE_H_

#include <fstream>
#include <string>

#define KEY_DELIMITER '='
#define LINE_DELIMITER '\n'

class ConfFile {
  std::ifstream my_file;

 public:
  explicit ConfFile(std::string file_path);
  int get_pair(std::string &key, std::string &value);
  ~ConfFile();
};

#endif  // CONF_FILE_H_
