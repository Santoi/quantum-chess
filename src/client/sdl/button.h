#ifndef QUANTUM_CHESS_PROJ_BUTTON_H
#define QUANTUM_CHESS_PROJ_BUTTON_H

#include "pixel_coordinate.h"
#include "text_entry_button.h"
#include "drawable_button.h"
#include <list>
#include <string>
#include <memory>


class Renderer;

class Button {
private:
    DrawableButton drawable;

public:

    Button() = delete;

    explicit Button(Renderer& renderer_);

    virtual bool fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) = 0;

    void render();

    void setAreaAndPosition(int x, int y, int height, int width);
};

class ConnectButton: public Button {
private:
    const std::list<std::unique_ptr<TextEntryButton>>& text_entries;

public:
    ConnectButton() = delete;

    explicit ConnectButton(Renderer& renderer_, const std::list<std::unique_ptr<TextEntryButton>>& text_entry_buttons_ptr);

    bool fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) override;

    ~ConnectButton() = default;
};

class PickMatchButton: public Button {

public:

    bool fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens);

};


#endif //QUANTUM_CHESS_PROJ_BUTTON_H
