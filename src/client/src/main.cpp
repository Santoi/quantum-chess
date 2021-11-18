#include "client.h"
#include <iostream>
#define SUCCESS 0

int main(int argc, char* argv[]) {
   bool single_threaded_client = false;
    if (argc == 4)
       single_threaded_client = true;
    try {
        Client client;
        client.execute(argv[1], argv[2], single_threaded_client);
    } catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return SUCCESS;
}