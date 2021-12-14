#include "chessman_data.h"
#include <string>

ChessmanData::ChessmanData(const BoardPosition &position_,
                           std::string chessman_,
                           double prob) :
    position(position_),
    chessman(std::move(chessman_)),
    probability(prob) {}
