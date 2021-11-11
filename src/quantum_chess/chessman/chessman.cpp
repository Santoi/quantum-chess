#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include "chessman.h"
#include "../chess_exception.h"

// TODO HACER LO DE CHEQUEO PARA SPLIT Y MERGE (CUANDO Pido casilleros). HACERLO PARA PAWN ESPECIAL.

// TODO split pawn, move pawn y etc.

 //TODO smart pointers.

// TODO Peon no splitea ni enlaza.

// TODO unir move y split?

// TODO agregar otras validaciones al momento de mostrar posiciones (por ejemplo cuando no te podes entanglear con una que ya estas).

Chessman::Chessman(const Position & position_, bool white_, Board & board_):
        positions(1, QuantumPosition(position_, 1, this)),
        board(board_), white(white_), measured(false) {}


void Chessman::move(const Position & initial, const Position & final) {
    // TODO ver como mejorar lo de checkCanMoveOrFail y eso. (estoy repitiendo
    //  lo de buscar).
    std::pair<Position, Chessman *> chessman_in_path;

    std::vector<Position> path;
    checkCanMoveOrFail(initial, final);

    calculatePath(initial, final, path);
    getMiddlePathChessman(path, chessman_in_path);

    if (this == board.getChessmanAt(final))
        throw ChessException("la pieza no se puede mover al lugar donde hay un fragmento de ella.");

    // TODO verlo si lo puedo hacer.
    Chessman * final_chessman = board.getChessmanAt(final);

    if (final_chessman && chessman_in_path.second)
        throw ChessException("no se puede hacer measure y entrelazado+"
                             " a la vez");
    if (isAlreadyEntangled(chessman_in_path.second))
        throw ChessException("no se puede entrelazar dos veces la misma pieza");

    // Si el inicial es cuantico y hay pieza al final, o hay pieza al final y es cuantica.
    if ((this->isQuantum() && final_chessman) || (final_chessman && final_chessman->isQuantum())) {
        this->measure(initial);
        final_chessman->measure(final);
        if (positions.front() != initial || (final_chessman && final_chessman->getPosition() == final && final_chessman->white == white))
            return;
    }
    // A partir de aqui, measure ya esta resuelto.
    if (final_chessman)
        board.removeChessmanOf(final);

    if (chessman_in_path.second) {
        if (getProbability(initial) / 2 < PRECISION_PROB)
            throw ChessException("no se puede volver a dividir la pieza.");
        double entangled_prob = chessman_in_path.second->getProbability(chessman_in_path.first);
        double initial_prob = getProbability(initial);
        double new_initial_prob = entangled_prob * initial_prob;
        double new_final_prob = initial_prob * (1 - entangled_prob);
        auto qpos_initial = std::find(positions.begin(), positions.end(), initial);
        auto insert = qpos_initial;
        insert++;

        // Solo lo meto al principio si es la real, es decir, la inicial era la real,
        // y si la que estaba en el camino no lo era.
        if(qpos_initial == positions.begin() && chessman_in_path.second->getPosition() != chessman_in_path.first)
            insert = positions.begin();

        std::list<QuantumPosition *> list = qpos_initial->getEntangled();
        qpos_initial->setProb(new_initial_prob);
        insert = positions.insert(insert, QuantumPosition(final, new_final_prob, list, this));
        qpos_initial->addToEntangled(*insert);

        board.addChessmanIn(final, this);

        entangle(final, *(chessman_in_path.second), chessman_in_path.first);
    }
    else {
        auto it = std::find(positions.begin(), positions.end(),
                            initial);
        // TODO puedo pasar lista por movimiento y copiarla si hace falta.
        it->setPosition(final);

        board.addChessmanOfIn(initial, final);
    }

    // TODO LOGICA ENTRELAZADO.
    measured = false;

}

void Chessman::split(const Position &initial, const Position &position1,
                     const Position &position2) {
    if (position1 == position2)
        throw ChessException("no se puede hacer un split a la misma"
                             "posicion");
    // TODO no se puede hacer split a casillero lleno ni entrelazar.

    if (getProbability(initial) / 2 < PRECISION_PROB)
        throw ChessException("no se puede volver a dividir la pieza.");

    std::vector<Position> path;
    std::pair<Position, Chessman *> chessman_in_path_1, chessman_in_path_2;

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

    if (chessman_in_path_1.second || chessman_in_path_2.second)
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
    std::list<QuantumPosition *> list = it->getEntangled();
    it->setProb(prob / 2);
    it->setPosition(Position(new_real));
    auto it2 = positions.insert(++it, QuantumPosition(new_fake, prob/2, list, this));
    it = std::find(positions.begin(), positions.end(), new_real);
    (it)->addToEntangled(*it2);

    // TODO LOGICA ENTRELAZADO.
    board.addChessmanOfIn(initial, position1, position2);
    measured = false;
}

