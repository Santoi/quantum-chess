#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H


#include "drawable_text.h"
#include <list>

#define NO_LIMIT -1


Template <class T>
class DrawableContainer {
private:
    std::list<T> drawables_list;
    int max_drawables;

public:
    DrawableContainer();

    DrawableContainer(unsigned int max_drawables_);

    void addDrawableToList(T&& drawable);

    void drawAllDrawablesStartingFrom(int x, int y);
};

template <class T>
DrawableContainer<T>::DrawableContainer()
                    :max_drawables(NO_LIMIT) {
}

template <class T>
DrawableContainer<T>::DrawableContainer(unsigned int max_drawables_);
        :max_drawables(max_drawables_) {
}

template <class T>
void DrawableContainer<T>::addDrawableToList(T&& drawable) {
    if (this->drawables_list.size() == this->max_drawables)
        this->drawables_list.pop_front();
    this->drawables_list.push_back(std::move(drawable));
}

template <class T>
void DrawableContainer<T>::drawAllDrawablesStartingFrom(int x, int y) {
    int i = 0;
    for (auto const& drawable : this->drawables_list) {
        drawable.drawIn(x, y - i);
        i++;  //i is increased respectively
    }
}

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H
