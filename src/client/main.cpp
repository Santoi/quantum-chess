#include "client.h"
#include <iostream>

int main(void) {
  try {
    Client client;
    client.execute();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
