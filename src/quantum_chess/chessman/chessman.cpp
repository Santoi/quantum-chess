#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include "chessman.h"
#include "../chess_exception.h"

// TODO ver que pasa si queres traspasar una pieza cuantica que es la misma,
// deberia romper!!.

// TODO ver entrelazamiento cuando hay un 100 de que este en el medio


// TODO, ver excepciones, algunas nunca se llega, ver si convendria
// en ver de llamar a todo lo mismo que chequear.

Chessman::Chessman(const Position & position_, bool white_, Board & board_):
        positions(1, QuantumPosition(position_, 1)),
        board(board_), white(white_) {}


void Chessman::move(const Position & initial, const Position & final) {
    // TODO ver como mejorar lo de checkCanMoveOrFail y eso. (estoy repitiendo
    //  lo de buscar).
    const Chessman * chessman_in_path = nullptr;
    std::vector<Position> path;
    std::vector<Chessman *> chessmen_in_path;
    checkCanMoveOrFail(initial, final);

    calculatePath(initial, final, path);
    getMiddlePathChessman(path, chessman_in_path);
    
    if (Chessman * final_chessman = board.getChessmanAt(final)) {
        if (final_chessman->isQuantum()) {
            measure(initial);
            final_chessman->measure(final);
            if (getPosition() != initial)
                return;
            /* Si la posicion real del final era esa, se mide termina aqui.
             * si, no, se completa el movimiento. */
            if (final_chessman->getPosition() == final && final_chessman->white == white)
                return;
            else if (final_chessman->getPosition() == final && final_chessman->white != white)
                board.removeChessmanOf(final);
        }
        else if (final_chessman->white != white) {
            measure(initial);
            final_chessman->measure(final);
            if (getPosition() != initial)
                return;
        }
        else
            throw ChessException("La pieza final no es cuantica ni se"
                                 "puede comer.");
        board.removeChessmanOf(final);
    }
    auto it = std::find(positions.begin(), positions.end(),
                        initial);
    double prob = it->getProb();
    it = positions.erase(it);
    positions.insert(it, QuantumPosition(final, prob));

    board.addChessmanOfIn(initial, final);
    // TODO LOGICA ENTRELAZADO.
}

void Chessman::split(const Position &initial, const Position &position1,
                     const Position &position2) {
    if (position1 == position2)
        throw ChessException("no se puede hacer un split a la misma"
                             "posicion");
    // TODO no se puede hacer split a casillero lleno ni entrelazar.

    std::vector<Position> path;
    const Chessman * chessman_in_path_1 = nullptr, * chessman_in_path_2 = nullptr;

    // TODO reunir todo en una sola? Creo que no por chessmen in path
    checkCanMoveOrFail(initial, position1);
    checkCanMoveOrFail(initial, position2);

    calculatePath(initial, position1, path);
    getMiddlePathChessman(path, chessman_in_path_1);

    calculatePath(initial, position2, path);
    getMiddlePathChessman(path, chessman_in_path_2);

    if (board.getChessmanAt(position1) || board.getChessmanAt(position2))
        throw ChessException("no se puede hacer split a un casillero"
                             "lleno");

    if (chessman_in_path_1 || chessman_in_path_2)
        throw ChessException("no se puede hacer split y enlazar");

    // Se sortea aunque no sea el real.
    Position new_real, new_fake;
    bool coin = board.flipACoin();
    new_real = coin ? position1 : position2;
    new_fake = !coin ? position1 : position2;

    /* Se obtiene la posicion inicial y se borra, luego se inserta en su
     * lugar primero la real y luego la fake (podrian no serlo), de esta manera
     * si la inicial era la real, la nueva real se ubica primera. */
    auto it = std::find(positions.begin(), positions.end(), initial);
    double prob = it->getProb();
    it = positions.erase(it);
    it = positions.insert(it, QuantumPosition(new_real, prob / 2));
    positions.insert(it + 1, QuantumPosition(new_fake, prob/2));

    // TODO LOGICA ENTRELAZADO.
    board.addChessmanOfIn(initial, position1, position2);
}

