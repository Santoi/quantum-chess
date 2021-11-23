#ifndef QUANTUM_CHESS_PROJ_CLIENT_DATA_H
#define QUANTUM_CHESS_PROJ_CLIENT_DATA_H

#include <cstdint>
#include <string>

typedef struct ClientData {
public:
  typedef enum {
    ROLE_WHITE,
    ROLE_BLACK,
    ROLE_SPECTATOR
  } Role;

  const uint16_t id;
  const std::string name;
  const Role role;

  ClientData(uint16_t id_, const std::string &name_, Role role_);
} ClientData;


#endif //QUANTUM_CHESS_PROJ_CLIENT_DATA_H
