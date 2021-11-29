#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H


class Renderer;

class DrawableButton {
private:
    Renderer& renderer;
    int x;
    int y;
    int height;
    int width;

public:

    DrawableButton() = delete;

    explicit DrawableButton(Renderer& renderer_);

    void render();

    void setAreaAndPosition(int x, int y, int height, int width);

    ~DrawableButton() = default;
};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
