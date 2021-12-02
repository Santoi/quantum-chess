#include "login.h"
#include "../communication/client_protocol.h"
#include "../../common/src/unique_ptr.h"
#include <iostream>

Login::Login()
        :client_socket_ptr(nullptr) {
}

void Login::connectToServer(const std::string& ip_, const std::string& port_) {
    const char* ip = ip_.c_str();
    const char* port = port_.c_str();
    Socket::createAConnectedSocket(client_socket_ptr, ip, port);
}

void Login::getListOfMatchButtons(Renderer& renderer_, std::vector<std::unique_ptr<Button>>& buttons_ptr) {
    ClientProtocol protocol;
    std::map<uint16_t, std::vector<ClientData>> data = std::move(
            protocol.receiveMatchesInfo(*client_socket_ptr));
    buttons_ptr.reserve(data.size() + 1);
    int i = 0;
    for (auto it = data.begin(); it != data.end(); it++) {
        std::unique_ptr<Button> button = make_unique<PickMatchButton>(renderer_, i);
        buttons_ptr.push_back(std::move(button));
        i++;
    }
    std::unique_ptr<Button> button = make_unique<PickMatchButton>(renderer_, i);
    buttons_ptr.push_back(std::move(button));
    //std::cout << "Selecciona de las partidas disponibles a cuál de estas"
    //             " quieres entrar." << std::endl;
    /*std::cout << "Las partidas disponibles son" << std::endl;
    uint16_t last_id = 0;
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << "#" << it->first << ": ";
        std::vector<ClientData> &client_data = it->second;
        for (auto it_match = client_data.begin();
             it_match != client_data.end(); ++it_match) {
            char other_cliente_role = ' ';
            switch (it_match->role) {
                case ClientData::ROLE_WHITE:
                    other_cliente_role = 'w';
                    break;
                case ClientData::ROLE_BLACK:
                    other_cliente_role = 'b';
                    break;
                case ClientData::ROLE_SPECTATOR:
                    other_cliente_role = 'o';
                    break;
            }
            std::cout << it_match->name << "#" << it_match->id << "("
                      << other_cliente_role << "), ";
        }
        std::cout << std::endl;
        last_id = it->first;
        std::cout << last_id << std::endl;
    }
    std::cout << "Todavía no estamos conectado al match!" << std::endl;*/
}

void Login::saveNickName(const std::string& nick_name) {
    client_nick_name = nick_name;
}

Socket Login::getClientSocket() {
    return std::move(*client_socket_ptr);
}

std::string Login::getClientNickName() {
    return client_nick_name;
}

std::list<ClientData::Role> Login::getAvailableRoles() {
    std::list<ClientData::Role> available_roles;
    ClientProtocol protocol;
    protocol.getAvailableRoles(*client_socket_ptr, available_roles);
    return available_roles;
}


void Login::sendSavedNickNameToServer() {
    ClientProtocol protocol;
    protocol.sendClientsNickName(*client_socket_ptr, client_nick_name);
    std::list<ClientData::Role> available_roles = getAvailableRoles();
    //ClientData::Role role = *available_roles.begin();
    protocol.sendChosenRole(*client_socket_ptr, *available_roles.begin());
}

void Login::chooseMatchNumber(int match_number) {
    ClientProtocol protocol;
    std::cout << "Me conecto a la partida " << match_number << std::endl;
    protocol.sendChosenGame(*client_socket_ptr, match_number);
}
