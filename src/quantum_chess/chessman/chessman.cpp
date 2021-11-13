#include <stdexcept>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <iostream>
#include "chessman.h"
#include "../chess_exception.h"

// TODO ver privadas y publicas

// TODO revisar los find.

 //TODO smart pointers.

 // TODO Hacer measure privada, cambiando los test o ver que puedo hacer con test
 // para que la vean

 // TODO testear posiblemerge y splits (con un caso al menos).

 // TODO HACER POSIBLE MOVES LIST!!!

Chessman::Chessman(const Position & position_, bool white_, Board & board_):
        positions(1, QuantumPosition(position_, 1, this)),
        board(board_), white(white_) {}


void Chessman::move(const Position & initial, const Position & final) {
    // Check if can be moved.
    std::vector<Position> path;
    std::vector<Position> posible_moves;
    calculateMoves(initial, posible_moves);
    auto final_it = std::find(posible_moves.begin(), posible_moves.end(),
                              final);
    if (final_it == posible_moves.end())
        throw ChessException("that chessman cant do that move");
    moveValidationExceptionThrower(checkIsAValidMove(initial, final));

    // Search path and get middle path chessman.
    std::pair<Position, Chessman *> chessman_in_path;
    calculatePath(initial, final, path);
    getMiddlePathChessman(path, chessman_in_path);

    Chessman * final_chessman = board.getChessmanAt(final);

    /* If initial is quantic and there is a chessman at the end, or there is a
     * chessman at the end and this is quantic, then measure both chessmen. */
    if ((this->isQuantum() && final_chessman) ||
        (final_chessman && final_chessman->isQuantum())) {
        this->measure(initial);
        final_chessman->measure(final);
        if (positions.front() != initial ||
            (final_chessman->getPosition() == final
             && final_chessman->white == white))
            return;
    }
    // Measure solved from here.
    // If there is final chessman, then is removed of the board.
    if (final_chessman)
        board.removeChessmanOf(final);


    // TODO hacer lo de mezclar con una funcion split.
    // If there is a chessman in path then entangle.
    if (chessman_in_path.second) {
        entangle(initial, final, *chessman_in_path.second, chessman_in_path.first);
        board.addChessmanIn(final, this);
    } else {
        auto initial_qp_it = std::find(positions.begin(),
                                       positions.end(), initial);
        initial_qp_it->setPosition(final);
        board.addChessmanOfIn(initial, final);
    }
}

void Chessman::split(const Position &initial, const Position &final1,
                     const Position &final2) {
    std::vector<Position> posible_moves;
    calculateMoves(initial, posible_moves);
    auto final_it = std::find(posible_moves.begin(), posible_moves.end(),
                              final1);
    if (final_it == posible_moves.end())
        throw ChessException("that chessman cant do that split");
    moveValidationExceptionThrower(checkIsAValidSplit(initial, final1));
    final_it = std::find(posible_moves.begin(), posible_moves.end(),
                              final1);
    if (final_it == posible_moves.end())
        throw ChessException("that chessman cant do that split");
    moveValidationExceptionThrower(checkIsAValidSplit(initial, final2));

    if (final1 == final2)
        throw ChessException("cannot split into the same square");

    // Even if not real, the coin is flipped.
    Position new_real, new_fake;
    bool coin = board.flipACoin();
    new_real = coin ? final1 : final2;
    new_fake = !coin ? final1 : final2;

    // TODO esto podria meterse en un metodo y mandarse igual que en move.
    auto initial_qp_it = std::find(positions.begin(), positions.end(), initial);
    double old_prob = initial_qp_it->getProb();
    // Entangled list is copied and then moved.
    std::list<QuantumPosition *> entangled_list = initial_qp_it->getEntangled();
    initial_qp_it->setProb(old_prob / 2);
    initial_qp_it->setPosition(Position(new_real));
    auto new_qp_it = positions.insert(++initial_qp_it,
                                      QuantumPosition(new_fake,
                                                      old_prob / 2,
                                                      std::move(entangled_list),
                                                      this));
    new_qp_it->addMeToEntangled();

    board.addChessmanOfIn(initial, final1, final2);
}

