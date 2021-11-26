#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H

#include <map>
#include "sprite.h"

class ChessmanSpriteRepository {
    std::map<std::string, Sprite> chessmen;
    std::map<std::string, Sprite> fills;

    void loadFills(Renderer & renderer);

    void loadChessmen(Renderer & renderer);

public:
    ChessmanSpriteRepository(Renderer & renderer);

    Sprite &getChessman(const std::string & string);

    Sprite &getFill(const std::string &string);
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H
