#ifndef QUANTUM_CHESS_PROJ_SCENE_H
#define QUANTUM_CHESS_PROJ_SCENE_H

class Scene {
protected:
    int scale;

public:
    Scene() = delete;

    Scene(int scale);

    virtual void render() = 0;

    virtual void setScale(int scale_) = 0;
};


#endif //QUANTUM_CHESS_PROJ_SCENE_H
