#include <iostream>
#include "board.h"
#include "chessman/tower.h"
#include "chessman/bishop.h"
#include "chessman/queen.h"
#include "ascii_chess.h"
#include "chessman/king.h"


int main() {
    try {
		AsciiChess ascii_chess;
		ascii_chess.execute();
	}
    catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
