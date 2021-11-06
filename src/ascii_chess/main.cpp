#include <iostream>
#include "../quantum_chess/board.h"
#include "ascii_chess.h"


int main() {
    try {
		AsciiChess ascii_chess;
		ascii_chess.execute();
	}
    catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
