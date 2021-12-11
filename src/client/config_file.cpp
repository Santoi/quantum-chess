#include "config_file.h"
#include <fstream>

#define CHARACTER '='

ConfigFile::ConfigFile(std::ifstream &file) : configs() {
  loadFile(file);
}

void ConfigFile::loadFile(std::ifstream &file) {
  while (!file.eof() && file.peek() != EOF) {
    std::string line, key, value;
    std::getline(file, line);
    size_t character_position = line.find_first_of(CHARACTER);
    if (character_position == std::string::npos)
      throw std::runtime_error("error reading config file");
    key = line.substr(0, character_position);
    value = line.substr(character_position + 1, std::string::npos);
    if (key.empty() || value.empty())
      throw std::runtime_error("error reading config file");
    if (configs.count(key))
      throw std::runtime_error("duplicated config");
    configs.insert(std::make_pair(key, value));
  }
}

const std::string & ConfigFile::getValue(const std::string &key) {
  return configs.at(key);
}


