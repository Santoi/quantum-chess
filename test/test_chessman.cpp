#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../src/quantum_chess/board.h"
#include "../src/quantum_chess/chessman/tower.h"
#include "../src/quantum_chess/chessman/tower.h"
#include "../src/quantum_chess/chessman/bishop.h"
#include "../src/quantum_chess/chessman/king.h"
#include "../src/quantum_chess/chess_exception.h"

TEST(Chessman, MoveFromANonExistingPosition) {
    Board board;
    ChessmanContainer tower('T', Position(0, 1), true, board);
    Chessman * chessman = tower.get();
    board.addChessman(std::move(tower));

    EXPECT_THROW(chessman->move(Position(0, 2),
                                Position(0, 3)), ChessException);
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
    ChessmanContainer tower('T', Position(5, 1), true, board);
    Chessman * chessman = tower.get();
    board.addChessman(std::move(tower));

    chessman->move(Position(5, 1), Position(5, 3));
    chessman->move(Position(5, 3), Position(1, 3));

    EXPECT_EQ(Position(1, 3), chessman->getPosition());
}

TEST(Tower, MoveWithChessmanInTheBoard) {
    Board board;
    // Se crea pieza en (5, 1)
    ChessmanContainer tower_cont('T', Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    ChessmanContainer tower_2_cont('T', Position(7, 3), true, board);
    Chessman * tower = tower_cont.get();
    board.addChessman(std::move(tower_cont));
    board.addChessman(std::move(tower_2_cont));

    tower->move(Position(5, 1), Position(7, 1));

    EXPECT_EQ(Position(7, 1), tower->getPosition());

    tower->move(Position(7, 1), Position(7, 2));
    EXPECT_EQ(Position(7, 2), tower->getPosition());
}

TEST(Tower, BadMoveToChessmanSameColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    ChessmanContainer tower_cont('T', Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    ChessmanContainer tower2_cont('T', Position(7, 1), true, board);
    Chessman * tower = tower_cont.get();

    board.addChessman(std::move(tower_cont));
    board.addChessman(std::move(tower2_cont));

    EXPECT_THROW(tower->move(Position(5, 1), Position(7, 1)),
                 ChessException);
}

TEST(Tower, MoveToChessmanDiffColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    ChessmanContainer tower_cont('T', Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    ChessmanContainer tower2_cont('T', Position(7, 1), false, board);
    Chessman * tower = tower_cont.get();

    board.addChessman(std::move(tower_cont));
    board.addChessman(std::move(tower2_cont));

    tower->move(Position(5, 1), Position(7, 1));

    EXPECT_EQ(Position(7, 1), tower->getPosition());
}

TEST(Tower, BadMoveWithChessmanInTheMiddle) {
    Board board;
    // Se crea pieza en (7, 1)
    ChessmanContainer tower_cont('T', Position(7, 1), true, board);
    // Se crea pieza en (7, 3) y se agrega al tablero.
    ChessmanContainer tower2_cont('T', Position(7, 3), true, board);
    Chessman * tower = tower_cont.get();

    board.addChessman(std::move(tower_cont));
    board.addChessman(std::move(tower2_cont));

    EXPECT_THROW(tower->move(Position(7, 1), Position(7, 5)),
                 ChessException);
}

TEST(Tower, BadMoveWithEmptyBoard) {
    Board board;
    ChessmanContainer cont('T', Position(5, 1), true, board);
    Chessman * tower = cont.get();
    board.addChessman(std::move(cont));

    EXPECT_THROW(tower->move(Position(5, 1), Position(2, 3)),
                 ChessException);
}

// Se testea el alfil para probar el movimiento diagonal
TEST(Bishop, CalculatePosibleMovesWithEmptyBoard) {
    Board board;
    ChessmanContainer bishop_cont('B', Position(2, 1), true, board);
    Chessman * bishop = bishop_cont.get();
    board.addChessman(std::move(bishop_cont));
    std::vector<Position> posible_moves;

    bishop->calculatePosibleMoves(Position(2, 1), posible_moves);

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
    ChessmanContainer bishop_cont('B', Position(7, 7), true, board);
    Chessman * bishop = bishop_cont.get();
    board.addChessman(std::move(bishop_cont));

    bishop->move(Position(7, 7), Position(4, 4));
    bishop->move(Position(4, 4), Position(1, 7));

    EXPECT_EQ(Position(1, 7), bishop->getPosition());
}

TEST(Bishop, MoveWithChessmanInTheBoard) {
    Board board;
    ChessmanContainer tower_cont('T', Position(7, 3), true, board);
    // Se crea pieza en (7, 3) y se agrega al tablero.
    ChessmanContainer bishop_cont('B', Position(5, 1), true, board);
    Chessman * bishop = bishop_cont.get();

    board.addChessman(std::move(tower_cont));
    board.addChessman(std::move(bishop_cont));

    bishop->move(Position(5, 1), Position(6, 2));

    EXPECT_EQ(Position(6, 2), bishop->getPosition());

    bishop->move(Position(6, 2), Position(5, 3));
    EXPECT_EQ(Position(5, 3), bishop->getPosition());
}

TEST(Bishop, BadMoveToChessmanSameColorPosition) {
    Board board;
    ChessmanContainer tower_cont('T', Position(7, 7), true, board);
    // Se crea pieza en (7, 3) y se agrega al tablero.
    ChessmanContainer bishop_cont('B', Position(5, 5), true, board);
    Chessman * bishop = bishop_cont.get();

    board.addChessman(std::move(tower_cont));
    board.addChessman(std::move(bishop_cont));

    EXPECT_THROW(bishop->move(Position(5, 5), Position(7, 7)),
                 ChessException);
}

TEST(Bishop, MoveToChessmanDiffColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    ChessmanContainer tower_cont('T', Position(0, 1), false, board);
    // Se crea pieza en (7, 3) y se agrega al tablero.
    ChessmanContainer bishop_cont('B', Position(1, 0), true, board);
    Chessman * bishop = bishop_cont.get();

    board.addChessman(std::move(tower_cont));
    board.addChessman(std::move(bishop_cont));

    bishop->move(Position(1, 0), Position(0, 1));

    EXPECT_EQ(Position(0, 1), bishop->getPosition());
}

TEST(Bishop, BadMoveWithChessmanInTheMiddle) {
    Board board;
    ChessmanContainer tower_cont('T', Position(6, 3), true, board);
    // Se crea pieza en (7, 3) y se agrega al tablero.
    ChessmanContainer bishop_cont('B', Position(7, 2), true, board);
    Chessman * bishop = bishop_cont.get();

    board.addChessman(std::move(tower_cont));
    board.addChessman(std::move(bishop_cont));

    EXPECT_THROW(bishop->move(Position(7, 2), Position(5, 4)),
                 ChessException);
}

TEST(Bishop, BadMoveWithEmptyBoard) {
    Board board;
    ChessmanContainer container('B', Position(5, 1), true, board);
    Chessman * bishop = container.get();

    EXPECT_THROW(bishop->move(Position(5, 1), Position(5, 2)),
                 ChessException);
}

// Se testea movimientos del rey.
TEST(King, CalculatePosibleMovesWithEmptyBoard) {
    Board board;
    ChessmanContainer container('K', Position(2, 1), true, board);
    Chessman * king = container.get();
    std::vector<Position> posible_moves;

    king->calculatePosibleMoves(Position(2, 1), posible_moves);

    std::vector<Position> posible_moves_gt = {
            Position(3, 1), Position(3, 2),
            Position(2, 2), Position(1, 2),
            Position(1, 1), Position(1, 0),
            Position(2, 0), Position(3, 0)
    };

    EXPECT_EQ(posible_moves, posible_moves_gt);
}

// Del caballo se testean sus movimientos rodeado por piezas.
TEST(Knight, CalculatePosibleMovesSurrounded) {
	Board board;
	std::vector<Position> sorround = {
            Position(5, 4), Position(5, 5),
            Position(4, 5), Position(3, 5),
            Position(3, 4), Position(3, 3),
            Position(4, 3), Position(5, 3)
	};
	std::vector<Position> posible_moves_gt = {
            Position(6, 5), Position(5, 6),
            Position(3, 6), Position(2, 5),
            Position(2, 3), Position(3, 2),
            Position(5, 2), Position(6, 3),
	};
	
	for (size_t i = 0; i < sorround.size(); i++){
		board.addChessman(std::move(ChessmanContainer('T',
                                                      sorround[i],
                                                      true, board)));
	}
	
	ChessmanContainer horse('H', Position(4, 4), true, board);
	
	Chessman * chessman = horse.get();
	board.addChessman(std::move(horse));
	
	std::vector<Position> posible_moves;
	chessman->calculatePosibleMoves(Position(4, 4), posible_moves);
	
	EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Pawn, PosibleMoveWithEmptyBoard) {
	Board board;
	ChessmanContainer pawn('P', Position(1, 1), true, board);
	
	Chessman * chessman = pawn.get();
	board.addChessman(std::move(pawn));
	
	std::vector<Position> posible_moves_gt = {
            Position(1, 2), Position(1, 3),
	};
	
	std::vector<Position> posible_moves;
	chessman->calculatePosibleMoves(Position(1, 1), posible_moves);
	
	EXPECT_EQ(posible_moves, posible_moves_gt);
	
	chessman->move(Position(1, 1), Position(1, 3));
	
	posible_moves_gt = {
            Position(1, 4)
	};
	
	chessman->calculatePosibleMoves(Position(1, 3), posible_moves);
	
	EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Pawn, PosibleMoveWithChessmanInPositionToCaptureButSameColor) {
	Board board;
	ChessmanContainer pawn('P', Position(1, 1), true, board);
	
	Chessman * chessman = pawn.get();
	board.addChessman(std::move(pawn));
	
	board.addChessman(std::move(ChessmanContainer('P',
                                                  Position(2, 2),
                                                  true, board)));
	board.addChessman(std::move(ChessmanContainer('P',
                                                  Position(0, 2),
                                                  true, board)));
	
	std::vector<Position> posible_moves_gt = {
            Position(1, 2), Position(1, 3)
	};
	
	std::vector<Position> posible_moves;
	chessman->calculatePosibleMoves(Position(1, 1), posible_moves);
	
	EXPECT_EQ(posible_moves, posible_moves_gt);
}		

TEST(Pawn, PosibleMoveWithChessmanInPositionToCapture) {
	Board board;
	ChessmanContainer pawn('P', Position(1, 1), true, board);
	
	Chessman * chessman = pawn.get();
	board.addChessman(std::move(pawn));
	
	board.addChessman(std::move(ChessmanContainer('P',
                                                  Position(2, 2),
                                                  false, board)));
	board.addChessman(std::move(ChessmanContainer('P',
                                                  Position(0, 2),
                                                  false, board)));
	
	std::vector<Position> posible_moves_gt = {
            Position(1, 2), Position(2, 2),
            Position(0, 2), Position(1, 3)
	};
	
	std::vector<Position> posible_moves;
	chessman->calculatePosibleMoves(Position(1, 1), posible_moves);
	
	EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Chessman, OneSplit){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 0.5));
    EXPECT_TRUE(QuantumPosition(2, 2, 0.5) == chessman->getAllPositions()[1]);
}

TEST(Chessman, TwoSplitsSplittingReal){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 0.25));
    EXPECT_TRUE(QuantumPosition(2, 1, 0.25) == chessman->getAllPositions()[1]);
    EXPECT_TRUE(QuantumPosition(2, 2, 0.5) == chessman->getAllPositions()[2]);
}

