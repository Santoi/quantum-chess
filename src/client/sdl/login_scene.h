#ifndef QUANTUM_CHESS_PROJ_LOGIN_SCENE_H
#define QUANTUM_CHESS_PROJ_LOGIN_SCENE_H

#include "window.h"
#include "../login/login_state.h"
#include "../logic/button.h"
#include "drawables/drawable_container.h"
#include "../logic/text_entry_button.h"
#include "scene.h"
#include "../login/login_state_handler.h"
#include <vector>

class LoginStateHandler;

class TextureSprite;

class LoginScene : public Scene {
private:
  LoginStateHandler &login_state_handler;
  TextureSprite background;

  void setConnectionButtonsDimensions(Button &connect_button,
                                      TextEntryButton &ip_text_entry,
                                      TextEntryButton &port_text_entry,
                                      TextEntryButton &name_text_entry);

  // Return an iterator pointing to the first button to render
  __gnu_cxx::__normal_iterator<std::unique_ptr<Button> *,
      std::vector<std::unique_ptr<Button>>>
  findFirstButtonToRender(std::vector<std::unique_ptr<Button>> &match_buttons,
                          size_t match_to_render);

public:
  LoginScene() = delete;

  LoginScene(Window &window, LoginStateHandler &login_state_handler);

  // Render the current login state scene
  void render();

  void renderChoosingMatchButtons(
      std::vector<std::unique_ptr<Button>> &match_buttons,
      NextMatchesButton &next_matches_button,
      PreviousMatchesButton &previous_matches_button,
      RefreshMatchesButton &refresh_matches_button, size_t matches_page,
      size_t matches_per_page);

  void renderConnectionToServerButtons(Button &connect_button,
                                       TextEntryButton &ip_text_entry,
                                       TextEntryButton &port_text_entry,
                                       TextEntryButton &name_text_entry);

  void renderRolesButtons(Button &white_role_button, Button &black_role_button,
                          Button &spectator_role_button);
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_SCENE_H
