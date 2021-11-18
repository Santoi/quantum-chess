#include "client_data_repository.h"


ClientDataRepository::ClientDataRepository()
                    : data(){
}


ClientDataRepository::ClientDataRepository(ClientDataRepository&& other_repository) noexcept
                    : data(std::move(other_repository.data)) {

}
void ClientDataRepository::saveClientData(ClientData && client_data, uint16_t client_id) {
    data.insert(std::make_pair(client_id, std::move(client_data)));
}

std::vector<const ClientData *> ClientDataRepository::getAllData() const {
    std::vector<const ClientData *> output;
    for (auto & client: data)
        output.push_back(&client.second);
    return output;
}

const ClientData & ClientDataRepository::getClientData(uint16_t client_id) const {
    if (data.count(client_id))
        return this->data.at(client_id);
    throw std::runtime_error("that id doesnt exist");
}

