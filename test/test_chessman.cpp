#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/chessman/chessman.h"
#include "../src/board.h"
#include "../src/chessman/tower.h"
#include "../src/chessman/bishop.h"
#include "../src/chessman/king.h"

TEST(Chessman, MoveFromANonExistingPosition) {
    Board board;
    Tower tower(Position(0, 1), true, board);

    EXPECT_THROW(tower.move(Position(0, 2),
                           Position(0, 3)), std::invalid_argument);
}

TEST(Tower, CalculatePosibleMovesWithEmptyBoard) {
    Board board;
    Tower tower(Position(5, 1), true, board);
    std::vector<Position> posible_moves;

    tower.calculatePosibleMoves(Position(5, 1), posible_moves);

    std::vector<Position> posible_moves_gt = {
            Position(5, 0), Position(5, 2),
            Position(5, 3), Position(5, 4),
            Position(5, 5), Position(5, 6),
            Position(5, 7), Position(0, 1),
            Position(1, 1), Position(2, 1),
            Position(3, 1), Position(4, 1),
            Position(6, 1), Position(7, 1),
    };

    EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Tower, MoveWithEmptyBoard) {
    Board board;
    Tower tower(Position(5, 1), true, board);

    tower.move(Position(5, 1), Position(5, 3));
    tower.move(Position(5, 3), Position(1, 3));

    EXPECT_EQ(Position(1, 3), tower.getPosition());
}

TEST(Tower, MoveWithChessmanInTheBoard) {
    Board board;
    // Se crea pieza en (5, 1)
    Tower tower(Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 3), true, board);
    board.addChessman(&tower_2);

    tower.move(Position(5, 1), Position(7, 1));

    EXPECT_EQ(Position(7, 1), tower.getPosition());

    tower.move(Position(7, 1), Position(7,2));
    EXPECT_EQ(Position(7, 2), tower.getPosition());
}

TEST(Tower, BadMoveToChessmanSameColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    Tower tower(Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 1), true, board);
    board.addChessman(&tower_2);

    EXPECT_THROW(tower.move(Position(5, 1), Position(7, 1)), std::invalid_argument);
}

TEST(Tower, MoveToChessmanDiffColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    Tower tower(Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 1), false, board);
    board.addChessman(&tower_2);

    tower.move(Position(5, 1), Position(7, 1));

    EXPECT_EQ(Position(7,1), tower.getPosition());
}

TEST(Tower, BadMoveWithChessmanInTheMiddle) {
    Board board;
    // Se crea pieza en (5, 1)
    Tower tower(Position(7, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 3), true, board);
    board.addChessman(&tower_2);

    EXPECT_THROW(tower.move(Position(7,1), Position(7,5)), std::invalid_argument);
}

TEST(Tower, BadMoveWithEmptyBoard) {
    Board board;
    Tower tower(Position(5, 1), true, board);
    std::vector<Position> posible_moves;

    EXPECT_THROW(tower.move(Position(5, 1), Position(2, 3)), std::invalid_argument);
}
// Se testea el alfil para probar el movimiento diagonal
TEST(Bishop, CalculatePosibleMovesWithEmptyBoard) {
    Board board;
    Bishop bishop(Position(2, 1), true, board);
    std::vector<Position> posible_moves;

    bishop.calculatePosibleMoves(Position(2, 1), posible_moves);

    std::vector<Position> posible_moves_gt = {
            Position(1, 0), Position(3, 2),
            Position(4, 3), Position(5, 4),
            Position(6, 5), Position(7, 6),
            Position(3, 0), Position(1, 2),
            Position(0, 3)
    };

    EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Bishop, MoveWithEmptyBoard) {
    Board board;
    Bishop bishop(Position(7, 7), true, board);

    bishop.move(Position(7, 7), Position(4, 4));
    bishop.move(Position(4, 4), Position(1, 7));

    EXPECT_EQ(Position(1, 7), bishop.getPosition());
}

TEST(Bishop, MoveWithChessmanInTheBoard) {
    Board board;
    // Se crea pieza en (5, 1)
    Bishop bishop(Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 3), true, board);
    board.addChessman(&tower_2);

    bishop.move(Position(5, 1), Position(6, 2));

    EXPECT_EQ(Position(6, 2), bishop.getPosition());

    bishop.move(Position(6, 2), Position(5, 3));
    EXPECT_EQ(Position(5, 3), bishop.getPosition());
}

TEST(Bishop, BadMoveToChessmanSameColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    Bishop bishop(Position(5, 5), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 7), true, board);
    board.addChessman(&tower_2);

    EXPECT_THROW(bishop.move(Position(5, 5), Position(7, 7)), std::invalid_argument);
}

TEST(Bishop, MoveToChessmanDiffColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    Bishop bishop(Position(1, 0), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(0, 1), false, board);
    board.addChessman(&tower_2);

    bishop.move(Position(1, 0), Position(0, 1));

    EXPECT_EQ(Position(0, 1), bishop.getPosition());
}

TEST(Bishop, BadMoveWithChessmanInTheMiddle) {
    Board board;
    // Se crea pieza en (5, 1)
    Bishop bishop(Position(7, 2), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(6, 3), true, board);
    board.addChessman(&tower_2);

    EXPECT_THROW(bishop.move(Position(7, 2), Position(5, 4)), std::invalid_argument);
}

TEST(Bishop, BadMoveWithEmptyBoard) {
    Board board;
    Bishop bishop(Position(5, 1), true, board);
    std::vector<Position> posible_moves;

    EXPECT_THROW(bishop.move(Position(5, 1), Position(5, 2)), std::invalid_argument);
}

TEST(King, CalculatePosibleMovesWithEmptyBoard) {
    Board board;
    King king(Position(2, 1), true, board);
    std::vector<Position> posible_moves;

    king.calculatePosibleMoves(Position(2, 1), posible_moves);

    std::vector<Position> posible_moves_gt = {
            Position(3, 1), Position(3, 2),
            Position(2, 2), Position(1, 2),
            Position(1, 1), Position(1, 0),
            Position(2, 0), Position(3, 0)
    };

    EXPECT_EQ(posible_moves, posible_moves_gt);
}

// TODO test pieza en el medio.
