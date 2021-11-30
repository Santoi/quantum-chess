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
    int scale;

public:

    Button() = delete;

    Button(Renderer& renderer_, const std::string& not_pressed_file_name,
           const std::string& pressed_file_name);

    virtual bool fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) = 0;

    void setScale(const int& scale_);

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

    bool fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) override;

};


#endif //QUANTUM_CHESS_PROJ_BUTTON_H
