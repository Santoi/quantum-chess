#include "login_renderer.h"

LoginRenderer::LoginRenderer(const LoginState& login_state_, Window& window)
                :Scene(window.renderer().getMinDimension()), login_state(login_state_) {
}

void LoginRenderer::render() {

}

void LoginRenderer::setScale(int scale_) {
    scale = scale_;
}