TEST(Chessman, TwoSplitsSplittingFake){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 0.5));
    EXPECT_TRUE(QuantumPosition(2, 1, 0.25) == chessman->getAllPositions()[2]);
    EXPECT_TRUE(QuantumPosition(2, 3, 0.25) == chessman->getAllPositions()[1]);
}

TEST(Chessman, SplitThenMoveSplitted){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2),
                    Position(2, 2));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 0.5));
    EXPECT_TRUE(QuantumPosition(2, 2, 0.5) == chessman->getAllPositions()[1]);

    chessman->move(Position(1, 2), Position(1, 3));
    chessman->move(Position(2, 2), Position(2, 3));
    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 0.5));
    EXPECT_TRUE(QuantumPosition(2, 3, 0.5) == chessman->getAllPositions()[1]);
}

TEST(Chessman, OneBadSplitToSamePosition){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1),
                           true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    EXPECT_THROW(chessman->split(Position(1, 1), Position(1, 1),
                                 Position(2, 2)), ChessException);
}

TEST(Chessman, OneBadSplitToInvalidPosition){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1),
                           true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    EXPECT_THROW(chessman->split(Position(1, 1), Position(1, 1),
                                 Position(3, 2)), ChessException);
}

TEST(Chessman, SplitToSamePosition){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1),
                           true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    EXPECT_THROW(chessman->split(Position(1, 1), Position(2, 2),
                                 Position(2, 2)), ChessException);
}

