#include "client_data.h"
#include <string>

ClientData::ClientData(uint16_t id_, const std::string &name_, Role role_) :
    id(id_), name(name_), role(role_) {}
