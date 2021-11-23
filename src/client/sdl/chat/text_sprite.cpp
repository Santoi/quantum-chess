#include "text_sprite.h"
#include "../sdl/renderer.h"

TextSprite::TextSprite(Renderer &renderer, Font &font): renderer(renderer),
                                                        text(font) {}
