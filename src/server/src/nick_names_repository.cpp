#include "nick_names_repository.h"


NickNamesRepository::NickNamesRepository()
                    :nick_names(BASE_CLIENTS){
}


NickNamesRepository::NickNamesRepository(NickNamesRepository&& other_repository)
                    :nick_names(std::move(other_repository.nick_names)) {

}
void NickNamesRepository::saveNickNameRelatedToId(std::string&& clients_nick_name, const int& client_id) {
    if (this->nick_names.size() < (size_t)client_id)
        this->nick_names.resize(this->nick_names.size() + BASE_CLIENTS);
    this->nick_names[client_id] = clients_nick_name;
}

void NickNamesRepository::getNickNameRelatedToId(std::string& clients_nick_name, const int& client_id) const {
    clients_nick_name = this->nick_names[client_id];
}

