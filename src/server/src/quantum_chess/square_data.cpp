#include "square_data.h"

SquareData::SquareData(char chessman_, bool white_, const Position &position_,
                       double probability_) : chessman(chessman_),
                                              white(white_),
                                              position(position_),
                                              probability(probability_) {}
