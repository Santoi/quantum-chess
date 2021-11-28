#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H

#include "pixel_coordinate.h"
#include <string>

class TextEntryButton {
private:
    //has a text entry field
    const std::string button_name;
    int x;
    int y;
    int width;
    int height;
    bool expecting_text;

public:

    TextEntryButton() = delete;

    TextEntryButton(const std::string& button_name_);

    void setAreaAndPosition(int x_, int y_, int height_, int width_);

    bool enableTextEntryIfClicked(const PixelCoordinate& pixel);

    std::string getText() const;

    void disableTextEntry();
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
