#ifndef QUANTUM_CHESS_PROJ_NICK_NAMES_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_NICK_NAMES_REPOSITORY_H

#include <vector>
#include <string>
#include <map>

class NickNamesRepository {
private:
    std::map<int, std::string> nick_names;

public:
    //Creates a NickNamesRepository with string vector of size BASE_CLIENTS.
    NickNamesRepository();

    //Moves the string vector from other_repository to new repository.
    NickNamesRepository(NickNamesRepository&& other_repository);

    //Saves, based on the client_id, the clients_nick_name string. It expands the string vector
    //capacity if necessary.
    void saveNickNameRelatedToId(std::string&& clients_nick_name, const int& client_id);

    //Fills the clients_nick_name string with the nick name associated with the client_id
    //passed to the function.
    void getNickNameRelatedToId(std::string& clients_nick_name, const int& client_id) const;

    ~NickNamesRepository() = default;
};


#endif //QUANTUM_CHESS_PROJ_NICK_NAMES_REPOSITORY_H
