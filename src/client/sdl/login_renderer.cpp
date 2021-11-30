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

void LoginRenderer::renderIPAndPortFields(Button& connect_button,
                                          TextEntryButton& ip_text_entry,
                                          TextEntryButton& port_text_entry) {
   connect_button.setAreaAndPosition(200, 300, scale*0.1, scale*0.3);
   connect_button.render();
   ip_text_entry.setAreaAndPosition(10, 10, scale*0.1, scale*0.8);
   ip_text_entry.render();
   port_text_entry.setAreaAndPosition(10, 100, scale*0.1, scale*0.3);
   port_text_entry.render();
}
