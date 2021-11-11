#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../src/quantum_chess/board.h"
#include "../src/quantum_chess/chessman/tower.h"
#include "../src/quantum_chess/chessman/tower.h"
#include "../src/quantum_chess/chessman/bishop.h"
#include "../src/quantum_chess/chessman/king.h"
#include "../src/quantum_chess/chess_exception.h"


// TODO test capture.
TEST(Chessman, MoveFromANonExistingPosition) {
    Board board;
    ChessmanContainer tower('T', Position(0, 1), true, board);
    Chessman * chessman = tower.get();
    board.addChessman(std::move(tower));

    EXPECT_THROW(chessman->move(Position(0, 2),
                                Position(0, 3)), ChessException);
}

TEST(Chessman, ClassicToClassicCapture) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    bishop->move(Position(0, 0), Position(1, 1));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(1, 1, 1));
    EXPECT_FALSE(board.isThere(queen));
}

TEST(Chessman, MoveThenMove) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    Chessman * queen = queen_cont.get();

    board.addChessman(std::move(queen_cont));

    queen->move(Position(1, 1), Position(2, 2));
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(2, 2, 1));

    queen->move(Position(2, 2), Position(3, 3));
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(3, 3, 1));
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
    EXPECT_TRUE(QuantumPosition(2, 2, 0.5) == chessman->getPosition(1));
}

TEST(Chessman, TwoSplitsSplittingReal){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 0.25));
    EXPECT_TRUE(QuantumPosition(2, 1, 0.25) == chessman->getPosition(1));
    EXPECT_TRUE(QuantumPosition(2, 2, 0.5) == chessman->getPosition(2));
}

TEST(Chessman, TwoSplitsSplittingFake){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 0.5));
    EXPECT_TRUE(QuantumPosition(2, 3, 0.25) == chessman->getPosition(1));
    EXPECT_TRUE(QuantumPosition(2, 1, 0.25) == chessman->getPosition(2));

}

TEST(Chessman, SplitThenMoveSplitted){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2),
                    Position(2, 2));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 0.5));
    EXPECT_TRUE(QuantumPosition(2, 2, 0.5) == chessman->getPosition(1));

    chessman->move(Position(1, 2), Position(1, 3));
    chessman->move(Position(2, 2), Position(2, 3));
    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 0.5));
    EXPECT_TRUE(QuantumPosition(2, 3, 0.5) == chessman->getPosition(1));
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
    EXPECT_TRUE(chessman->getPosition(1) == QuantumPosition(1, 1, 0.75));
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
    EXPECT_TRUE(chessman->getPosition(1) == QuantumPosition(2, 1, 0.25));
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
    EXPECT_TRUE(chessman->getPosition(1) == QuantumPosition(2, 2, 0.5));
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


 TEST(Chessman, OneSplitMeasureReal){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

    chessman->measure(Position(1, 2));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_EQ(chessman->getAllPositions().size(), 1);
}

TEST(Chessman, OneSplitMeasureFake){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

    chessman->measure(Position(2, 2));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_EQ(chessman->getAllPositions().size(), 1);
}

TEST(Chessman, TwoSplitsSplittingRealMeasureReal){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

    chessman->measure(Position(1, 3));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 1));
    EXPECT_EQ(chessman->getAllPositions().size(), 1);
}

TEST(Chessman, TwoSplitsSplittingRealMeasureFakeFirstSplit){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

    chessman->measure(Position(2, 2));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 0.5));
    EXPECT_TRUE(chessman->getPosition(1) == QuantumPosition(2, 1, 0.5));
    EXPECT_EQ(chessman->getAllPositions().size(), 2);
}

TEST(Chessman, TwoSplitsSplittingRealMeasureFakeSecondSplit){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

    chessman->measure(Position(2, 1));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 3, 0.25/0.75));
    EXPECT_TRUE(chessman->getPosition(1) ==
                QuantumPosition(2, 2, 0.5/0.75));
    EXPECT_EQ(chessman->getAllPositions().size(), 2);
}

