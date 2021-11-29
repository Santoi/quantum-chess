#include "login_renderer.h"

LoginRenderer::LoginRenderer(LoginStateHandler &login_state_handler_,
                             Window &window)
    : scale(window.renderer().getMinDimension()),
      login_state_handler(login_state_handler_) {
}

void LoginRenderer::render() {
  login_state_handler.tellRendererWhatToRender(*this);
}

void LoginRenderer::renderIPAndPortFields(ConnectButton &connect_button,
                                          TextEntryButton &ip_text_entry,
                                          TextEntryButton &port_text_entry) {
  // connect_button.setArea(x, y, width, height)
  //connect_button.render()
  //...
}


void LoginRenderer::setScale(int scale_) {
  scale = scale_;
}

