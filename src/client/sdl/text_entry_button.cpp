#include "text_entry_button.h"
#include "chat/font.h"
#include "chat/drawable_text.h"
#include "drawable_text_entry_button.h"

#define MAX_INPUT 20

TextEntryButton::TextEntryButton(Renderer& renderer_, TextSpriteRepository repository, const std::string& button_name_)
                : text_entry(30), drawable_text_button(repository,
                                                       button_name_), expecting_text_entry(false) {
    input_text.reserve(MAX_INPUT);
}

void TextEntryButton::setAreaAndPosition(int x_, int y_, int height_, int width_) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    drawable_text_button.setAreaAndPosition(x_, y_, height_, width_);
}

void TextEntryButton::render() {
    std::lock_guard<std::mutex> lock_guard(mutex);
    drawable_text_button.render(text_entry.getText());
}

bool TextEntryButton::enableTextEntryIfClicked(const PixelCoordinate& pixel_) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    if (drawable_text_button.pixelIsOnTextEntry(pixel_)) {
        expecting_text_entry = true;
        text_entry.enableEntry();
        std::cout << "Text entry pressed!" << std::endl;
        return true;
    }
    return false;
}

void TextEntryButton::disableTextEntry() {
    std::lock_guard<std::mutex> lock_guard(mutex);
    expecting_text_entry = false;
    text_entry.disableEntry();
}

void TextEntryButton::concatIfEnabled(const std::string &text_) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    if (!expecting_text_entry)
        return;
    if (text_entry.isEnabled())
      text_entry.concat(text_);
}

std::string TextEntryButton::getText() const {
    std::lock_guard<std::mutex> lock_guard(mutex);
    return text_entry.getText();
}
