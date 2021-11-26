#include <iostream>
#include "server.h"

#define SUCCESS 0

int main(int argc, char *argv[]) {
  try {
    Server server(nullptr, argv[1]);
    server.execute();
  }
  catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return SUCCESS;
}