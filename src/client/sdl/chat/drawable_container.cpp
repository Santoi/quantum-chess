#include "drawable_container.h"

#define NO_LIMIT -1

DrawableContainer::DrawableContainer()
                  :max_drawables(NO_LIMIT) {
}

DrawableContainer::DrawableContainer(int max_drawables_)
                    :max_drawables(max_drawables_) {
}

void DrawableContainer::addDrawableToList(DrawableText&& drawable) {
    if (this->drawables_list.size() == this->max_drawables)
        this->drawables_list.pop_front();
    this->drawables_list.push_back(std::move(drawable));
}

void DrawableContainer::drawAllDrawablesStartingFrom(int x, int y) {
    int i = 0;
    for (auto const& drawable : this->drawables_list) {
        drawable.drawIn(x, y - i);
        i++;  //i is increased respectively
    }
}