void Chessman::merge(const Position &initial1, const Position &initial2,
                     const Position &final) {
    // TODO no se puede hacer split a casillero lleno ni entrelazar.
    if (initial1 == initial2)
        throw ChessException("no se puede hacer merge desde la misma"
                             "posicion");

    std::pair<Position, Chessman *> chessman_in_path_1, chessman_in_path_2;
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

    if (chessman_in_path_1.second || chessman_in_path_2.second)
        throw ChessException("no se puede hacer merge y enlazar");

    /* Se chequea si el iterador 1 es el real, es decir el primero del vector
     * posicion, si no lo es, se guarda en el 2, sea o no el inicial, se
     * colocara en la posicion correcta. */
    auto it1 = std::find(positions.begin(), positions.end(), initial1);
    auto it2 = std::find(positions.begin(), positions.end(), initial2);
    double prob = it1->getProb() + it2->getProb();
    ifEntangledPositionsNotAppearsInBothUnentangle(&(*it1), &(*it2));
    if (it1 == positions.begin()) {
        it2->deleteMeFromEntangled();
        positions.erase(it2); // Se borra primero el 2 para no modificar el 1.
        it1->setProb(prob);
        it1->setPosition(final);
    } else {
        it1->deleteMeFromEntangled();
        positions.erase(it1); // Se borra primero el 1 para no modificar el 2.
        it2->setProb(prob);
        it2->setPosition(final);
    }
    // TODO VER QUE HACER CON MERGE CON ENTANGLEMENT
    // Se borran todas (si estan) y luego se guarda  en la final
    board.removeChessmanOf(initial1);
    board.removeChessmanOf(initial2);
    board.removeChessmanOf(final);
    board.addChessmanIn(final, this);
    // TODO LOGICA ENTRELAZADO.
    measured = false;
}

void Chessman::measure(const Position & position) {
    if (!isQuantum())
        return;
    measured=true;
    auto it = std::find(positions.begin(), positions.end(), position);
    // TODO falta logica entrelazado.
    /* Si es el primero, se borra entero el vector y se deja solo la posicion
     * con probabilidad 1. */
    if (it == positions.end())
        throw ChessException("la pieza no esta alli");
    if (it == positions.begin()) {
        it->setProb(1);
        for (; it != positions.end(); ++it) {
            it->deleteMeFromEntangled();
            measureOthers(*it);
            if(it != positions.begin())
                board.removeChessmanOf(Position(*it));
            it->unentangle();
        }
        positions.erase(++positions.begin(), positions.end());
        positions.begin()->unentangle();
    } else if (it != positions.end()) {
        it->deleteMeFromEntangled();
        measureOthers(*it);
        it->unentangle();
        double prob = it->getProb();
        positions.erase(it);
        board.removeChessmanOf(position);
        for (it = positions.begin(); it != positions.end(); ++it) {
            it->setProb(it->getProb() / (1 - prob));
        }
    }

}

void Chessman::measureOthers(QuantumPosition & quantum_position) {
    for (auto & other: quantum_position.getEntangled()) {
        if (!entangledPositionAppearsMoreThanOnce(other)) {
            quantum_position.deleteMeFromEntangled(other);
            other->measure();
        }
    }
    auto list = searchAppearsInAllLessIn(quantum_position);
    for (auto & qpos: list) {
        // TODO VER ACA
        for (auto iterator = positions.begin(); iterator != positions.end(); ++iterator) {
            iterator->deleteMeFromEntangled(qpos);
        }
        qpos->measure();
    }
}

