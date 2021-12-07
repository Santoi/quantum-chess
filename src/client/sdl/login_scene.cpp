#include "login_scene.h"
#include "../login/login_state_handler.h"

LoginScene::LoginScene(Window &window,
                       LoginStateHandler &login_state_handler)
    :
    Scene(window),
    login_state_handler(login_state_handler),
    background(window.renderer(), "img/login-background.jpg", window.getWidth(),
               window.getHeight()) {}

void LoginScene::render() {
  background.render(0, 0, window.getWidth(), window.getHeight());
  login_state_handler.render(*this);
}

void LoginScene::setConnectionButtonsDimensions(Button &connect_button,
                                                TextEntryButton &ip_text_entry,
                                                TextEntryButton &port_text_entry,
                                                TextEntryButton &name_text_entry) {
  int width = window.getWidth();
  int height = window.getHeight();
  int button_height = height / 15;
  int ip_button_width = width / 3, port_button_width = width / 10,
      nick_button_width = width / 3, connect_button_width = width / 4;
  int ip_button_x_pos = (width - ip_button_width) / 2 - port_button_width * 1.1;
  int port_button_x_pos = width / 2 + port_button_width * 1.1;

  ip_text_entry.setAreaAndPosition(ip_button_x_pos,
                                   button_height,
                                   ip_button_width, button_height);
  port_text_entry.setAreaAndPosition(port_button_x_pos,
                                     button_height,
                                     port_button_width, button_height);
  name_text_entry.setAreaAndPosition(width / 2 - nick_button_width / 2,
                                     button_height * 3,
                                     nick_button_width,
                                     button_height);
  connect_button.setAreaAndPosition(width / 2 - connect_button_width / 2,
                                    button_height * 5,
                                    connect_button_width,
                                    button_height);
}

void LoginScene::renderIPAndPortFields(Button &connect_button,
                                       TextEntryButton &ip_text_entry,
                                       TextEntryButton &port_text_entry,
                                       TextEntryButton &name_text_entry) {
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
                               0.1 * width, 0.1 * height);
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
    white_role_button.setAreaAndPosition(100, 100, 0.2 * height, 0.2 * width);
    white_role_button.render();
    black_role_button.setAreaAndPosition(250, 100, 0.2 * height, 0.2 * width);
    black_role_button.render();
    spectator_role_button.setAreaAndPosition(400, 100, 0.2 * height, 0.2 * width);
    spectator_role_button.render();
}
