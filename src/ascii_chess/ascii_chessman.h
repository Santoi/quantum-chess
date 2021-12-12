#ifndef QUANTUM_CHESS_PROJ_ASCII_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_ASCII_CHESSMAN_H

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

class AsciiChessman {
    bool isWhite;
    char character;
public:
    AsciiChessman(bool isWhite_, char character_);

    AsciiChessman(const AsciiChessman &) = default;

    friend std::ostream& operator<< (std::ostream & os, const AsciiChessman & chessman);
};


#endif //QUANTUM_CHESS_PROJ_ASCII_CHESSMAN_H
