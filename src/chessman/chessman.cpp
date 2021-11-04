#include <stdexcept>
#include <vector>
#include <iostream>
#include "chessman.h"

// TODO implementar comer.
// TODO ver que excepciones cambiar a ChessError (revisar todas)
// TODO aclarar no importa como se calcule el path siempre se deja el final al final.
Chessman::Chessman(const Position & position_, bool white_, Board & board_):
                   position(position_),
                   board(board_), white(white_) {}


void Chessman::move(const Position & initial, const Position & final) {
    std::vector<Chessman *> chessmen_in_path;
    // TODO desharcodear
    // TODO encapsular en canMove();
    checkCanMove(initial, final, chessmen_in_path);
    // TODO deberia chequearlo en calculatePosibleMoves
    if (Chessman * final_chessman = board.getChessmanAt(final)) {
        if(final_chessman->isQuantum())
            int hola = 5; // TODO capture o measure.
        else if (final_chessman->white != white)
            board.removeChessmanOf(final);
        else
            throw std::invalid_argument("la pieza no se puede mover alli, hay una pieza no cuantica del mismo color");
    }
    // TODO editar el board desde aca?
    position = final;
    board.addChessmanOfIn(initial, final);
    // TODO LOGICA DE COMER (VA A DIFERIR EN PAWN) ENTRELAZAMIENTO, MEASURE ETC.
}

void Chessman::checkCanMove(Position initial, Position final, std::vector<Chessman *> & chessmen_in_path) const{
    std::vector<Position> path;
    std::vector<Position> posible_moves;
    if (initial != position)
        throw std::invalid_argument("la ficha no está en esa posicion");
    calculatePosibleMoves(initial, posible_moves);
    if (std::find(posible_moves.begin(), posible_moves.end(), final) == posible_moves.end())
        throw std::invalid_argument("la pieza no se puede mover alli");
    calculatePath(initial, final, path);
    getPathMiddleChessmen(path, &chessmen_in_path);
}

bool Chessman::checkFreePath(const std::vector<Position> & path) const {
    return getPathMiddleChessmen(path, nullptr);
}

bool Chessman::getPathMiddleChessmen(const std::vector<Position> & path, std::vector<Chessman *> * chessmen) const {
    if(chessmen) {
        *chessmen = std::vector<Chessman *>();
        chessmen->reserve(7);
    }
    for (size_t i = 0; i < path.size(); i++) {
        if (Chessman *chessman = board.getChessmanAt(path[i])) {
            if (!(chessman->isQuantum() || ((i == path.size() - 1) && chessman->white != white))) {
                if (chessmen)
                    *chessmen = std::vector<Chessman *>();
                return false;
            }
        }
    }
    return true;
}

bool Chessman::isQuantum() const {
    // TODO ver si cuando es tradicional solo tiene una el arbol directamente.
    // TODO desharcodear.
    return false;
}

bool Chessman::isWhite() const {
    return white;
}

Position Chessman::getPosition() {
    return position;
}

void Chessman::calculatePath(const Position & initial, const Position & final, std::vector<Position> & path) const {
    // aclarar no importa como se calcule el path siempre se deja el final al final.
    if (initial == final)
        std::invalid_argument("no se puede calcular el camino entre posiciones iguales");
    if (initial.y() == final.y())
        calculateFilePath(initial, final, path);
    else if (initial.x() == final.x())
        calculateRowPath(initial, final, path);
    else if (abs((initial.x() - final.x()) / (initial.y() - final.y())) == 1)
        calculateDiagonalPath(initial, final, path);
    // TODO calcular el caso de diagonal.
    else
        throw std::invalid_argument("ese movimiento es imposible");
}

void Chessman::calculateFilePath(const Position & initial, const Position & final, std::vector<Position> & path) const {
    const Position & bottom = (initial.x() < final.x()) ? initial : final;
    const Position & top = (initial.x() < final.x()) ? final : initial;
    path = std::vector<Position> ();
    path.reserve(7);

    for (uint8_t i = bottom.x() + 1; i < top.x(); i++)
        path.push_back(Position(i, initial.y()));
    path.push_back(final);
}

void Chessman::calculateRowPath(const Position & initial, const Position & final, std::vector<Position> & path) const {
    const Position & bottom = (initial.y() < final.y()) ? initial : final;
    const Position & top = (initial.y() < final.y()) ? final : initial;
    path = std::vector<Position> ();
    path.reserve(7);

    for (uint8_t i = bottom.y() + 1; i < top.y(); i++)
        path.push_back(Position(initial.x(), i));
    path.push_back(final);
}

