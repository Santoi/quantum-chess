#include "login_renderer.h"

LoginRenderer::LoginRenderer(Window& window)
                :Scene(window.renderer().getMinDimension()) {
}

void LoginRenderer::render() {

}

void LoginRenderer::setScale(int scale_) {
    scale = scale_;
}

