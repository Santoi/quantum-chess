#include "board.h"
#include "chess_exception.h"
#include "chessman/king.h"
#include "chessman/queen.h"
#include "chessman/tower.h"
#include "chessman/bishop.h"
#include "chessman/knight.h"
#include "chessman/pawn.h"
#include <utility>
#include <algorithm>
#include <memory>

Board::Board(): chessmen(), board(), next_white(true), coin() {}

Board::Board(int seed): chessmen(), board(), next_white(true), coin(seed) {}

// TODO interfaz cuantica, dejarla a punto.

// TODO testear BOARD.

void Board::addNewChessman(char chessman_, Position position_,
                                 bool white_){
    std::unique_ptr<Chessman> new_chessman = createChessman(chessman_,
                                                            position_,
                                                            white_);
    Chessman * ptr = new_chessman.get();
    chessmen.push_back(std::move(new_chessman));

    for (size_t i = 0; i < ptr->countPositions(); i++){
        Position position = Position(ptr->getPosition(i));
        if (board.count(Position(position)))
            throw ChessException("ya hay una pieza alli");
        board.insert(std::make_pair(Position(position),
                                    ptr));
    }
}

void Board::move(const Position & initial, const Position & final) {
    Chessman * chessman = getChessmanAt(initial);
    if (!chessman)
        throw ChessException("no hay ninguna pieza ahi");
    if (chessman->isWhite() != next_white)
        throw ChessException("no es tu turno");
    chessman->move(initial, final);
    next_white = !next_white;
}

void Board::split(const Position & initial, const Position & pos1,
                  const Position & pos2){
    Chessman * chessman = getChessmanAt(initial);
    if (!chessman)
        throw ChessException("no hay ninguna pieza alli");
    if (chessman->isWhite() != next_white)
        throw ChessException("no es tu turno");
    chessman->split(initial, pos1, pos2);
    next_white = !next_white;
}

void Board::merge(const Position & initial1, const Position & initial2,
                  const Position & final){
    Chessman * chessman_1 = getChessmanAt(initial1),
             * chessman_2 = getChessmanAt(initial2);
    if (!chessman_1)
        throw ChessException("no hay ninguna pieza alli");
    if (!chessman_2)
        throw ChessException("no hay ninguna pieza alli");
    if (chessman_1 != chessman_2)
        throw ChessException("se esta tratando de unir dos piezas distintas");
    // TODO chequear el otro? chessman ya chequea.
    if (chessman_1->isWhite() != next_white)
        throw ChessException("no es tu turno");
    chessman_1->merge(initial1, initial2, final);
    next_white = !next_white;
}

void Board::addChessmanIn(const Position &position, Chessman * chessman) {
    if (board.count(position))
        throw ChessException("ya hay una pieza alli");
    board.insert(std::pair<Position, Chessman *>(Position(position),
                                                 chessman));
}

void Board::removeChessmanOf(const Position & position) {
	if (board.count(position))
		board.erase(position);
}

void Board::addChessmanOfIn(const Position & initial, const Position & final) {
    Chessman * chessman = getChessmanAt(initial);
    if (!chessman)
        throw ChessException("no hay ninguna pieza ahi");
    if (board.count(final))
		throw ChessException("ya hay una pieza alli");
	board.erase(initial);
    board.insert(std::pair<Position, Chessman *>(final, chessman));
}

void Board::addChessmanOfIn(const Position & initial, const Position & pos1,
                            const Position & pos2) {
    Chessman * chessman = getChessmanAt(initial);
    if (!chessman)
        throw ChessException("no hay ninguna pieza ahi");
    if (board.count(pos1) || board.count(pos2))
        throw ChessException("ya hay una pieza alli");
    board.erase(initial);
    board.insert(std::pair<Position, Chessman *>(pos1, chessman));
    board.insert(std::pair<Position, Chessman *>(pos2, chessman));
}

Chessman *Board::getChessmanAt(const Position &position) {
    if (board.count(position))
        return board.at(position);
    return nullptr;
}

bool Board::isNextWhite() const{
    return next_white;
}

bool Board::isThere(Chessman * chessman) {
    return std::any_of(board.begin(), board.end(),
                       [&] (std::pair<const Position, Chessman *> pair) {
                                    return pair.second == chessman; });
}

void Board::loadVectors(std::vector<char> & characters_, std::vector<bool> & colors_,
                        std::vector<Position> & positions_) {
    // TODO hacerlo un paquete solo.
    characters_.reserve(board.size());
    colors_.reserve(board.size());
    positions_.reserve(board.size());
    for (auto it = board.begin(); it != board.end(); ++it) {
        characters_.push_back(it->second->print());
        positions_.push_back(it->first);
        colors_.push_back(it->second->isWhite());
    }
}

std::unique_ptr<Chessman> Board::createChessman(char chessman_,
                                                Position position_,
                                                bool white_) {
    Chessman * pointer = nullptr;
    switch (chessman_){
        case 'K':
            pointer = new King(position_, white_, *this);
            break;
        case 'Q':
            pointer = new Queen(position_, white_, *this);
            break;
        case 'T':
            pointer = new Tower(position_, white_, *this);
            break;
        case 'B':
            pointer = new Bishop(position_, white_, *this);
            break;
        case 'H':
            pointer = new Knight(position_, white_, *this);
            break;
        case 'P':
            pointer = new Pawn(position_, white_, *this);
            break;
        default:
            throw ChessException("esa letra no "
                                 "representa ninguna pieza");
    }
    if (!pointer)
        throw std::runtime_error("cannot allocate memory for chessman");
    return std::unique_ptr<Chessman>(pointer);
}

void Board::load() {
    addNewChessman('T', Position(0, 0), true);
    addNewChessman('H', Position(1, 0), true);
    addNewChessman('B', Position(2, 0), true);
    addNewChessman('Q', Position(3, 0), true);
    addNewChessman('K', Position(4, 0), true);
    addNewChessman('B', Position(5, 0), true);
    addNewChessman('H', Position(6, 0), true);
    addNewChessman('T', Position(7, 0), true);
    addNewChessman('T', Position(0, 7), false);
    addNewChessman('H', Position(1, 7), false);
    addNewChessman('B', Position(2, 7), false);
    addNewChessman('Q', Position(3, 7), false);
    addNewChessman('K', Position(4, 7), false);
    addNewChessman('B', Position(5, 7), false);
    addNewChessman('H', Position(6, 7), false);
    addNewChessman('T', Position(7, 7), false);

    for (uint8_t i = 0; i < 8; i++)
        addNewChessman('P', Position(i, 1), true);

    for (uint8_t i = 0; i < 8; i++)
        addNewChessman('P', Position(i, 6), false);
}

bool Board::flipACoin() {
    return coin.flip();
}
