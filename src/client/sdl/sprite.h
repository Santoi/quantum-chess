#ifndef QUANTUM_CHESS_PROJ_SPRITE_H
#define QUANTUM_CHESS_PROJ_SPRITE_H

#include "renderer.h"
#include <SDL2pp/SDL2pp.hh>
#include <string>

#define DEFAULT_SPRITE "img/default.png"

class Renderer;

class Sprite {
private:
  Renderer &renderer;
  SDL2pp::Texture sprite_;
  int width_, height_;

public:
  explicit Sprite(Renderer &renderer,
                  const std::string &file_name = DEFAULT_SPRITE,
                  int width = 0, int height = 0);

  Sprite(Sprite &&other) = default;
  Sprite& operator=(Sprite &&other) noexcept;

  SDL2pp::Texture& sprite();

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

  int width() const;
  int height() const;

  ~Sprite();
};


#endif //QUANTUM_CHESS_PROJ_SPRITE_H
