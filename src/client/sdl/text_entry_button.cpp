#include "text_entry_button.h"
#include "chat/font.h"
#include "chat/drawable_text.h"
#include "drawable_text_entry_button.h"

#define MAX_INPUT 20

TextEntryButton::TextEntryButton(Renderer& renderer_, const std::string& button_name_)
                :text_entry(30), drawable_text_button(renderer_, button_name_), expecting_text_entry(false) {
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

void TextEntryButton::backSpaceIfEnabled() {
    //text_entry.backspace();
    std::lock_guard<std::mutex> lock_guard(mutex);
    if (!expecting_text_entry)
        return;
    else if (!input_text.empty())
        input_text.pop_back();
    std::cout << input_text << std::endl;
}


void TextEntryButton::concatIfEnabled(const std::string &text_) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    if (!expecting_text_entry)
        return;
    input_text.append(text_);
    //text_entry.concat(text_);
    std::cout << input_text << std::endl;
}

std::string TextEntryButton::getText() const {
    std::lock_guard<std::mutex> lock_guard(mutex);
    //get string from text entry
    return input_text;
}
