#include "server_ftp_factory.h"

FTPFactory::FTPFactory(std::string config_file_path) : myDir(),
                          myCommandFactory(myDir, config_file_path) {}

FTP FTPFactory::generateFTP() {
  return FTP(this->myCommandFactory);
}

FTPFactory::~FTPFactory() {}
