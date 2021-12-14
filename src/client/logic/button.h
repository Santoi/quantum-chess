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

  //Derived Button checks if pixel is on button: if it is then
  //it fills tokens accordingly and a true is returned.
  //Else nothing happens with tokens list and a false is returned.
  virtual bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                                   std::list<std::string> &tokens) = 0;

  //Calls drawable's method render.
  virtual void render();

  //Calls drawable's method with same name and parameters.
  void setAreaAndPosition(size_t x, size_t y, size_t width, size_t height);

  //Calls drawable's method disablePressedStatus.
  void resetButtonToNotPressedState();

  virtual ~Button() = default;
};

class ConnectButton : public Button {
private:
  const std::vector<std::unique_ptr<TextEntryButton>> &text_entries_ptr;

public:
  ConnectButton() = delete;

  //Creates a ConnectButton with a text_entry_buttons array.
  ConnectButton(ButtonSpriteRepository &button_repository,
                TextSpriteRepository &text_repository,
                std::string &&button_text,
                const std::vector<std::unique_ptr<TextEntryButton>>
                &text_entry_buttons);

  //If pixel is on button, it adds to the tokens list the content of each text
  // entry button and true is returned, otherwise return false
  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~ConnectButton() override = default;
};

class PickMatchButton : public Button {
private:
  uint16_t match_id;

public:
  PickMatchButton() = delete;

  //PickMatchButton is created with a vector of client data and a match id.
  PickMatchButton(ButtonSpriteRepository &button_repository,
                  TextSpriteRepository &text_repository,
                  std::vector<ClientData> &client_data,
                  uint16_t match_id);

  //If pixel is on button, the match_id is added to the list of tokens
  //as a string and a true is returned.
  //Else nothing happens with tokens list and a false is returned.
  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~PickMatchButton() override = default;
};

class NextMatchesButton : public Button {
public:
  NextMatchesButton() = delete;

  NextMatchesButton(ButtonSpriteRepository &button_repository,
                    TextSpriteRepository &text_repository);

  //If pixel is on button, "NEXT" string is added to the list of tokens
  //as a string and a true is returned.
  //Else nothing happens with tokens list and a false is returned.
  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~NextMatchesButton() override = default;
};

class PreviousMatchesButton : public Button {
public:
  PreviousMatchesButton() = delete;

  PreviousMatchesButton(ButtonSpriteRepository &button_repository,
                        TextSpriteRepository &text_repository);

  //If pixel is on button, "PREV" string is added to the list of tokens
  //as a string and a true is returned.
  //Else nothing happens with tokens list and a false is returned.
  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  ~PreviousMatchesButton() override = default;
};

class RefreshMatchesButton : public Button {
public:
  RefreshMatchesButton() = delete;

  RefreshMatchesButton(ButtonSpriteRepository &button_repository,
                       TextSpriteRepository &text_repository);

  //If pixel is on button, UINT16_MAX as string is added to the list of tokens
  //as a string and a true is returned.
  //Else nothing happens with tokens list and a false is returned.
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

  //Creates a RoleButton that has the given role
  RoleButton(ButtonSpriteRepository &button_repository,
             TextSpriteRepository &text_repository,
             ClientData::Role role_, std::string &&type,
             bool role_is_available_);

  //If pixel is on button, role as string is added to the list of tokens
  //as a string and a true is returned.
  //Else nothing happens with tokens list and false is returned.
  bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                           std::list<std::string> &tokens) override;

  //Renders drawable as usual. If role is available, nothing else is
  //rendered. Else, an additional layer is rendered over the drawable
  //to signal unavailability.
  void render() override;

  ~RoleButton() override = default;

private:
  //Transforms role to a string and adds it to the tokens list.
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

class OptionButton: public Button {
private:
    std::string option;

public:
    OptionButton(ButtonSpriteRepository &button_repository,
                                 TextSpriteRepository &text_repository,
                                 std::string &&text, std::string &&option);

    bool fillTokensIfClicked(const PixelCoordinate &pixel_,
                             std::list<std::string> &tokens) override;

    ~OptionButton() override = default;
};


#endif //QUANTUM_CHESS_PROJ_BUTTON_H
