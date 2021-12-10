#include "login_scene.h"
#include "../login/login_state_handler.h"
#include <vector>

#define MAX_MATCH_BUTTON_COUNT 8

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

void LoginScene::renderConnectionToServerButtons(Button &connect_button,
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

std::reverse_iterator<__gnu_cxx::__normal_iterator<std::unique_ptr<Button> *, std::vector<std::unique_ptr<Button>>>>
LoginScene::findFirstButtonToRender(
    std::vector<std::unique_ptr<Button>> &match_buttons,
    size_t match_to_render) {
  auto it = match_buttons.rbegin();
  size_t matches = 0;
  while (matches < match_to_render &&
         it != match_buttons.rend()) {
    ++it;
    matches++;
  }
  return it;
}

void LoginScene::renderChoosingMatchButtons(
    std::vector<std::unique_ptr<Button>> &match_buttons,
    NextMatchesButton &next_matches_button,
    PreviousMatchesButton &previous_matches_button,
    RefreshMatchesButton &refresh_matches_button, size_t matches_page,
    size_t matches_per_page) {
  size_t width = window.getWidth();
  size_t height = window.getHeight();
  size_t match_button_width = width * .9, button_height = height / 20;
  size_t other_button_width = width * .15;

  auto it = findFirstButtonToRender(match_buttons,
                                    matches_page * matches_per_page);
  size_t i = 1;
  for (; it != match_buttons.rend(); ++it) {
    (*it)->setAreaAndPosition(width / 2 - match_button_width / 2,
                              height * i * .1,
                              match_button_width, button_height);
    (*it)->render();
    if (i++ == matches_per_page) {
      break;
    }
  }
  next_matches_button.setAreaAndPosition(width - other_button_width * 2.5,
                                         height * i * .1, other_button_width,
                                         button_height);
  previous_matches_button.setAreaAndPosition(other_button_width * 1.5,
                                             height * i * .1,
                                             other_button_width,
                                             button_height);
  refresh_matches_button.setAreaAndPosition(width / 2 - other_button_width / 2,
                                            height * i * .1,
                                            other_button_width,
                                            button_height);
  next_matches_button.render();
  previous_matches_button.render();
  refresh_matches_button.render();
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
