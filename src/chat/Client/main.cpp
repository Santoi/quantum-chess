#include "client.h"
#include <iostream>
#define SUCCESS 0

int main(int argc, char* argv[]) {
    try {
        Client client(argv[1], argv[2]);
        client.execute();
    } catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return SUCCESS;
}