TEST(Chessman, TwoSplitsSplittingFakeMeasuringOneOfThem){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

    chessman->measure(Position(2, 3));

    EXPECT_TRUE(chessman->getPosition() == QuantumPosition(1, 2, 0.5/0.75));
    EXPECT_TRUE(QuantumPosition(2, 1, 0.25/0.75) ==
                chessman->getPosition(1));
    EXPECT_EQ(chessman->getAllPositions().size(), 2);
}

TEST(Chessman, MeasureOtherPosition){
    Board board(0);
    ChessmanContainer queen('Q', Position(1, 1), true, board);
    Chessman * chessman = queen.get();
    board.addChessman(std::move(queen));

    chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
    chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

    EXPECT_THROW(chessman->measure(Position(4, 4)), ChessException);
}

TEST(Chessman, MoveWithTwoQuantumInTheMiddle){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(2, 2), Position(4, 4));
    queen->split(Position(2, 2), Position(3, 3), Position(2, 3));
    EXPECT_THROW(bishop->move(Position(0, 0), Position(5, 5)), ChessException);
}

TEST(Chessman, MoveClassicWithMeasureToFakeQuantumPieceOfSameColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
    bishop->move(Position(0, 0), Position(3, 3));
    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(3, 3, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, MoveClassicWithMeasureToRealQuantumPieceOfSameColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
    bishop->move(Position(0, 0), Position(3, 3));
    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(3, 3, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, MoveClassicWithMeasureToRealQuantumPieceOfDifferentColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
    bishop->move(Position(0, 0), Position(3, 3));
    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(3, 3, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_FALSE(board.isThere(queen));
}

TEST(Chessman, MoveClassicWithMeasureToFakeQuantumPieceOfDifferentColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
    bishop->move(Position(0, 0), Position(3, 3));
    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(3, 3, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}


// TODO que pasa si son del mismo palo.
TEST(Chessman, MoveRealQuantumPieceWithMeasureToClassicAndCaptureDifferentColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
    queen->move(Position(3, 3), Position(0, 0));
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(0, 0, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
    EXPECT_FALSE(board.isThere(bishop));
}

TEST(Chessman, MoveClassicWithMeasureToFakeQuantumPieceDifferentColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
    queen->move(Position(3, 3), Position(0, 0));
    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
    EXPECT_TRUE(board.isThere(bishop));
}

TEST(Chessman, MoveRealQuantumPieceWithMeasureToClassicAndCaptureSameColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));
    // TODO VER SI ESTO ESTA BIEN.
    queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
    EXPECT_THROW(queen->move(Position(3, 3), Position(0, 0)), ChessException);
}

TEST(Chessman, MoveFakeQuantumPieceWithMeasureToClassicAndCaptureSameColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
    EXPECT_THROW(queen->move(Position(3, 3), Position(0, 0)), ChessException);
}

TEST(Chessman, MoveMeasureFromRealQuantumToRealQuantumOfDifferentColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer queen_2_cont('Q', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * queen_2 = queen_2_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(queen_2_cont));

    queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
    queen_2->split(Position(0, 0), Position(1, 1), Position(0, 1));
    queen_2->move(Position(1, 1), Position(3, 3));
    EXPECT_TRUE(queen_2->getPosition() == QuantumPosition(3, 3, 1));
    EXPECT_TRUE(queen_2->getAllPositions().size() == 1);
    EXPECT_FALSE(board.isThere(queen));
}

TEST(Chessman, MoveMeasureFromRealQuantumToFakeQuantumOfDifferentColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer queen_2_cont('Q', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * queen_2 = queen_2_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(queen_2_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
    queen_2->split(Position(0, 0), Position(1, 1), Position(0, 1));
    queen_2->move(Position(1, 1), Position(3, 3));
    EXPECT_TRUE(queen_2->getPosition() == QuantumPosition(3, 3, 1));
    EXPECT_TRUE(queen_2->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, MoveMeasureFromFakeQuantumToRealQuantumOfDifferentColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer queen_2_cont('Q', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * queen_2 = queen_2_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(queen_2_cont));

    queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
    queen_2->split(Position(0, 0), Position(0, 1), Position(1, 1));
    queen_2->move(Position(1, 1), Position(3, 3));
    EXPECT_TRUE(queen_2->getPosition() == QuantumPosition(0, 1, 1));
    EXPECT_TRUE(queen_2->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(3, 3, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, MoveMeasureFromFakeQuantumToFakeQuantumOfDifferentColor) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer queen_2_cont('Q', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * queen_2 = queen_2_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(queen_2_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
    queen_2->split(Position(0, 0), Position(0, 1), Position(1, 1));
    queen_2->move(Position(1, 1), Position(3, 3));
    EXPECT_TRUE(queen_2->getPosition() == QuantumPosition(0, 1, 1));
    EXPECT_TRUE(queen_2->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, CantSplitAndEntangle){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer queen_2_cont('Q', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * queen_2 = queen_2_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(queen_2_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
    EXPECT_THROW(queen_2->split(Position(0, 0), Position(0, 1), Position(3, 3)), ChessException);
}

TEST(Chessman, CantMergeAndEntangle){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer queen_2_cont('Q', Position(0, 0), false, board);
    Chessman * queen = queen_cont.get(), * queen_2 = queen_2_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(queen_2_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
    queen_2->split(Position(0, 0), Position(0, 1), Position(2, 2));
    EXPECT_THROW(queen->merge(Position(3, 3), Position(1, 2), Position(1, 1)), ChessException);
}

// TODO modificar esto porque le falta entrelazamiento.
TEST(Chessman, MoveWithOneQuantumFakeInTheMiddle){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(4, 4, 0.5));
    EXPECT_TRUE(bishop->getPosition(1) == QuantumPosition(0, 0, 0.5));
}

// medir entre ellos.
TEST(Chessman, EntangleWithRealThenMeasureTheOneInTheMiddleThatWasEntangled){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(2, 2), Position(1, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    queen->measure(Position(2, 2));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(2, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, EntangleWithRealThenMeasureTheOneInTheMiddleThatWasNotEntangled){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(2, 2), Position(1, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    queen->measure(Position(1, 2));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(2, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, EntangleWithFakeThenMeasureTheOneInTheMiddleThatWasEntangled){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    queen->measure(Position(2, 2));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(4, 4, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, EntangleThenMoveBothPiecesThenMeasure){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    bishop->move(Position(4, 4), Position(5, 5));
    queen->move(Position(1, 2), Position(1, 1));

    queen->measure(Position(1, 1));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(5, 5, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 1, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}



TEST(Chessman, EntangleWithFakeThenMeasureTheOneInTheMiddleThatWasNotEntangled){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    queen->measure(Position(1, 2));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(4, 4, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, EntangleWithRealThenSplitTheNonEntangledAndMeasureBothOfThem){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(2, 2), Position(1, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    queen->split(Position(1, 2), Position(0, 2), Position(1, 3));

    queen->measure(Position(1, 3));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 0.5));
    EXPECT_TRUE(bishop->getPosition(1) == QuantumPosition(4, 4, 0.5));
    EXPECT_TRUE(bishop->positionsSize() == 2);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(2, 2, 0.5/0.75));
    EXPECT_TRUE(queen->getPosition(1) == QuantumPosition(0, 2, 0.25/0.75));
    EXPECT_TRUE(queen->positionsSize() == 2);

    queen->resetMeasured();
    bishop->resetMeasured();
    queen->measure(Position(0, 2));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 1));
    EXPECT_TRUE(bishop->positionsSize() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(2, 2, 1));
    EXPECT_TRUE(queen->positionsSize() == 1);
}

TEST(Chessman, EntangleWithFakeThenSplitEntangledThenMeasureNonMiddle){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    queen->split(Position(2, 2), Position(3, 3), Position(2, 3));

    bishop->measure(Position(0, 0));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(4, 4, 1));
    EXPECT_TRUE(bishop->positionsSize() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->positionsSize() == 1);
}

TEST(Chessman, EntangleWithRealThenSplitGeneratedThenMeasureOriginal){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    bishop->split(Position(4, 4), Position(3, 3), Position(5, 5));

    bishop->measure(Position(0, 0));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(3, 3, 0.25/0.5));
    EXPECT_TRUE(bishop->getPosition(1) == QuantumPosition(5, 5, 0.25/0.5));
    EXPECT_TRUE(bishop->positionsSize() == 2);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(1, 2, 1));
    EXPECT_TRUE(queen->positionsSize() == 1);
}


TEST(Chessman, EntangleWithFakethenSplitNotEntangledAndMeasureEntangled){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(1, 1), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
    bishop->move(Position(0, 0), Position(4, 4));

    queen->split(Position(1, 2), Position(0, 2), Position(1, 3));

    queen->measure(Position(2, 2));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(4, 4, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(0, 2, 0.5));
    EXPECT_TRUE(queen->getPosition(1) == QuantumPosition(1, 3, 0.5));
    EXPECT_TRUE(queen->getAllPositions().size() == 2);
}

TEST(Chessman, DoubleEntangleWithRealThenMeasureMiddle){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(4, 3), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    ChessmanContainer tower_cont('B', Position(2, 6), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get(), * tower = tower_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));
    board.addChessman(std::move(tower_cont));

    queen->split(Position(4, 3), Position(4, 4), Position(4, 2));
    bishop->move(Position(0, 0), Position(7, 7));
    tower->move(Position(2, 6), Position(5, 3));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 0.5));
    EXPECT_TRUE(bishop->getPosition(1) == QuantumPosition(7, 7, 0.5));
    EXPECT_TRUE(tower->getPosition() == QuantumPosition(2, 6, 0.5));
    EXPECT_TRUE(tower->getPosition(1) == QuantumPosition(5, 3, 0.5));

    queen->measure(Position(4, 4));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(tower->getPosition() == QuantumPosition(2, 6, 1));
    EXPECT_TRUE(tower->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(4, 4, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, DoubleEntangleWithFakeThenMeasureMiddle){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(4, 3), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    ChessmanContainer tower_cont('B', Position(2, 6), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get(), * tower = tower_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));
    board.addChessman(std::move(tower_cont));

    queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
    bishop->move(Position(0, 0), Position(7, 7));
    tower->move(Position(2, 6), Position(5, 3));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(7, 7, 0.5));
    EXPECT_TRUE(bishop->getPosition(1) == QuantumPosition(0, 0, 0.5));
    EXPECT_TRUE(tower->getPosition() == QuantumPosition(5, 3, 0.5));
    EXPECT_TRUE(tower->getPosition(1) == QuantumPosition(2, 6, 0.5));

    queen->measure(Position(4, 4));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(7, 7, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(tower->getPosition() == QuantumPosition(5, 3, 1));
    EXPECT_TRUE(tower->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(4, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, DoubleEntangleWithRealThenMeasureOneOfOthers){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(4, 3), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    ChessmanContainer tower_cont('B', Position(2, 6), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get(), * tower = tower_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));
    board.addChessman(std::move(tower_cont));

    queen->split(Position(4, 3), Position(4, 4), Position(4, 2));
    bishop->move(Position(0, 0), Position(7, 7));
    tower->move(Position(2, 6), Position(5, 3));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 0.5));
    EXPECT_TRUE(bishop->getPosition(1) == QuantumPosition(7, 7, 0.5));
    EXPECT_TRUE(tower->getPosition() == QuantumPosition(2, 6, 0.5));
    EXPECT_TRUE(tower->getPosition(1) == QuantumPosition(5, 3, 0.5));

    tower->measure(Position(2, 6));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(0, 0, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(tower->getPosition() == QuantumPosition(2, 6, 1));
    EXPECT_TRUE(tower->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(4, 4, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, DoubleEntangleWithFakeThenMeasureOneOfOthers){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(4, 3), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    ChessmanContainer tower_cont('B', Position(2, 6), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get(), * tower = tower_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));
    board.addChessman(std::move(tower_cont));

    queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
    bishop->move(Position(0, 0), Position(7, 7));
    tower->move(Position(2, 6), Position(5, 3));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(7, 7, 0.5));
    EXPECT_TRUE(bishop->getPosition(1) == QuantumPosition(0, 0, 0.5));
    EXPECT_TRUE(tower->getPosition() == QuantumPosition(5, 3, 0.5));
    EXPECT_TRUE(tower->getPosition(1) == QuantumPosition(2, 6, 0.5));

    bishop->measure(Position(0, 0));

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(7, 7, 1));
    EXPECT_TRUE(bishop->getAllPositions().size() == 1);
    EXPECT_TRUE(tower->getPosition() == QuantumPosition(5, 3, 1));
    EXPECT_TRUE(tower->getAllPositions().size() == 1);
    EXPECT_TRUE(queen->getPosition() == QuantumPosition(4, 2, 1));
    EXPECT_TRUE(queen->getAllPositions().size() == 1);
}

TEST(Chessman, DoubleEntangleSamePiecesEntangleWithFakeMeasurenInitialFake){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(4, 3), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    ChessmanContainer tower_cont('B', Position(2, 6), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get(), * tower = tower_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));
    board.addChessman(std::move(tower_cont));

    queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
    bishop->move(Position(0, 0), Position(7, 7));

    EXPECT_THROW(bishop->move(Position(7, 7), Position(3, 3)), ChessException);
}

TEST(Chessman, SplitUntilReachLimit) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get();
    board.addChessman(std::move(queen_cont));

    queen->split(Position(0, 0), Position(0, 1), Position(0, 2));
    queen->split(Position(0, 2), Position(0, 3), Position(0, 4));
    queen->split(Position(0, 4), Position(0, 5), Position(0, 6));
    queen->split(Position(0, 6), Position(0, 7), Position(1, 7));
    queen->split(Position(1, 7), Position(1, 6), Position(1, 5));
    queen->split(Position(1, 5), Position(1, 4), Position(1, 3));
    queen->split(Position(1, 3), Position(1, 2), Position(1, 1));
    queen->split(Position(1, 1), Position(1, 0), Position(2, 0));
    queen->split(Position(2, 0), Position(2, 1), Position(2, 2));
    queen->split(Position(2, 2), Position(2, 3), Position(2, 4));
    queen->split(Position(2, 4), Position(2, 5), Position(2, 6));
    queen->split(Position(2, 6), Position(2, 7), Position(3, 7));
    queen->split(Position(3, 7), Position(3, 6), Position(3, 5));
    queen->split(Position(3, 5), Position(3, 4), Position(3, 3));
    queen->split(Position(3, 3), Position(3, 2), Position(3, 1));
    queen->split(Position(3, 1), Position(3, 0), Position(4, 0));

    EXPECT_THROW(queen->split(Position(4, 0), Position(4, 1), Position(4, 2)), ChessException);

    queen->measure(Position(0, 1));

    EXPECT_TRUE(queen->getPosition() == QuantumPosition(0, 1, 1));
    EXPECT_TRUE(queen->positionsSize() == 1);
}

TEST(Chessman, EntangleThenSplitThenMergeThenMeasure){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(4, 3), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
    bishop->move(Position(0, 0), Position(7, 7));

    bishop->split(Position(7, 7), Position(6, 6), Position(5, 5));
    bishop->merge(Position(6, 6), Position(5, 5), Position(6, 6));

    bishop->measure(Position(6, 6));

    EXPECT_TRUE(queen->getPosition() == QuantumPosition(4, 2, 1));
    EXPECT_TRUE(queen->positionsSize() == 1);

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(6, 6, 1));
    EXPECT_TRUE(bishop->positionsSize() == 1);
}

TEST(Chessman, EntangleThenSplitTHenMergeThenMeasure){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(4, 3), true, board);
    ChessmanContainer bishop_cont('B', Position(0, 0), true, board);
    Chessman * queen = queen_cont.get(), * bishop = bishop_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(bishop_cont));

    queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
    bishop->move(Position(0, 0), Position(7, 7));

    bishop->split(Position(7, 7), Position(6, 6), Position(5, 5));
    bishop->merge(Position(6, 6), Position(5, 5), Position(6, 6));

    bishop->measure(Position(6, 6));

    EXPECT_TRUE(queen->getPosition() == QuantumPosition(4, 2, 1));
    EXPECT_TRUE(queen->positionsSize() == 1);

    EXPECT_TRUE(bishop->getPosition() == QuantumPosition(6, 6, 1));
    EXPECT_TRUE(bishop->positionsSize() == 1);
}


TEST(Chessman, EntangleThenMergeOneEntangledOtherNonEntangledThenMeasureEntangled){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(0, 0), true, board);
    ChessmanContainer queen_2_cont('Q', Position(4, 3), true, board);
    Chessman * queen = queen_cont.get(), * queen_2 = queen_2_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(queen_2_cont));

    queen_2->split(Position(4, 3), Position(4, 2), Position(4, 4));
    queen->move(Position(0, 0), Position(7, 7));
    queen_2->move(Position(4, 4), Position(4, 5));


    queen->merge(Position(0, 0), Position(7, 7), Position(5, 5));


    EXPECT_TRUE(queen->getPosition() == QuantumPosition(5, 5, 1));

    queen->measure(Position(5, 5));

    std::cout << Position(queen->getPosition()) << std::endl;

    EXPECT_TRUE(queen->getPosition() == QuantumPosition(5, 5, 1));
    EXPECT_TRUE(queen->positionsSize() ==  1);
    EXPECT_TRUE(queen_2->getPosition() == QuantumPosition(4, 2, 0.5));
    EXPECT_TRUE(queen_2->getPosition(1) == QuantumPosition(4, 5, 0.5));
    EXPECT_TRUE(queen_2->positionsSize() ==  2);
}

TEST(Chessman, EntangleThenSplitThenMergeOneEntangledOtherNonEntangledThenMeasureEntangled){
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(0, 0), true, board);
    ChessmanContainer queen_2_cont('Q', Position(4, 3), true, board);
    Chessman * queen = queen_cont.get(), * queen_2 = queen_2_cont.get();

    board.addChessman(std::move(queen_cont));
    board.addChessman(std::move(queen_2_cont));

    queen_2->split(Position(4, 3), Position(4, 2), Position(4, 4));
    queen->move(Position(0, 0), Position(7, 7));
    queen_2->move(Position(4, 4), Position(4, 5));


    queen->split(Position(7, 7), Position(6, 6), Position(5, 5));
    queen->merge(Position(0, 0), Position(5, 5), Position(5, 5));


    EXPECT_TRUE(queen->getPosition() == QuantumPosition(6, 6, 0.25));
    EXPECT_TRUE(queen->getPosition(1) == QuantumPosition(5, 5, 0.75));

    queen->measure(Position(5, 5));

    EXPECT_TRUE(queen->getPosition() == QuantumPosition(6, 6, 1));
    EXPECT_TRUE(queen->positionsSize() ==  1);
    EXPECT_TRUE(queen_2->getPosition() == QuantumPosition(4, 2, 1));
    EXPECT_TRUE(queen_2->positionsSize() ==  1);
}

TEST(Chessman, EntangleWithItselfFails) {
    Board board(0);
    ChessmanContainer queen_cont('Q', Position(0, 0), true, board);
    Chessman *queen = queen_cont.get();

    board.addChessman(std::move(queen_cont));

    queen->split(Position(0, 0), Position(1, 1), Position(4, 4));

    EXPECT_THROW(queen->move(Position(1, 1), Position(5, 5)), ChessException);
}

// TODO ver que hacer cuando mergeas algo que tenia algo enlazado.


