#include <ostream>
#include "ascii_chessman.h"

AsciiChessman::AsciiChessman(bool isWhite_, char character_): isWhite(isWhite_),
    character(character_) {}

std::ostream &operator<<(std::ostream &os, const AsciiChessman &chessman) {
    if (chessman.isWhite)
        os << GREEN << chessman.character << RESET;
    else
        os << RED << chessman.character << RESET;
    return os;
}
