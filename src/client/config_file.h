#ifndef QUANTUM_CHESS_PROJ_CONFIG_FILE_H
#define QUANTUM_CHESS_PROJ_CONFIG_FILE_H

#include <string>
#include <map>
#include <fstream>

class ConfigFile {
  std::map<std::string, std::string> configs;

  void loadFile(std::ifstream &file);

public:
  explicit ConfigFile(std::ifstream &file);

  const std::string & getValue(const std::string &key);
};


#endif //QUANTUM_CHESS_PROJ_CONFIG_FILE_H