void Chessman::merge(const Position &initial1, const Position &initial2,
                     const Position &final) {
    std::vector<Position> posible_moves;
    calculateMoves(initial1, posible_moves);
    auto final_it = std::find(posible_moves.begin(), posible_moves.end(),
                              final);
    if (final_it == posible_moves.end())
        throw ChessException("that chessman cant do that merge");
    moveValidationExceptionThrower(checkIsAValidMerge(initial1, final));

    final_it = std::find(posible_moves.begin(), posible_moves.end(),
                         final);
    if (final_it == posible_moves.end())
        throw ChessException("that chessman cant do that merge");
    moveValidationExceptionThrower(checkIsAValidMerge(initial2, final));

    if (initial1 == initial2)
        throw ChessException("cannot merge from same square");

    // Remove chessman of final places if there.
    if (board.getChessmanAt(final) == this)
        board.removeChessmanOf(final);

    /* If iterator 1 is real, then merge is saved in first position, if no
     * is saved in position of iterator 2 no matter what (if it 2 is real,
     * then is correct. */
    auto it1 = std::find(positions.begin(), positions.end(), initial1);
    auto it2 = std::find(positions.begin(), positions.end(), initial2);
    double prob = it1->getProb() + it2->getProb();

    it1->ifNotInOtherUnentangle(*it2);
    it2->ifNotInOtherUnentangle(*it1);

    if (it1 == positions.begin()) {
        it2->deleteMeFromEntangled();
        positions.erase(it2);
        it1->setProb(prob);
        it1->setPosition(final);
    } else {
        it1->deleteMeFromEntangled();
        positions.erase(it1);
        it2->setProb(prob);
        it2->setPosition(final);
    }

    board.addChessmanIn(final, this);
}

void Chessman::measure(const Position &position) {
    // If is not Quantum, then go back.
    if (!isQuantum())
        return;
    auto position_qp_it = std::find(positions.begin(),
                                    positions.end(), position);

    if (position_qp_it == positions.end())
        throw ChessException("la pieza no esta alli");


    // If position is the first one, then leave as only real.
    if (position_qp_it == positions.begin()) {
        position_qp_it->setProb(1);
        // Measure the others, entangled with this and the other and remove.
        for (; position_qp_it != positions.end(); ++position_qp_it) {
            position_qp_it->deleteMeFromEntangled();
            measureOthers(*position_qp_it);
            if (position_qp_it != positions.begin())
                board.removeChessmanOf(Position(*position_qp_it));
            position_qp_it->unentangle();
        }
        positions.erase(++positions.begin(), positions.end());

    } else if (position_qp_it != positions.end()) {
        /* If is not real, then delete only it, un entangling
         * and measuring other. */
        position_qp_it->deleteMeFromEntangled();
        measureOthers(*position_qp_it);
        position_qp_it->unentangle();
        double prob = position_qp_it->getProb();
        positions.erase(position_qp_it);
        board.removeChessmanOf(position);
        // Probability is propagated in the other positions.
        for (position_qp_it = positions.begin();
             position_qp_it != positions.end(); ++position_qp_it) {
            position_qp_it->setProb(position_qp_it->getProb() / (1 - prob));
        }
    }
}

void Chessman::measureOthers(QuantumPosition & quantum_position) {
    // If entangled appears only in this position, then measure.
    for (auto & qp_to_measure: quantum_position.getEntangled()) {
        if (!entangledPositionAppearsMoreThanOnce(qp_to_measure)) {
            quantum_position.deleteMeFromEntangled(*qp_to_measure);
            qp_to_measure->measure();
        }
    }
    /* If other entangled appears in all positions but not in this one, then it
     * means that this is the position that was holding the other from
     * measuring.*/
    auto to_measure = searchEntangledWithAllPositionsExceptWith(
            quantum_position);
    for (auto & qp_to_measure: to_measure) {
        for (auto iterator = positions.begin(); iterator != positions.end();
             ++iterator) {
            iterator->deleteMeFromEntangled(*qp_to_measure);
        }
        qp_to_measure->measure();
    }
}