void Chessman::merge(const Position &initial1, const Position &initial2,
                     const Position &final) {
    // TODO no se puede hacer split a casillero lleno ni entrelazar.
    if (initial1 == initial2)
        throw ChessException("no se puede hacer merge desde la misma"
                             "posicion");

    std::vector<Chessman *> chessmen_in_path_1, chessmen_in_path_2;

    const Chessman * chessman_in_path_1 = nullptr, * chessman_in_path_2 = nullptr;
    /* Se chequea, si la pieza que esta en la posicion final es la misma, se quita.
     * Lo mismo para los iniciales, esto se hace ya que no se molestan, es decir,
     * si tienen que pasar por encima de la otra, no pasa nada. */
    if (board.getChessmanAt(final) == this)
        board.removeChessmanOf(final);
    else if (board.getChessmanAt(initial1) == this)
        board.removeChessmanOf(initial1);
    else if (board.getChessmanAt(initial2) == this)
        board.removeChessmanOf(initial2);


    // En este caso, si se puede mover al mismo lugar donde esta.
    std::vector<Position> path;
    if (initial1 != final) {
        checkCanMoveOrFail(initial1, final);
        calculatePath(initial1, final, path);
        getMiddlePathChessman(path, chessman_in_path_1);
    }
    if (initial2 != final) {
        checkCanMoveOrFail(initial2, final);
        calculatePath(initial2, final, path);
        getMiddlePathChessman(path, chessman_in_path_1);
    }

    if (chessman_in_path_1 || chessman_in_path_2)
        throw ChessException("no se puede hacer merge y enlazar");

    /* Se chequea si el iterador 1 es el real, es decir el primero del vector
     * posicion, si no lo es, se guarda en el 2, sea o no el inicial, se
     * colocara en la posicion correcta. */
    auto it1 = std::find(positions.begin(), positions.end(), initial1);
    auto it2 = std::find(positions.begin(), positions.end(), initial2);
    double prob = it1->getProb() + it2->getProb();
    if (it1 == positions.begin()) {
        positions.erase(it2); // Se borra primero el 2 para no modificar el 1.
        positions.erase(it1);
        positions.insert(positions.begin(), QuantumPosition(final, prob));
    } else if (it2 == positions.begin()) {
        positions.erase(it1); // Se borra primero el 1 para no modificar el 2.
        positions.erase(it2);
        positions.insert(positions.begin(), QuantumPosition(final, prob));
    } else {
        // Se chequea el orden para saber cual borrar primero.
        auto it_first = (it1 < it2) ? it1 : it2;
        auto it_last = !(it1 < it2) ? it1 : it2;
        positions.erase(it_last);
        auto it = positions.erase(it_first);
        positions.insert(it, QuantumPosition(final, prob));
    }
    // Se borran todas (si estan) y luego se guarda  en la final
    board.removeChessmanOf(initial1);
    board.removeChessmanOf(initial2);
    board.removeChessmanOf(final);
    board.addChessmanIn(final, this);
    // TODO LOGICA ENTRELAZADO.
}

void Chessman::measure(const Position & position) {
    if (!isQuantum())
        return;
    auto it = std::find(positions.begin(), positions.end(), position);
    // TODO falta logica entrelazado.
    /* Si es el primero, se borra entero el vector y se deja solo la posicion
     * con probabilidad 1. */
    if (it == positions.begin()) {
        it->setProb(1);
        for (++it; it != positions.end(); ++it) {
            board.removeChessmanOf(Position(*it));
        }
        positions.erase(positions.begin() + 1, positions.end());
    } else if (it != positions.end()) {
        double prob = it->getProb();
        positions.erase(it);
        board.removeChessmanOf(position);
        for (it = positions.begin(); it != positions.end(); ++it) {
            it->setProb(it->getProb() / (1 - prob));
        }
    } else {
        throw ChessException("la pieza no esta alli");
    }
}