void Chessman::calculateDiagonalPath(const Position & initial, const Position final, std::vector<Position> & path) const {
    int8_t sum_x = (initial.x() < final.x()) ? 1 : -1;
    int8_t sum_y = (initial.y() < final.y()) ? 1 : -1;
    path = std::vector<Position> ();
    path.reserve(6);

    for (int8_t i = initial.x() + sum_x, j = initial.y() + sum_y;
         i * sum_x < final.x() * sum_x && j * sum_y < final.y() * sum_y; i += sum_x, j += sum_y)
        path.push_back(Position(i, j));
    path.push_back(final);
}

std::ostream &operator<<(std::ostream &os, const Chessman &chessman) {
    if (chessman.white)
        os << GREEN << chessman.print() << RESET;
    else
        os << RED << chessman.print() << RESET;
    return os;
}
/*
Chessman::Chessman(const Chessman & orig): position(orig.position), board(orig.board), white(orig.white) {

}

Chessman &Chessman::operator=(const Chessman & orig) {
    position = orig.position;
    board = orig.board;
    white = orig.white;
    return *this;
}*/


/*
Pawn::Pawn(const Position &position_, bool white_, Board & board_):
           Chessman(position_, white_, board_), first_move(true) {}

bool Pawn::checkMoveAndMiddleChessmen(const Position &initial,
                                      const Position & final,
                                      std::vector<Chessman *> *
                                              chessmen_in_path) {
    std::vector<Position> path;
    path.reserve(MAX_PATH_LENGTH);
    if (initial.x() != final.x())
        return false;
    if (initial.y() + 2 == final.y() && first_move) {
        path.push_back(Position(initial.y() + 2, initial.x()));
        path.push_back(Position(initial.y() + 1, initial.x()));
    }
    if (initial.y() + 1 == final.y())
        path.push_back(Position(initial.y() + 1, initial.x()));
    if (!path.empty() && checkFreePath(path, chessmen_in_path)) {
        return true;
    }
    return false;
}

void Pawn::move(const Position &initial, const Position &final) {
    Chessman::move(initial, final);
    first_move = false;
}

Knight::Knight(const Position &position, bool white_, Board &board_):
             Chessman(position, white_, board_) {}


bool Knight::checkMoveAndMiddleChessmen(const Position &initial,
                                        const Position &final,
                                        std::vector<Chessman *> *
                                          chessmen_in_path) {
    // TODO ver si esta bien esto con el puntero.
    std::vector<Chessman *>vector;
    vector.reserve(1);

    if (initial.x() - 2 == final.x() && initial.y() - 1 == final.y())
        vector.push_back(
                board.getChessmanAt(Position(initial.x() - 2, initial.y() - 1)));
    else if (initial.x() - 2 == final.x() && initial.y() + 1 == final.y())
        vector.push_back(
                board.getChessmanAt(Position(initial.x() - 2, initial.y() + 1)));
    else if (initial.x() - 1 == final.x() && initial.y() - 2 == final.y())
        vector.push_back(
                board.getChessmanAt(Position(initial.x() - 1, initial.y() - 2)));
    else if (initial.x() - 1 == final.x() && initial.y() + 2 == final.y())
        vector.push_back(
                board.getChessmanAt(Position(initial.x() - 1, initial.y() + 2)));
    else if (initial.x() + 1 == final.x() && initial.y() - 2 == final.y())
        vector.push_back(
                board.getChessmanAt(Position(initial.x() + 1, initial.y() - 2)));
    else if (initial.x() + 1 == final.x() && initial.y() + 2 == final.y())
        vector.push_back(
                board.getChessmanAt(Position(initial.x() + 1, initial.y() + 2)));
    else if (initial.x() + 2 == final.x() && initial.y() - 1 == final.y())
        vector.push_back(
                board.getChessmanAt(Position(initial.x() + 2, initial.y() - 1)));
    else if (initial.x() + 2 == final.x() && initial.y() + 1 == final.y())
        vector.push_back(
                board.getChessmanAt(Position(initial.x() + 2, initial.y() + 1)));
    else
        return false;
    if (chessmen_in_path)
        *chessmen_in_path = std::move(vector);
    return true;
}
*/

