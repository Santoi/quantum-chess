#include <iostream>
#include "board.h"
#include "chessman/tower.h"
#include "chessman/bishop.h"
#include "chessman/queen.h"
#include "ascii_chess.h"
#include "chessman/king.h"


int main() {
    try{
        Board board;
        Tower tower(Position(0, 0), true, board);
        Tower tower2(Position(0, 7), false, board);
        Queen queen(Position(3, 0), true, board);
        Bishop bishop(Position(2, 0), true, board);
        King king(Position(4, 0), true, board);
        board.addChessman(&tower);
        board.addChessman((&tower2));
        board.addChessman(&bishop);
        board.addChessman(&queen);
        board.addChessman(&king);
        AsciiChess ascii_chess(board);
        ascii_chess.draw();
        while(1) {
            try {
                std::string first, second, three, fourth, fifth;
                std::cin >> first;
                if (first == "q")
                    break;
                std::cin >> second >> three >> fourth >> fifth;
                ascii_chess.readCommand(first, second, three, fourth, fifth);
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
