#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H


#include "drawable_text.h"
#include <list>

class DrawableContainer {
private:
    std::list<DrawableText> drawables_list;
    int max_drawables;

public:
    DrawableContainer();

    DrawableContainer(int max_drawables_);

    void addDrawableToList(DrawableText&& drawable);

    void drawAllDrawablesStartingFrom(int x, int y);
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H
