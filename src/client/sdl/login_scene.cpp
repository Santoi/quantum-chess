#include "login_scene.h"
#include "../login/login_state_handler.h"

LoginScene::LoginScene(LoginStateHandler &login_state_handler, Window &window)
    :
    Scene(window),
    login_state_handler(login_state_handler) {}

void LoginScene::render() {
  login_state_handler.render(*this);
}

void LoginScene::setConnectionButtonsDimensions(Button &connect_button,
                                                TextEntryButton &ip_text_entry,
                                                TextEntryButton &port_text_entry,
                                                TextEntryButton &name_text_entry) {
  int width = window.getWidth();
  int height = window.getHeight();
  int button_height = width / 20;
  int ip_button_width = width / 3, port_button_width = width / 10;
  int ip_button_x_pos = (width - ip_button_width) / 2 - port_button_width * 1.1;
  int port_button_x_pos = width / 2 + port_button_width * 1.1;
  int connect_button_width = width / 4;
  ip_text_entry.setAreaAndPosition(ip_button_x_pos, height / 10,
                                   ip_button_width, button_height);
  port_text_entry.setAreaAndPosition(port_button_x_pos, height / 10,
                                     port_button_width, button_height);
  connect_button.setAreaAndPosition(width / 2 - connect_button_width / 2,
                                    height / 5,
                                    connect_button_width,
                                    button_height);
  name_text_entry.setAreaAndPosition(200, 300, 100, 50);
}

void LoginScene::renderIPAndPortFields(Button &connect_button,
                                       TextEntryButton &ip_text_entry,
                                       TextEntryButton &port_text_entry, TextEntryButton &name_text_entry) {
  setConnectionButtonsDimensions(connect_button, ip_text_entry,
                                 port_text_entry, name_text_entry);
  ip_text_entry.render();
  port_text_entry.render();
  name_text_entry.render();
  connect_button.render();
}

void LoginScene::renderMatchButtons(
    std::vector<std::unique_ptr<Button>> &match_buttons) {
  int width = window.getWidth();
  int height = window.getHeight();
  int i = 0;
  for (auto &button: match_buttons) {
    button->setAreaAndPosition(10, ++i * 200,
                               0.1 * height, 0.1 * width);
    button->render();
  }
}

void LoginScene::renderConnectedSprite(TextureSprite &texture) {
  int width = window.getWidth();
  int height = window.getHeight();
  texture.render(10, 10, width * 0.9, height * 0.9);
}

void LoginScene::renderRolesButtons(Button &white_role_button,
                                    Button &black_role_button,
                                    Button &spectator_role_button) {
    int width = window.getWidth();
    int height = window.getHeight();
    white_role_button.setAreaAndPosition(100, 100, 0.2 * width, 0.2 * height);
    white_role_button.render();
    black_role_button.setAreaAndPosition(350, 100, 0.2 * width, 0.2 * height);
    black_role_button.render();
    spectator_role_button.setAreaAndPosition(600, 100, 0.2 * width, 0.2 * height);
    spectator_role_button.render();
}
