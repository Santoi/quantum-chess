#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include "../sdl/renderer.h"
#include "../sdl/sprite.h"
#include "../communication/client_protocol.h"
#include <map>
#include <string>

class Renderer;

class Chessman {
private:
  Renderer &renderer;
  Sprite sprite_;
  Sprite fill;
  std::map<std::string, std::pair<std::string, std::string>> image;
  double probability;

public:
  Chessman(Renderer &renderer, const ClientProtocol::ChessmanData &data);
  Chessman(Chessman &&other) noexcept;
  Chessman(const Chessman &other) = delete;
  Chessman& operator=(Chessman &&other) noexcept;
  void render(int x, int y);
  ~Chessman();
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
