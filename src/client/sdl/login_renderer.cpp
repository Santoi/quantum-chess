#include "login_renderer.h"

LoginRenderer::LoginRenderer(LoginStateHandler& login_state_handler_,
                             Window& window)
    : scale(window.renderer().getMinDimension()),
      login_state_handler(login_state_handler_) {
}

void LoginRenderer::setScale(const int& scale_) {
    scale = scale_;
}


void LoginRenderer::render() {
  login_state_handler.tellRendererWhatToRender(*this);
}

void LoginRenderer::renderSettingsPage(Button &connect_button,
                        TextEntryButton &ip_text_entry,
                        TextEntryButton &port_text_entry, TextEntryButton &name_text_entry) {
   connect_button.setAreaAndPosition(200, 300, scale*0.135, scale*0.310);
   connect_button.render();
   ip_text_entry.setAreaAndPosition(10, 10, scale*0.1, scale*0.8);
   ip_text_entry.render();
   port_text_entry.setAreaAndPosition(10, 100, scale*0.1, scale*0.3);
   port_text_entry.render();
   name_text_entry.setAreaAndPosition(300, 100, scale*0.1, scale*0.5);
   name_text_entry.render();
}

void LoginRenderer::renderMatchButtons(std::vector<std::unique_ptr<Button>>& match_buttons) {
    for (int i = 0; i < (int)match_buttons.size(); i++) {
        match_buttons[i]->setAreaAndPosition(i * 20 + 10, 200, 0.1 * scale, 0.1 * scale);
        match_buttons[i]->render();
    }
}

void LoginRenderer::renderRolesButtons(Button& white_role_buton, Button& black_role_buton, Button& spectator_role_buton) {
    white_role_buton.setAreaAndPosition(100, 100, 0.3*scale, 0.3*scale);
    white_role_buton.render();
    black_role_buton.setAreaAndPosition(250, 100, 0.3*scale, 0.3*scale);
    black_role_buton.render();
    spectator_role_buton.setAreaAndPosition(400, 100, 0.3*scale, 0.3*scale);
    spectator_role_buton.render();
}


void LoginRenderer::renderConnectedSprite(TextureSprite& texture) {
    texture.render(10, 10, scale*0.9, scale*0.9);
}

