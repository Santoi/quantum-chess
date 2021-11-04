#include <iostream>
#include "board.h"
#include "chessman/tower.h"
#include "chessman/bishop.h"
#include "chessman/queen.h"
#include "ascii_chess.h"
#include "chessman/king.h"


int main() {
    // TODO hacer dinamica de turnos.
    try{
        Board board;
        board.load();
        AsciiChess ascii_chess(board);
        ascii_chess.draw();
        while(1) {
            try {
                if(ascii_chess.readCommand())
                    break;
                ascii_chess.draw();
            }
            catch(const std::exception & e){
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
    catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
