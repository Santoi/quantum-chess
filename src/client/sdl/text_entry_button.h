#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H

#include "pixel_coordinate.h"

class TextEntryButton {
private:
    //has a text entry field
    int x;
    int y;
    int width;
    int height;
    bool expecting_text;

public:

    TextEntryButton();

    void setAreaAndPosition(int x, int y, int height, int width);

    bool enableTextEntryIfClicked(const PixelCoordinate& pixel);

    void disableTextEntry();
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
