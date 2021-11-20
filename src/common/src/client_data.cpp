#include "client_data.h"

ClientData::ClientData(uint16_t id_, const std::string &name_, bool player_,
                       bool white_): id(id_), name(name_), player(player_),
                       white(white_) {}

uint16_t ClientData::getId() const {
    return id;
}

const std::string &ClientData::getName() const {
    return name;
}

bool ClientData::isWhite() const {
    return white;
}

bool ClientData::isPlayer() const {
    return player;
}
