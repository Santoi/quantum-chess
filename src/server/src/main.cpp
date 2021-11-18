#include <iostream>
#include "server.h"

#define SUCCESS 0

int main(int argc, char* argv[]) {
    bool one_thread_only = false;
    int type_of_single_thread = 0;
    if (argc == 3){
        one_thread_only = true;
        type_of_single_thread = atoi(argv[2]);
    }
    try {
        Server server(nullptr, argv[1]);
        server.execute(one_thread_only, type_of_single_thread);
    }
    catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return SUCCESS;
}