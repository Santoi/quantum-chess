#include "login_scene.h"
#include "../login/login_state_handler.h"

LoginScene::LoginScene(LoginStateHandler &login_state_handler, Window &window)
    :
    Scene(window),
    login_state_handler(login_state_handler) {}

void LoginScene::render() {
  login_state_handler.render(*this);
}

void LoginScene::renderIPAndPortFields(Button &connect_button,
                                       TextEntryButton &ip_text_entry,
                                       TextEntryButton &port_text_entry) {
  // LoginScene::setButtonDimensions()
  int width = window.getWidth();
  int height = window.getHeight();
  int button_height = width / 20;
  int ip_button_width = width / 4, port_button_width = width / 10;
  int ip_button_x_pos =
      width / 2 - ip_button_width / 2 - port_button_width * 1.1;
  int port_button_x_pos =
      width / 2 + ip_button_width / 2 + port_button_width * 1.1;
  int connect_button_width = width / 6;
  ip_text_entry.setAreaAndPosition(ip_button_x_pos, height / 10,
                                   ip_button_width, button_height);
  port_text_entry.setAreaAndPosition(port_button_x_pos, height / 10,
                                     port_button_width, button_height);
  connect_button.setAreaAndPosition(connect_button_width, height / 5,
                                    button_height,
                                    ip_button_width);
  // end setButtonDimensions()

  ip_text_entry.render();
  port_text_entry.render();
  connect_button.render();
}

void LoginScene::renderMatchButtons(
    std::list<std::unique_ptr<Button>> &match_buttons) {
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
