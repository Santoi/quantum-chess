#include "chessman_container.h"
#include "chessman.h"
#include "king.h"
#include "queen.h"
#include "tower.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"

ChessmanContainer::ChessmanContainer(char chessman_, Position position, bool white, Board &board): pointer(nullptr) {
    switch (chessman_){
        case 'K':
            pointer = new King(position, white, board);
            break;
        case 'Q':
            pointer = new Queen(position, white, board);
            break;
        case 'T':
            pointer = new Tower(position, white, board);
            break;
        case 'B':
            pointer = new Bishop(position, white, board);
            break;
        case 'H':
            pointer = new Knight(position, white, board);
            break;
        case 'P':
            pointer = new Pawn(position, white, board);
            break;
        default:
            throw std::invalid_argument("esa letra no representa ninguna pieza");
    }
    if (!pointer)
        throw std::runtime_error("no se pudo alocar memoria");
}

Chessman * ChessmanContainer::get(){
    if (pointer)
        return pointer;
    throw std::runtime_error("el contenedor no tiene ninguna pieza");
}

ChessmanContainer::~ChessmanContainer() {
    delete pointer;
}

ChessmanContainer::ChessmanContainer(ChessmanContainer &&orig): pointer(orig.pointer){
    orig.pointer = nullptr;
}

ChessmanContainer &ChessmanContainer::operator=(ChessmanContainer &&orig) {
    delete pointer;
    pointer = orig.pointer;
    orig.pointer = nullptr;
    return *this;
}
