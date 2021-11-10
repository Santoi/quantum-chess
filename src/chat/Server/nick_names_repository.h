#ifndef QUANTUM_CHESS_PROJ_NICK_NAMES_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_NICK_NAMES_REPOSITORY_H

#include <vector>
#include <string>


class NickNamesRepository {
private:
    std::vector<std::string> nick_names;

public:
    NickNamesRepository();
    NickNamesRepository(NickNamesRepository&& other_repository);
    void saveNickNameRelatedToId(std::string&& clients_nick_name, const int& client_id);
    void getNickNameRelatedToId(std::string& clients_nick_name, const int& client_id) const;
    ~NickNamesRepository() = default;
};


#endif //QUANTUM_CHESS_PROJ_NICK_NAMES_REPOSITORY_H
