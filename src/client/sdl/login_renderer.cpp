#include "login_renderer.h"

LoginRenderer::LoginRenderer(LoginStateHandler& login_state_handler_, Window& window)
                :Scene(window.renderer().getMinDimension()), login_state_handler(login_state_handler_) {
}

void LoginRenderer::render() {
    login_state_handler.tellRendererWhatToRender(*this);
}

void LoginRenderer::renderIPAndPortFields(std::list<Button>& buttons) {
    // button.setArea(x, y, width, height)
    //button.render()
    //ip draw here (x, y) with this scale
    //port draw here (x, y) with this scale
    //name draw here (x, y) with this scale
    //connect draw here (x, y) with this scale
}


void LoginRenderer::setScale(int scale_) {
    scale = scale_;
}

