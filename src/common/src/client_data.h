#ifndef QUANTUM_CHESS_PROJ_CLIENT_DATA_H
#define QUANTUM_CHESS_PROJ_CLIENT_DATA_H


#include <cstdint>
#include <string>

class ClientData {
    uint16_t id;
    std::string name;
    bool player;
    bool white;

public:
    ClientData(uint16_t id_, const std::string & name_, bool player_, bool white_);

    uint16_t getId() const;
    const std::string & getName() const;
    bool isPlayer() const;
    bool isWhite() const;
};


#endif //QUANTUM_CHESS_PROJ_CLIENT_DATA_H
