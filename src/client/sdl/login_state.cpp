#include "login_state.h"
#include "../../common/src/unique_ptr.h"
#include "../../common/src/client_data.h"
#include <iostream>

LoginState::LoginState(Login& login_)
            :login(login_) {
}

void LoginState::resetPressedButtons() {
    for (auto it = buttons_ptr.begin(); it != buttons_ptr.end(); it++)
        (*it)->resetButton();
}


NotConnectedToServerState::NotConnectedToServerState(Login& login_, Renderer& renderer_)
                            :LoginState(login_) {
    text_entry_buttons_ptr.reserve(3);
    std::unique_ptr<TextEntryButton> ip_ptr = make_unique<TextEntryButton>(renderer_, "img/buttons/ip_text.png");
    text_entry_buttons_ptr.push_back(std::move(ip_ptr));
    std::unique_ptr<TextEntryButton> port_ptr = make_unique<TextEntryButton>(renderer_, "img/buttons/port_text.png");
    text_entry_buttons_ptr.push_back(std::move(port_ptr));
    std::unique_ptr<TextEntryButton> nick_name_ptr = make_unique<TextEntryButton>(renderer_, "img/buttons/nick_name_text.png");
    text_entry_buttons_ptr.push_back(std::move(nick_name_ptr));
    buttons_ptr.reserve(1);
    std::unique_ptr<Button> button_ptr = make_unique<ConnectButton>(renderer_, text_entry_buttons_ptr);
    buttons_ptr.push_back(std::move(button_ptr));
}

bool NotConnectedToServerState::clientIsConnectedToMatch() {
    return false;
}

void NotConnectedToServerState::tellRendererWhatToRender(LoginRenderer& login_renderer) {
    login_renderer.renderSettingsPage(*buttons_ptr[0], *text_entry_buttons_ptr[0],
                                         *text_entry_buttons_ptr[1], *text_entry_buttons_ptr[2]);
}

void NotConnectedToServerState::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {
    for (auto it = buttons_ptr.begin(); it != buttons_ptr.end(); it++)
        active_buttons.push_back(**it);
}

void NotConnectedToServerState::fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                                active_text_entries) {
    for (auto it = text_entry_buttons_ptr.begin(); it != text_entry_buttons_ptr.end(); it++)
        active_text_entries.push_back(**it);
}

int NotConnectedToServerState::proccessTokens(std::list<std::string>&& tokens) {
    std::string ip = tokens.front(); //tokens strings has the same order as how TextEntryButton are in the list
                                    //(first the ip string, second the port string, third the nick name)
    tokens.pop_front();
    std::cout << ip << std::endl;
    std::string port = tokens.front();
    tokens.pop_front();
    std::cout << port << std::endl;
    login.connectToServer(ip, port);
    std::string nick_name = tokens.front();
    tokens.pop_front();
    std::cout << nick_name << std::endl;
    login.saveNickName(nick_name);
    return 1;
}

NotConnectedToMatchState::NotConnectedToMatchState(Login& login_, Renderer& renderer_)
                        :LoginState(login_) {
    login.getListOfMatchButtons(renderer_, buttons_ptr);
}

bool NotConnectedToMatchState::clientIsConnectedToMatch() {
    return false;
}

void NotConnectedToMatchState::tellRendererWhatToRender(LoginRenderer& login_renderer) {
    login_renderer.renderMatchButtons(buttons_ptr);
}

void NotConnectedToMatchState::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {
    for (auto it = buttons_ptr.begin(); it != buttons_ptr.end(); it++)
        active_buttons.push_back(**it);
}

void NotConnectedToMatchState::fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                                        active_text_entries) {
    //dont have text_entries
}

int NotConnectedToMatchState::proccessTokens(std::list<std::string>&& tokens) {
    std::string str_match_number = tokens.front();
    int match_number = std::stoi(str_match_number);
    login.chooseMatchNumber(match_number);
    login.sendSavedNickNameToServer();
    return 2;
}

void SelectingRoleState::addActiveOrInactiveRoleButtonWithImages(ClientData::Role role_, Renderer& renderer_,
                                                            std::list<ClientData::Role>& available_roles,
                                                            const std::string& available_not_pressed_image,
                                                            const std::string& available_pressed_image,
                                                            const std::string& not_available_not_pressed_image,
                                                            const std::string& not_available_pressed_image) {
    std::unique_ptr<RoleButton> role_button_ptr;
    std::list<ClientData::Role>::iterator findIter = std::find(available_roles.begin(),
                                                           available_roles.end(), role_);
    if (findIter != available_roles.end())
        role_button_ptr = make_unique<RoleButton>(renderer_, role_, true, available_not_pressed_image,
                                                  available_pressed_image);
    else
        role_button_ptr = make_unique<RoleButton>(renderer_, role_, false, not_available_not_pressed_image,
                                                  not_available_pressed_image);
    buttons_ptr.push_back(std::move(role_button_ptr));
}

SelectingRoleState::SelectingRoleState(Login& login_, Renderer& renderer_)
                    :LoginState(login_) {
    std::list<ClientData::Role> available_roles = login.getAvailableRoles();
    addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_WHITE, renderer_, available_roles,
                                            "img/buttons/available_white_role.png",
                                            "img/buttons/available_white_role.png",
                                            "img/buttons/not_available_white_role.png",
                                            "img/buttons/not_available_white_role.png");
    addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_BLACK, renderer_, available_roles,
                                            "img/buttons/available_black_role.png",
                                            "img/buttons/available_black_role.png",
                                            "img/buttons/not_available_black_role.png",
                                            "img/buttons/not_available_black_role.png");
    addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_SPECTATOR, renderer_, available_roles,
                                            "img/buttons/spectator_role.png", "img/buttons/spectator_role.png",
                                            "img/buttons/spectator_role.png", "img/buttons/spectator_role.png");
}

bool SelectingRoleState::clientIsConnectedToMatch() {
    return false;
}

void SelectingRoleState::tellRendererWhatToRender(LoginRenderer& login_renderer) {
  //  login_renderer.renderRolesButtons(buttons_ptr);
}

void SelectingRoleState::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {
    for (auto it = buttons_ptr.begin(); it != buttons_ptr.end(); it++)
        active_buttons.push_back(**it);
}

void SelectingRoleState::fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                        active_text_entries) {
    //dont have any
}

ClientData::Role getRoleFromString(const std::string& str_selected_role) {
    if (str_selected_role == "ROLE_WHITE")
        return ClientData::ROLE_WHITE;
    else if (str_selected_role == "ROLE_BLACK")
        return ClientData::ROLE_BLACK;
    else
        return ClientData::ROLE_SPECTATOR;
}

int SelectingRoleState::proccessTokens(std::list<std::string>&& tokens) {
    if (tokens.empty())
        return -1;
    std::string str_selected_role = tokens.front();
    ClientData::Role selected_role = getRoleFromString(str_selected_role);
    login.sendChosenRole(selected_role);
    return 3;
}

ConnectedToMatchState::ConnectedToMatchState(Login& login_, Renderer& renderer_)
                        :LoginState(login_),
                         texture_sprite(renderer_, "img/buttons/connected_sprite.png") {
}

bool ConnectedToMatchState::clientIsConnectedToMatch() {
    return true;
}

void ConnectedToMatchState::tellRendererWhatToRender(LoginRenderer& login_renderer) {
    login_renderer.renderConnectedSprite(texture_sprite);
}

void ConnectedToMatchState::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {

}

void ConnectedToMatchState::fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                            active_text_entries) {
}

int ConnectedToMatchState::proccessTokens(std::list<std::string>&& tokens) {
    return 4;
}
