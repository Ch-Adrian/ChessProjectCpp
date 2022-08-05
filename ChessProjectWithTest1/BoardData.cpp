#include "pch.h"
#include "BoardData.h"
#include "Settings.h"


BoardData::BoardData() {
	this->board = std::map<std::pair<int, int>, Piece*>();
	
	//Pawns
	for (int i = 0; i < 8; i++) {
		this->board.insert({ std::make_pair(i + 1, 2), new Piece(PAWN, WHITE) });
	}

	for (int i = 0; i < 8; i++) {
		this->board.insert({ std::make_pair(i + 1, 7), new Piece(PAWN,BLACK) });
	}
					
	//Pieces
									
	this->board.insert({std::make_pair(1,1), new Piece(ROOK, WHITE)});
	this->board.insert({std::make_pair(2,1), new Piece(KNIGHT, WHITE)});
	this->board.insert({std::make_pair(3,1), new Piece(BISHOP, WHITE)});
	this->board.insert({std::make_pair(4,1), new Piece(KING, WHITE)});
	this->board.insert({std::make_pair(5,1), new Piece(QUEEN, WHITE)});
	this->board.insert({std::make_pair(6,1), new Piece(BISHOP, WHITE)});
	this->board.insert({std::make_pair(7,1), new Piece(KNIGHT, WHITE)});
	this->board.insert({std::make_pair(8,1), new Piece(ROOK, WHITE)});
	this->board.insert({std::make_pair(1,8), new Piece(ROOK, BLACK)});
	this->board.insert({std::make_pair(2,8), new Piece(KNIGHT, BLACK)});
	this->board.insert({std::make_pair(3,8), new Piece(BISHOP, BLACK)});
	this->board.insert({std::make_pair(4,8), new Piece(KING, BLACK)});
	this->board.insert({std::make_pair(5,8), new Piece(QUEEN, BLACK)});
	this->board.insert({std::make_pair(6,8), new Piece(BISHOP, BLACK)});
	this->board.insert({std::make_pair(7,8), new Piece(KNIGHT, BLACK)});
	this->board.insert({std::make_pair(8,8), new Piece(ROOK, BLACK)});


}

BoardData::BoardData(Field** board) {
	BoardData();
}

const std::map<std::pair<int, int>, Piece*> BoardData::get_board() {
	return this->board;
}

