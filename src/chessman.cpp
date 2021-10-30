#include "chessman.h"

Chessman::Chessman(int value): value(value) {}

int Chessman::getValue() const {
    return value;
}