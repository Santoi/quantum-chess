#ifndef QUANTUM_CHESS_PROJ_LOGIN_SCENE_H
#define QUANTUM_CHESS_PROJ_LOGIN_SCENE_H

#include "window.h"
#include "../login/login_state.h"
#include "button.h"
#include "chat/drawable_container.h"
#include "text_entry_button.h"
#include "scene.h"
#include "../login/login_state_handler.h"

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

  // Return a reverse iterator pointing to the first button to render
  std::reverse_iterator<__gnu_cxx::__normal_iterator<std::unique_ptr<Button> *, std::vector<std::unique_ptr<Button>>>>
  findFirstButtonToRender(std::vector<std::unique_ptr<Button>> &match_buttons,
                          int match_to_render);

public:

  LoginScene() = delete;

  LoginScene(Window &window,
             LoginStateHandler &login_state_handler);

  void render();

  void renderChoosingMatchButtons(
      std::vector<std::unique_ptr<Button>> &match_buttons,
      NextMatchesButton &next_matches_button,
      PreviousMatchesButton &previous_matches_button, int matches_page,
      int matches_per_page);

  void renderConnectedSprite(TextureSprite &texture);

  void renderConnectionToServerButtons(Button &connect_button,
                                       TextEntryButton &ip_text_entry,
                                       TextEntryButton &port_text_entry,
                                       TextEntryButton &name_text_entry);

  void renderRolesButtons(Button &white_role_button, Button &black_role_button,
                          Button &spectator_role_button);

};


#endif //QUANTUM_CHESS_PROJ_LOGIN_SCENE_H