std::list<QuantumPosition *>
Chessman::searchEntangledWithAllPositionsExceptWith(
                const QuantumPosition & filtered_qp) {
    std::list<QuantumPosition*> candidates;
    auto positions_it = positions.begin();
    // If first position is the filtered one, then it advance 1.
    if (*positions_it == filtered_qp)
        positions_it++;
    // If is the end, then return empty list.
    if (positions_it == positions.end())
        return candidates;
    // Candidates initialize as the entangled of the first one.
    candidates = positions_it->getEntangled();
    for (; positions_it != positions.end(); ++positions_it) {
        if (*positions_it == filtered_qp)
            continue;
        for (auto candidates_it = candidates.begin();
             candidates_it != candidates.end(); ){
            // If not entangled, then delete from candidates.
            if (!positions_it->isEntangled(**candidates_it))
                candidates_it = candidates.erase(candidates_it);
            else
                ++candidates_it;
        }
    }
    return candidates;
}

bool
Chessman::entangledPositionAppearsMoreThanOnce(QuantumPosition * position) {
    size_t counter = 0;
    for (auto & position_: positions) {
        for (auto & entangled_position: position_.getEntangled())
            if (entangled_position == position) {
                if (++counter > 1)
                    return true;
            }
    }
    return false;
}


// Validates if move can be done (regardless the chessman).
Chessman::MoveValidationStatus
Chessman::checkIsAValidMove(const Position & initial, const Position & final) {
    checkIsInBoardOrFail(initial);

    if (std::find(positions.begin(), positions.end(),
                  initial) == positions.end())
        return CHESSMAN_NOT_IN_POSITION;

    if (initial == final)
        return MOVING_TO_SAME_SQUARE;

    if (this == board.getChessmanAt(final))
        return MOVING_TO_SQUARE_WITH_SAME_PIECE;
    Chessman * final_chessman = board.getChessmanAt(final);

    std::vector<Position> path;
    std::pair<Position, Chessman *> chessman_in_path;
    calculatePath(initial, final, path);

    if (!checkFreePath(path, chessman_in_path))
        return NON_FREE_PATH;

    getMiddlePathChessman(path, chessman_in_path);

    if (final_chessman && chessman_in_path.second)
        return MEASURING_AND_ENTANGLING;

    if (chessmanIsAlreadyEntangled(chessman_in_path.second))
        return ENTANGLING_SAME_PIECE_TWO_TIMES;

    return OK;
}

Chessman::MoveValidationStatus
Chessman::checkIsAValidSplit(const Position &initial, const Position &final) {
    checkIsInBoardOrFail(initial);

    if (std::find(positions.begin(), positions.end(),
                  initial) == positions.end())
        return CHESSMAN_NOT_IN_POSITION;

    if (initial == final)
        return MOVING_TO_SAME_SQUARE;

    std::vector<Position> path;
    std::pair<Position, Chessman *> chessman_in_path;

    calculatePath(initial, final, path);
    if (!checkFreePath(path, chessman_in_path))
        return NON_FREE_PATH;

    if (board.getChessmanAt(final))
        return SPLIT_TO_OCCUPIED_SQUARE;

    if (chessman_in_path.second)
        return SPLITTING_AND_ENTANGLING;

    if (getProbability(initial) / 2 < PRECISION_PROB)
        return SPLIT_LIMIT_REACHED;

    return OK;
}

Chessman::MoveValidationStatus
Chessman::checkIsAValidMerge(const Position &initial1, const Position &final) {
    checkIsInBoardOrFail(initial1);

    if (std::find(positions.begin(), positions.end(),
                  initial1) == positions.end())
        return CHESSMAN_NOT_IN_POSITION;

    std::vector<Position> path;
    std::pair<Position, Chessman *> chessman_in_path;

    if (initial1 != final) {
        calculatePath(initial1, final, path);
        if (!checkFreePath(path, chessman_in_path))
            return NON_FREE_PATH;
    }

    if (chessman_in_path.second)
        return MERGING_AND_ENTANGLING;

    return OK;
}

// TODO posible moves to list
void Chessman::calculatePosibleMoves(const Position &initial,
                                     std::vector<Position> &posible_moves) {
    calculateMoves(initial, posible_moves);

    for (auto it = posible_moves.begin(); it != posible_moves.end(); ){
        if (checkIsAValidMove(initial, *it)) {
            it = posible_moves.erase(it);
            continue;
        }
        ++it;
    }
}

void Chessman::calculatePosibleSplits(const Position & initial,
                                      std::vector<Position> &posible_moves) {
    calculateMoves(initial, posible_moves);

    for (auto it = posible_moves.begin(); it != posible_moves.end(); ){
        if (checkIsAValidSplit(initial, *it)) {
            it = posible_moves.erase(it);
            continue;
        }
        ++it;
    }
}

