#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H

#include <string>

class DrawableText {
private:
    std::string text;

public:
    DrawableText() = delete;

    DrawableText(const std::string& text_);

    void drawIn(int x, int y) const;
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H
