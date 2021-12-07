#include "client.h"
#include <iostream>

int main(int argc, char *argv[]) {
  try {
    Client client;
    client.execute();
  } catch(const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
