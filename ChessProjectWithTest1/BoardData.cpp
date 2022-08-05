#include "pch.h"
#include "BoardData.h"


BoardData::BoardData() {
	this->board = std::map<std::pair<int, int>, std::pair<int, bool>>();
	
	//Pawns
	for (int i = 0; i < 8; i++) {
		this->board.insert({ std::make_pair(i + 1, 2), std::make_pair(PAWN, WHITE) });
	}

	for (int i = 0; i < 8; i++) {
		this->board.insert({ std::make_pair(i + 1, 7), std::make_pair(PAWN,BLACK) });
	}

	//Pieces
	
	this->board.insert({std::make_pair(1,1), std::make_pair(ROOK, WHITE)});
	this->board.insert({std::make_pair(2,1), std::make_pair(KNIGHT, WHITE)});
	this->board.insert({std::make_pair(3,1), std::make_pair(BISHOP, WHITE)});
	this->board.insert({std::make_pair(4,1), std::make_pair(KING, WHITE)});
	this->board.insert({std::make_pair(5,1), std::make_pair(QUEEN, WHITE)});
	this->board.insert({std::make_pair(6,1), std::make_pair(BISHOP, WHITE)});
	this->board.insert({std::make_pair(7,1), std::make_pair(KNIGHT, WHITE)});
	this->board.insert({std::make_pair(8,1), std::make_pair(ROOK, WHITE)});
	this->board.insert({std::make_pair(1,8), std::make_pair(ROOK, BLACK)});
	this->board.insert({std::make_pair(2,8), std::make_pair(KNIGHT, BLACK)});
	this->board.insert({std::make_pair(3,8), std::make_pair(BISHOP, BLACK)});
	this->board.insert({std::make_pair(4,8), std::make_pair(KING, BLACK)});
	this->board.insert({std::make_pair(5,8), std::make_pair(QUEEN, BLACK)});
	this->board.insert({std::make_pair(6,8), std::make_pair(BISHOP, BLACK)});
	this->board.insert({std::make_pair(7,8), std::make_pair(KNIGHT, BLACK)});
	this->board.insert({std::make_pair(8,8), std::make_pair(ROOK, BLACK)});


}

BoardData::BoardData(Field** board) {
	BoardData();
}

const std::map<std::pair<int, int>, std::pair<int, bool>> BoardData::get_board() {
	return this->board;
}