// solo se llama si la que llama no es la primera.
std::list<QuantumPosition *> Chessman::searchAppearsInAllLessIn(QuantumPosition & quantumPosition) {
    std::list<QuantumPosition*> candidates;
    auto it_1 = positions.begin();
    if (&(*it_1) == &quantumPosition)
        it_1++;
    if (it_1 == positions.end())
        return candidates;
    candidates = it_1->getEntangled();
    for (; it_1 != positions.end(); ++it_1) {
        if (&(*it_1) == &quantumPosition)
            continue;
        for (auto it_2 = candidates.begin(); it_2 != candidates.end(); ){
            bool founded = false;
            for (auto it_3 = it_1->getEntangled().begin(); it_3 != it_1->getEntangled().end(); ++it_3) {
                if (*it_3 == *it_2) {
                    founded = true;
                    break;
                }
            }
            if (!founded) {
                it_2 = candidates.erase(it_2);
            }
            else
                ++it_2;
        }
    }
    return candidates;
}

bool Chessman::entangledPositionAppearsMoreThanOnce(QuantumPosition * position) {
    size_t counter = 0;
    for (auto & position_: positions) {
        for (auto & entangled_position: position_.getEntangled())
            // TODO revisar
            if (entangled_position == position) {
                if (++counter > 1)
                    return true;
            }
    }
    return false;
}

// Si cuando se hace el merge, se tiene que ambos tienen enlazado algo, esto no se desenlaza, sino
// si.
void Chessman::ifEntangledPositionsNotAppearsInBothUnentangle(QuantumPosition * position1, QuantumPosition * position2) {
    auto & entangled1 = position1->getEntangled(), & entangled2 = position2->getEntangled();
    for (auto it1= entangled1.begin(); it1 != entangled1.end(); ) {
        auto search_it = std::find(entangled2.begin(), entangled1.begin(),
                                   *it1);
        if (search_it == entangled2.end()) {
            position1->deleteMeFromEntangled(*it1);
            it1 = entangled1.erase(it1);
        }
        else {
            ++it1;
        }
    }
    for (auto it2= entangled2.begin(); it2 != entangled2.end(); ) {
        auto search_it = std::find(entangled1.begin(), entangled1.begin(),
                                   *it2);
        if (search_it == entangled2.end()) {
            position2->deleteMeFromEntangled(*it2);
            it2 = entangled1.erase(it2);
        }
        else {
            ++it2;
        }
    }
}

// TODO  void measure others.

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
    std::pair<Position, Chessman *> chessman_in_path;
    bool middle_path_free = getMiddlePathChessman(path, chessman_in_path);
    bool final_free = true;
    if (auto chessman = board.getChessmanAt(path.back())) {
        if (chessman->white == white && !chessman->isQuantum())
            final_free = false;

    }
    return middle_path_free && final_free;
}

bool Chessman::getMiddlePathChessman(const std::vector<Position> & path,
                                     std::pair<Position, Chessman *> & chessman)
                                     const {
    bool can_move = true;
    // Se revisa el camino.
    for (size_t i = 0; i < path.size() - 1; i++) {
        if (auto chessman_ = board.getChessmanAt(path[i])) {
            if (!can_move || !chessman_->isQuantum() || chessman_ == this)
                return false;
            chessman.first = path[i];
            chessman.second = chessman_;
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
    return positions.front();
}

const QuantumPosition & Chessman::getPosition(size_t index) const {
    size_t i = 0;
    if (index >= positions.size())
        throw std::invalid_argument("no tiene ese indice");
    for (auto & position: positions) {
        if (i == index)
            return position;
        i++;
    }
    // TODO ver aca
    return positions.front();
}

size_t Chessman::positionsSize() const {
    return positions.size();
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

void Chessman::entangle(const Position &position, Chessman & other, const Position &other_position) {
    auto it_this = std::find(positions.begin(), positions.end(), position);
    auto it_other = std::find(other.positions.begin(), other.positions.end(), other_position);
    if (it_this == positions.end() || it_other == other.positions.end())
        throw ChessException("la pieza no esta alli");
    it_this->entangle(*it_other);
    it_other->entangle(*it_this);
}

// solo para debug, en el medio se va a tener que mover la pieza.
void Chessman::resetMeasured() {
    measured = false;
}


std::list<QuantumPosition> & Chessman::getAllPositions() {
    return positions;
};

bool Chessman::isAlreadyEntangled(Chessman * chessman) {
    for (auto it = positions.begin(); it != positions.end(); ++it) {
        auto entangled = it->getEntangled();
        for (auto & qp: entangled) {
            if (chessman == qp->getChessman())
                return true;
        }
    }
    return false;
}


