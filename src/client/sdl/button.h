#ifndef QUANTUM_CHESS_PROJ_BUTTON_H
#define QUANTUM_CHESS_PROJ_BUTTON_H

#include "pixel_coordinate.h"
#include "text_entry_button.h"
#include "drawable_button.h"
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "../../common/src/client_data.h"


class Renderer;

class Button {
protected:
  DrawableButton drawable;

public:

  Button() = delete;

  Button(ButtonSpriteRepository &button_repository,
         TextSpriteRepository &text_repository, std::string &&type,
         std::string &&text);

  virtual bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                                   std::list<std::string> &tokens) = 0;

  void render();

  void setAreaAndPosition(int x, int y, int width, int height);

  virtual ~Button() = default;
};

class ConnectButton : public Button {
private:
  const std::list<TextEntryButton> &text_entries;

public:
  ConnectButton() = delete;

  ConnectButton(ButtonSpriteRepository &button_repository,
                TextSpriteRepository &text_repository,
                std::string &&button_text,
                const std::list<TextEntryButton> &text_entry_buttons);

  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~ConnectButton() override = default;
};

class PickMatchButton : public Button {
private:
  uint16_t match_id;

public:

  PickMatchButton() = delete;

  PickMatchButton(ButtonSpriteRepository &button_repository,
                  TextSpriteRepository &text_repository,
                  std::vector<ClientData> &client_data,
                  uint16_t match_id);

  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~PickMatchButton() override = default;
};


#endif //QUANTUM_CHESS_PROJ_BUTTON_H
