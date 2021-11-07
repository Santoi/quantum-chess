#include "board.h"
#include "chessman/chessman_container.h"
#include "chess_exception.h"
#include <utility>

Board::Board(): chessmen(), board(), next_white(true), coin() {}

Board::Board(int seed): chessmen(), board(), next_white(true), coin(seed) {}

void Board::addChessman(ChessmanContainer && chessman_cont){
    Chessman * chessman = chessman_cont.get();
    chessmen.push_back(std::move(chessman_cont));

    auto positions = chessman->getAllPositions();
    for (QuantumPosition & qpos: positions) {
        if (board.count(Position(qpos)))
            throw ChessException("ya hay una pieza alli");
        board.insert(std::pair<Position, Chessman *>(Position(qpos),
                                                     chessman));
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

void Board::addChessmanIn(const Position &position, Chessman * chessman) {
    if(board.count(position))
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

void Board::load() {
    addChessman(std::move(ChessmanContainer('T', Position(0, 0),
                                            true, *this)));
    addChessman(std::move(ChessmanContainer('H', Position(1, 0),
                                            true, *this)));
    addChessman(std::move(ChessmanContainer('B', Position(2, 0),
                                            true, *this)));
    addChessman(std::move(ChessmanContainer('Q', Position(3, 0),
                                            true, *this)));
    addChessman(std::move(ChessmanContainer('K', Position(4, 0),
                                            true, *this)));
    addChessman(std::move(ChessmanContainer('B', Position(5, 0),
                                            true, *this)));
    addChessman(std::move(ChessmanContainer('H', Position(6, 0),
                                            true, *this)));
    addChessman(std::move(ChessmanContainer('T', Position(7, 0),
                                            true, *this)));

    for (uint8_t i = 0; i < 8; i++)
        addChessman(std::move(ChessmanContainer('P', Position(i, 1),
                                                true, *this)));

    addChessman(std::move(ChessmanContainer('T', Position(0, 7),
                                            false, *this)));
    addChessman(std::move(ChessmanContainer('H', Position(1, 7),
                                            false, *this)));
    addChessman(std::move(ChessmanContainer('B', Position(2, 7),
                                            false, *this)));
    addChessman(std::move(ChessmanContainer('Q', Position(3, 7),
                                            false, *this)));
    addChessman(std::move(ChessmanContainer('K', Position(4, 7),
                                            false, *this)));
    addChessman(std::move(ChessmanContainer('B', Position(5, 7),
                                            false, *this)));
    addChessman(std::move(ChessmanContainer('H', Position(6, 7),
                                            false, *this)));
    addChessman(std::move(ChessmanContainer('T', Position(7, 7),
                                            false, *this)));
    for (uint8_t i = 0; i < 8; i++)
        addChessman(std::move(ChessmanContainer('P', Position(i, 6),
                                                false, *this)));
}

bool Board::flipACoin() {
    return coin.flip();
}
