#ifndef QUANTUM_CHESS_PROJ_BUTTON_H
#define QUANTUM_CHESS_PROJ_BUTTON_H

#include "../sdl/pixel_coordinate.h"
#include "text_entry_button.h"
#include "../sdl/drawables/drawable_button.h"
#include "../../common/client_data.h"
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "../../common/client_data.h"


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

  virtual void render();

  void setAreaAndPosition(size_t x, size_t y, size_t width, size_t height);

  void resetButton();

  virtual ~Button() = default;
};

class ConnectButton : public Button {
private:
  const std::vector<std::unique_ptr<TextEntryButton>> &text_entries_ptr;

public:
  ConnectButton() = delete;

  ConnectButton(ButtonSpriteRepository &button_repository,
                TextSpriteRepository &text_repository,
                std::string &&button_text,
                const std::vector<std::unique_ptr<TextEntryButton>> &text_entry_buttons);

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

class NextMatchesButton : public Button {
public:
  NextMatchesButton() = delete;

  NextMatchesButton(ButtonSpriteRepository &button_repository,
                    TextSpriteRepository &text_repository);

  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~NextMatchesButton() override = default;
};

class PreviousMatchesButton : public Button {
public:
  PreviousMatchesButton() = delete;

  PreviousMatchesButton(ButtonSpriteRepository &button_repository,
                        TextSpriteRepository &text_repository);

  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~PreviousMatchesButton() override = default;
};

class RefreshMatchesButton : public Button {
public:
  RefreshMatchesButton() = delete;

  RefreshMatchesButton(ButtonSpriteRepository &button_repository,
                       TextSpriteRepository &text_repository);

  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~RefreshMatchesButton() override = default;
};

class RoleButton : public Button {
private:
  const ClientData::Role role;
  TextureSprite *unavailable_role_sprite;
  bool role_is_available;

public:

  RoleButton() = delete;

  RoleButton(ButtonSpriteRepository &button_repository,
             TextSpriteRepository &text_repository,
             ClientData::Role role_, std::string &&type,
             bool role_is_available_);

  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  void render() override;

  ~RoleButton() override = default;

private:
  void addEnumToListOfTokens(std::list<std::string> &tokens);
};

class ReturnToMatchSelectionButton: public Button {

public:

    ReturnToMatchSelectionButton(ButtonSpriteRepository &button_repository,
                                 TextSpriteRepository &text_repository,
                                 std::string &&button_text);

    bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                             std::list<std::string> &tokens) override;

    ~ReturnToMatchSelectionButton() override = default;
};

#endif //QUANTUM_CHESS_PROJ_BUTTON_H