#include <iostream>
#include "server.h"

#define SUCCESS 0

int main(int argc, char *argv[]) {
  try {
    if (argc < 2)
      throw std::invalid_argument("must indicate port");
    std::string board_filename;
    if (argc < 3)
      board_filename = "default.txt";
    else
      board_filename = argv[2];
    Server server(nullptr, argv[1]);
    server.execute(board_filename);
  }
  catch(const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  catch(...) {
    std::cerr << "Error desconocido" << std::endl;
  }

  return SUCCESS;
}
