#ifndef QUANTUM_CHESS_PROJ_TILE_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_TILE_SPRITE_REPOSITORY_H

#include <map>
#include "sprite.h"

class TileSpriteRepository {
public:
    typedef enum {
        TILE_DEFAULT,
        TILE_MOVE,
        TILE_ENTANGLED,
        TILE_QUANTUM,
        TILE_SPLIT,
        TILE_MERGE
    } TileType;

private:
    std::map<TileType, Sprite> white_tiles;
    std::map<TileType , Sprite> black_tiles;

    void loadWhite(Renderer & renderer);

    void loadBlack(Renderer & renderer);

public:
    explicit TileSpriteRepository(Renderer & renderer);

    Sprite &getTile(TileType type, bool black);
};


#endif //QUANTUM_CHESS_PROJ_TILE_SPRITE_REPOSITORY_H
