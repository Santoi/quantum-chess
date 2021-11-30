#ifndef QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
#define QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H

#include "pixel_coordinate.h"
#include "texture_sprite.h"
#include "renderer.h"
#include "chat/text_entry.h"
#include "drawable_text_entry_button.h"
#include <string>
#include <mutex>

class TextEntryButton {
private:
    TextEntry text_entry;
    DrawableTextEntryButton drawable_text_button;
    mutable std::mutex mutex;
    bool expecting_text_entry;
    std::string input_text;

public:

    TextEntryButton() = delete;

    TextEntryButton(Renderer& renderer_, const std::string& button_name_);

    void setAreaAndPosition(int x_, int y_, int height_, int width_);

    bool enableTextEntryIfClicked(const PixelCoordinate& pixel);

    void render();

    void concatIfEnabled(const std::string &text_);

    std::string getText() const;

    void disableTextEntry();

private:
    bool pixelIsOnTextEntry(const PixelCoordinate& pixel);
};


#endif //QUANTUM_CHESS_PROJ_TEXT_ENTRY_BUTTON_H
