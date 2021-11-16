#include "nick_names_repository.h"


NickNamesRepository::NickNamesRepository()
                    :nick_names(){
}


NickNamesRepository::NickNamesRepository(NickNamesRepository&& other_repository)
                    :nick_names(std::move(other_repository.nick_names)) {

}
void NickNamesRepository::saveNickNameRelatedToId(std::string&& clients_nick_name, const int& client_id) {
    nick_names.insert(std::make_pair(client_id, std::move(clients_nick_name)));
}

void NickNamesRepository::getNickNameRelatedToId(std::string& clients_nick_name, const int& client_id) const {
    if (nick_names.count(client_id))
        clients_nick_name = this->nick_names.at(client_id);
}

