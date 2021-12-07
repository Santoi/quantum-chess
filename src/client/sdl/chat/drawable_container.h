#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H


#include "drawable_text.h"
#include <list>
#include <mutex>

#define NO_LIMIT -1


template<class T>
class DrawableContainer {
private:
  std::list<T> drawables_list;
  size_t max_drawables;

public:
  DrawableContainer();

  explicit DrawableContainer(unsigned int max_drawables_);

  void addDrawable(T &&drawable);

  void render(int x, int y);

  void clear();
};

template<class T>
DrawableContainer<T>::DrawableContainer()
        :max_drawables(NO_LIMIT) {
}

template<class T>
DrawableContainer<T>::DrawableContainer(unsigned int max_drawables_)
        :max_drawables(max_drawables_) {
}

template<class T>
void DrawableContainer<T>::addDrawable(T &&drawable) {
  if (drawables_list.size() == max_drawables)
    drawables_list.pop_back();
  drawables_list.push_front(std::move(drawable));
}

template<class T>
void DrawableContainer<T>::clear() {
  drawables_list.clear();
}

template<class T>
void DrawableContainer<T>::render(int x, int y) {
  for (auto &drawable: drawables_list) {
    drawable.render(x, y);
    y -= drawable.getDrawableHeight();
  }
}

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CONTAINER_H