void Chessman::checkCanMoveOrFail(const Position & initial,
                                  const Position & final)
                                  const {
    std::vector<Position> path;
    std::vector<Position> posible_moves;
    if (std::find(positions.begin(), positions.end(),
                  initial) == positions.end())
        throw ChessException("la ficha no está en esa posicion");
        
    calculatePosibleMoves(initial, posible_moves);
    if (std::find(posible_moves.begin(),
                  posible_moves.end(), final) == posible_moves.end())
        throw ChessException("la pieza no se puede mover alli");
}

bool Chessman::checkFreePath(const std::vector<Position> & path) const {
    const Chessman * chessman = nullptr;
    bool middle_path_free = getMiddlePathChessman(path, chessman);
    bool final_free = true;
    if (auto chessman = board.getChessmanAt(path.back())) {
        if (chessman->white == white && !chessman->isQuantum() && !isQuantum())
            final_free = false;
    }
    return middle_path_free && final_free;
}

bool Chessman::getMiddlePathChessman(const std::vector<Position> & path,
                                     const Chessman * & chessman)
                                     const {
    bool can_move = true;
    // Se revisa el camino.
    for (size_t i = 0; i < path.size() - 1; i++) {
        if (auto chessman_ = board.getChessmanAt(path[i])) {
            if (!can_move || !chessman_->isQuantum())
                return false;
            chessman = chessman_;
            can_move = false;
        }
    }
    return true;
}

bool Chessman::isQuantum() const {
	return positions.size() > 1;
}

bool Chessman::isWhite() const {
    return white;
}

const QuantumPosition & Chessman::getPosition() const {
    return positions[0];
}

const std::vector<QuantumPosition> & Chessman::getAllPositions() const {
	// TODO modificar cuando se haga cuantica.
    return positions;
}

void Chessman::calculatePath(const Position & initial,
                             const Position & final,
                             std::vector<Position> & path) const {
    if (initial == final)
        ChessException("no se puede calcular el "
                              "camino entre posiciones iguales");
    if (initial.y() == final.y())
        calculateFilePath(initial, final, path);
    else if (initial.x() == final.x())
        calculateRowPath(initial, final, path);
    else if (abs((initial.x() - final.x()) / (initial.y() - final.y())) == 1)
        calculateDiagonalPath(initial, final, path);
    else
        throw ChessException("ese movimiento es imposible");
}

void Chessman::calculateFilePath(const Position & initial,
                                 const Position & final,
                                 std::vector<Position> & path) const {
    const Position & bottom = (initial.x() < final.x()) ? initial : final;
    const Position & top = (initial.x() < final.x()) ? final : initial;
    path = std::vector<Position> ();
    path.reserve(7);

    for (uint8_t i = bottom.x() + 1; i < top.x(); i++)
        path.push_back(Position(i, initial.y()));
    path.push_back(final);
}

void Chessman::calculateRowPath(const Position & initial,
                                const Position & final,
                                std::vector<Position> & path) const {
    const Position & bottom = (initial.y() < final.y()) ? initial : final;
    const Position & top = (initial.y() < final.y()) ? final : initial;
    path = std::vector<Position> ();
    path.reserve(7);

    for (uint8_t i = bottom.y() + 1; i < top.y(); i++)
        path.push_back(Position(initial.x(), i));
    path.push_back(final);
}

void Chessman::calculateDiagonalPath(const Position & initial,
                                     const Position & final,
                                     std::vector<Position> & path) const {
    int8_t sum_x = (initial.x() < final.x()) ? 1 : -1;
    int8_t sum_y = (initial.y() < final.y()) ? 1 : -1;
    path = std::vector<Position> ();
    path.reserve(6);

    for (int8_t i = initial.x() + sum_x, j = initial.y() + sum_y;
         i * sum_x < final.x() * sum_x && j * sum_y < final.y() * sum_y;
         i += sum_x, j += sum_y)
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

double Chessman::getProbability(Position position_) {
    auto it = std::find(positions.begin(),
                        positions.end(), position_);
    if (it != positions.end())
        return it->getProb();
    throw std::invalid_argument("la pieza no esta alli");
}

