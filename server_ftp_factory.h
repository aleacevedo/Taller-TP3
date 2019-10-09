#ifndef FTP_FACTORY_H_
#define FTP_FACTORY_H_

#include <string>
#include "server_directory.h"
#include "server_command_factory.h"
#include "server_ftp.h"

class FTPFactory {
  Directory myDir;
  CommandFactory myCommandFactory;
 public:
  explicit FTPFactory(std::string config_file_path);
  FTP generateFTP();
  ~FTPFactory();
};

#endif  //  FTP_FACTORY_H_
