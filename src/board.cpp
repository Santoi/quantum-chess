#include "board.h"
#include "chessman/chessman_container.h"
#include <utility>

Board::Board(): chessmen(), board(), next_white(true) {}

void Board::addChessman(ChessmanContainer && chessman_cont){
    Chessman * chessman = chessman_cont.get();
    chessmen.push_back(std::move(chessman_cont));
    if (board.count(chessman->getPosition()))
		throw std::invalid_argument("ya hay una pieza alli");
    board.insert(std::pair<Position, Chessman *>(chessman->getPosition(), chessman));
}

void Board::move(const Position & initial, const Position & final) {
    Chessman * chessman = getChessmanAt(initial);
    if (!chessman)
        throw std::invalid_argument("no hay ninguna pieza ahi");
    if (chessman->isWhite() != next_white)
        throw std::invalid_argument("no es tu turno");
    chessman->move(initial, final);
    next_white = !next_white;
}

void Board::removeChessmanOf(const Position & position) {
	if (board.count(position))
		board.erase(position);
}

void Board::addChessmanOfIn(const Position & initial, const Position & final) {
    Chessman * chessman = getChessmanAt(initial);
    if (!chessman)
        throw std::invalid_argument("no hay ninguna pieza ahi");
    if (board.count(final))
		throw std::invalid_argument("ya hay una pieza alli");
	board.erase(initial);
    board.insert(std::pair<Position, Chessman *>(final, chessman));
}

Chessman *Board::getChessmanAt(const Position &position) {
    if (board.count(position))
        return board.at(position);
    return nullptr;
}

bool Board::isNextWhite() const{
    return next_white;
}

void Board::load() {
    addChessman(std::move(ChessmanContainer('T', Position(0, 0), true, *this)));
    addChessman(std::move(ChessmanContainer('H', Position(1, 0), true, *this)));
    addChessman(std::move(ChessmanContainer('B', Position(2, 0), true, *this)));
    addChessman(std::move(ChessmanContainer('Q', Position(3, 0), true, *this)));
    addChessman(std::move(ChessmanContainer('K', Position(4, 0), true, *this)));
    addChessman(std::move(ChessmanContainer('B', Position(5, 0), true, *this)));
    addChessman(std::move(ChessmanContainer('H', Position(6, 0), true, *this)));
    addChessman(std::move(ChessmanContainer('T', Position(7, 0), true, *this)));

    for(uint8_t i = 0; i < 8; i++)
        addChessman(std::move(ChessmanContainer('P', Position(i, 1), true, *this)));

    addChessman(std::move(ChessmanContainer('T', Position(0, 7), false, *this)));
    addChessman(std::move(ChessmanContainer('H', Position(1, 7), false, *this)));
    addChessman(std::move(ChessmanContainer('B', Position(2, 7), false, *this)));
    addChessman(std::move(ChessmanContainer('Q', Position(3, 7), false, *this)));
    addChessman(std::move(ChessmanContainer('K', Position(4, 7), false, *this)));
    addChessman(std::move(ChessmanContainer('B', Position(5, 7), false, *this)));
    addChessman(std::move(ChessmanContainer('H', Position(6, 7), false, *this)));
    addChessman(std::move(ChessmanContainer('T', Position(7, 7), false, *this)));
    for(uint8_t i = 0; i < 8; i++)
        addChessman(std::move(ChessmanContainer('P', Position(i, 6), false, *this)));
}
