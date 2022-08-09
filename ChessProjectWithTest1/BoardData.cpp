#include "pch.h"
#include "BoardData.h"
#include "Settings.h"


BoardData::BoardData() {
	this->board = std::map<Position, Piece*>();
	
	//Pawns
	for (int i = 0; i < 8; i++) {
		this->board.insert({ Position(i + 1, 2), new Piece(PAWN, WHITE) });
	}

	for (int i = 0; i < 8; i++) {
		this->board.insert({ Position(i + 1, 7), new Piece(PAWN,BLACK) });
	}
					
	//Pieces
									
	this->board.insert({Position(1,1), new Piece(ROOK, WHITE)});
	this->board.insert({Position(2,1), new Piece(KNIGHT, WHITE)});
	this->board.insert({Position(3,1), new Piece(BISHOP, WHITE)});
	this->board.insert({Position(4,1), new Piece(KING, WHITE)});
	this->board.insert({Position(5,1), new Piece(QUEEN, WHITE)});
	this->board.insert({Position(6,1), new Piece(BISHOP, WHITE)});
	this->board.insert({Position(7,1), new Piece(KNIGHT, WHITE)});
	this->board.insert({Position(8,1), new Piece(ROOK, WHITE)});
	this->board.insert({Position(1,8), new Piece(ROOK, BLACK)});
	this->board.insert({Position(2,8), new Piece(KNIGHT, BLACK)});
	this->board.insert({Position(3,8), new Piece(BISHOP, BLACK)});
	this->board.insert({Position(4,8), new Piece(KING, BLACK)});
	this->board.insert({Position(5,8), new Piece(QUEEN, BLACK)});
	this->board.insert({Position(6,8), new Piece(BISHOP, BLACK)});
	this->board.insert({Position(7,8), new Piece(KNIGHT, BLACK)});
	this->board.insert({Position(8,8), new Piece(ROOK, BLACK)});


}

const std::map<Position, Piece*> BoardData::get_board() {
	return this->board;
}

Piece* BoardData::get_piece(const Position& pos) {
	return this->board[pos];
}

int BoardData::get_type(const Position& pos) {
	return this->board[pos]->get_type();
}

int BoardData::get_color(const Position& pos) {
	return this->board[pos]->get_type();
}

void BoardData::move_piece(Move move) {
	Position from(move.from.col, move.from.row);
	Position to(move.to.col, move.to.row);
	this->board[to] = this->board[from];
	this->board.erase(from);
}