TEST(Chessman, MergeOneSplit){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

    chessman->merge(Position(1,2), Position(2, 2), Position(1, 3));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 1));
}

TEST(Chessman, MergeTwoSplitsSplittingRealMergingTheTwoFakes){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

    chessman->merge(Position(2, 2), Position(2, 1), Position(1, 1));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 0.25));
    EXPECT_TRUE(chessman->getAllPositions()[1] == QuantumPosition(1, 1, 0.75));
}

TEST(Chessman, MergeTwoSplitsSplittingRealMergingRealWithFake){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

    chessman->merge(Position(1, 3), Position(2,  2), Position(1, 1));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 1, 0.75));
    EXPECT_TRUE(chessman->getAllPositions()[1] == QuantumPosition(2, 1, 0.25));
}

TEST(Chessman, TwoSplitsSplittingFakeMergingFakes){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

    chessman->merge(Position(2, 3), Position(2, 1), Position(2, 2));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 0.5));
    EXPECT_TRUE(chessman->getAllPositions()[1] == QuantumPosition(2, 2, 0.5));
}

TEST(Chessman, SplitThenMoveSplittedThenMerge){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2),
                    Position(2, 2));

    chessman->move(Position(1, 2), Position(1, 3));
    chessman->move(Position(2, 2), Position(2, 3));

    chessman->merge(Position(1, 3), Position(2, 3), Position(2, 4));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(2, 4, 1));
}

TEST(Chessman, MergeOneSplitToPositionOfOneOfThem) {
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

    chessman->merge(Position(1,2), Position(2, 2), Position(2, 2));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(2, 2, 1));
}

TEST(Chessman, MergeOneSplitToPositionInTheSameLine) {
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(1, 3));

    chessman->merge(Position(1,2), Position(1, 3), Position(1, 1));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 1, 1));
}

TEST(Chessman, OneBadMergeToInvalidPosition){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1),
                            true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2),
                    Position(2, 2));

    EXPECT_THROW(chessman->merge(Position(1, 2), Position(2, 2),
                                 Position(3, 3)), ChessException);
}

TEST(Chessman, MergeFromSamePosition){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1),
                            true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2),
                    Position(2, 2));

    EXPECT_THROW(chessman->merge(Position(1, 2), Position(1, 2),
                                 Position(3, 3)), ChessException);
}


