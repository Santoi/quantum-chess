#include "chessman_data.h"


ChessmanData::ChessmanData(const Position &position_,
                                           std::string chessman_,
                                           double prob): position(position_),
                                                         chessman(std::move(chessman_)),
                                                         probability(prob) {}