void Chessman::calculatePosibleMerges(const Position & initial,
                                      std::vector<Position> &posible_moves) {
    calculateMoves(initial, posible_moves);
    posible_moves.push_back(initial);

    for (auto it = posible_moves.begin(); it != posible_moves.end(); ){
        if (checkIsAValidMerge(initial, *it)) {
            it = posible_moves.erase(it);
            continue;
        }
        ++it;
    }
}

bool Chessman::checkFreePath(const std::vector<Position> & path,
                             std::pair<Position, Chessman *> & chessman_in_path) const {
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
    return positions.front();
}

size_t Chessman::countPositions() const {
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

void Chessman::entangle(const Position & initial, const Position & final, Chessman & other,
                        const Position &other_position) {
    auto initial_qp_it = std::find(positions.begin(),
                                              positions.end(), initial);
    QuantumPosition & other_qp = *std::find(other.positions.begin(),
                              other.positions.end(), other_position);
    // New probabilities calculation.
    double entangled_prob =
            other_qp.getProb();
    double initial_prob = initial_qp_it->getProb();
    double new_initial_prob = entangled_prob * initial_prob;
    double new_final_prob = initial_prob * (1 - entangled_prob);
    auto insert_qp_it =initial_qp_it; insert_qp_it++;

    if (new_initial_prob < PRECISION_PROB ||
        new_final_prob < PRECISION_PROB)
        throw ChessException("no se puede volver a dividir la pieza.");

    /* If new quantum position created is real, then is placed at the
     * beginning of the entangled_list. */
    if (initial_qp_it == positions.begin() &&
        other.getPosition() != other_qp)
        insert_qp_it = positions.begin();

    std::list<QuantumPosition *> entangled_list =
            initial_qp_it->getEntangled();
    initial_qp_it->setProb(new_initial_prob);
    insert_qp_it = positions.insert(insert_qp_it,
                                 QuantumPosition(final, new_final_prob,
                                                 std::move(entangled_list),
                                                 this));
    insert_qp_it->addMeToEntangled();


    insert_qp_it->entangle(other_qp);
    other_qp.entangle(*insert_qp_it);
}

bool Chessman::chessmanIsAlreadyEntangled(Chessman * chessman) {
    for (auto & position: positions) {
        auto & entangled_list = position.getEntangled();
        for (auto & entangled_position: entangled_list) {
            if (entangled_position->isMyChessman(chessman))
                return true;
        }
    }
    return false;
}

void Chessman::checkIsInBoardOrFail(const Position & position) {
    Chessman * chessman = board.getChessmanAt(position);
    if (!chessman)
        throw ChessException("la pieza no esta en esa posicion en el tablero");
}

void Chessman::moveValidationExceptionThrower(MoveValidationStatus status) {
    switch(status){
        case CHESSMAN_NOT_IN_POSITION:
            throw ChessException("chessman is not in that position");
        case MOVING_TO_SQUARE_WITH_SAME_PIECE:
            throw ChessException("cannot move to square with a fragment"
                                 " of the same chessman");
        case MEASURING_AND_ENTANGLING:
            throw ChessException("cannot measure and entangle"
                                 " at same time");
        case ENTANGLING_SAME_PIECE_TWO_TIMES:
            throw ChessException("cannot entangle with same"
                                 " piece two times");
        case MOVING_TO_SAME_SQUARE:
            throw ChessException("cannot move to same square");
        case NON_FREE_PATH:
            throw ChessException("path is not free");
        case SPLIT_TO_OCCUPIED_SQUARE:
            throw ChessException("splitting to occupied space");
        case SPLITTING_AND_ENTANGLING:
            throw ChessException("cannot split and entangle in"
                                 " the same move");
        case SPLIT_LIMIT_REACHED:
            throw ChessException("cannot split more times that chessman");
        case MERGING_AND_ENTANGLING:
            throw ChessException("cannot merge and entangle in"
                                 " the same move");
        case PAWN_CANT_ENTANGLE:
            throw ChessException("pawn cannot entangle");
        case PAWN_CANT_SPLIT:
            throw ChessException("pawn cannot split");
        case PAWN_CANT_MERGE:
            throw ChessException("pawn cannot merge");
    }
}




