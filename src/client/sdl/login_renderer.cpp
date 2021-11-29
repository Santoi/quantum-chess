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

void LoginRenderer::renderIPAndPortFields(ConnectButton& connect_button,
                                          TextEntryButton& ip_text_entry,
                                          TextEntryButton& port_text_entry) {
   connect_button.setAreaAndPosition(50, 50, 50, 20);
   connect_button.render();
  //...
}

void LoginRenderer::setScale(int scale_) {
  scale = scale_;
}

