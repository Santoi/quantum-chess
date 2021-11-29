#ifndef QUANTUM_CHESS_PROJ_TEXTURE_SPRITE_H
#define QUANTUM_CHESS_PROJ_TEXTURE_SPRITE_H

#include "sprite.h"
#include "renderer.h"
#include <SDL2pp/SDL2pp.hh>
#include <string>

#define DEFAULT_SPRITE "img/default.png"

class Renderer;

class TextureSprite : public Sprite {
public:
  explicit TextureSprite(Renderer &renderer,
                         const std::string &file_name = DEFAULT_SPRITE,
                         int width = 0, int height = 0);

  TextureSprite(TextureSprite &&other) = default;

  TextureSprite &operator=(TextureSprite &&other) noexcept;

  // Render the current sprite from (x, y) to (x + width, y + height)
  void render(int x_src, int y_src, int x, int y,
              int width_src, int height_src, int width, int height);

  void render(int x, int y, int width, int height);

  void render(int x, int y);

  void setBlendMode(int blendMode);

  void setAlpha(float alpha);

  float getAlpha() const;

  int getImageWidth() const;

  int getImageHeight() const;

  void loadImage(const std::string &file_name, int width = 0, int height = 0);

  ~TextureSprite();
};


#endif //QUANTUM_CHESS_PROJ_TEXTURE_SPRITE_H