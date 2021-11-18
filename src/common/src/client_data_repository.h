#ifndef QUANTUM_CHESS_PROJ_CLIENT_DATA_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_CLIENT_DATA_REPOSITORY_H

#include <vector>
#include <string>
#include <map>
#include "client_data.h"

class ClientDataRepository {
private:
    std::map<uint16_t, ClientData> data;

public:
    //Creates a ClientDataRepository with string vector of size BASE_CLIENTS.
    ClientDataRepository();

    //Moves the string vector from other_repository to new repository.
    ClientDataRepository(ClientDataRepository&& other_repository) noexcept ;

    //Saves, based on the client_id, the clients_nick_name string. It expands the string vector
    //capacity if necessary.
    void saveClientData(ClientData && client_data, uint16_t client_id);

    const ClientData &getClientData(uint16_t client_id) const;

    ~ClientDataRepository() = default;

    std::vector<const ClientData *> getAllData() const;
};


#endif //QUANTUM_CHESS_PROJ_CLIENT_DATA_REPOSITORY_H
