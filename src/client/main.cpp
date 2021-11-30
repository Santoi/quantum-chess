#include "client.h"
#include <iostream>

#define SUCCESS 0

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Not enough arugments";
    return 1;
  }
  try {
    Client client;
    client.execute(argv[1], argv[2]);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return SUCCESS;
}