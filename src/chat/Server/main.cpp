#include <iostream>
#include "server.h"

#define SUCCESS 0

int main(int argc, char* argv[]) {
    bool one_thread_only = false;
    if (argc == 2)
        one_thread_only = true;
    try {
        Server server(nullptr, argv[2]);
        server.execute(one_thread_only);
    }
    catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return SUCCESS;
}