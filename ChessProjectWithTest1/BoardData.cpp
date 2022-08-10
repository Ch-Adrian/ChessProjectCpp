#include "pch.h"
#include "BoardData.h"
#include "Settings.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include <math.h>

BoardData::BoardData() {

	this->board = std::map<Position, Piece*>();
	
	boardArray = new Piece ** [9];
	for (int i = 0; i <= 8; i++) {
		boardArray[i] = new Piece*[9];
		for (int j = 0; j < 9; j++) {
			boardArray[i][j] = nullptr;
		}
	}

	white_pieces.push_back(new Rook(LEFT_ROOK, WHITE));
	white_pieces.push_back(new Knight(LEFT_KNIGHT, WHITE));
	white_pieces.push_back(new Bishop(LEFT_BISHOP, WHITE));
	white_pieces.push_back(new King(KING, WHITE));
	white_pieces.push_back(new Queen(QUEEN, WHITE));
	white_pieces.push_back(new Bishop(RIGHT_BISHOP, WHITE));
	white_pieces.push_back(new Knight(RIGHT_KNIGHT, WHITE));
	white_pieces.push_back(new Rook(RIGHT_ROOK, WHITE));

	black_pieces.push_back(new Rook(LEFT_ROOK, BLACK));
	black_pieces.push_back(new Knight(LEFT_KNIGHT, BLACK));
	black_pieces.push_back(new Bishop(LEFT_BISHOP, BLACK));
	black_pieces.push_back(new King(KING, BLACK));
	black_pieces.push_back(new Queen(QUEEN, BLACK));
	black_pieces.push_back(new Bishop(RIGHT_BISHOP, BLACK));
	black_pieces.push_back(new Knight(RIGHT_KNIGHT, BLACK));
	black_pieces.push_back(new Rook(RIGHT_ROOK, BLACK));



	//Pawns
	for (int i = 0; i < 8; i++) {
		white_pieces.push_back(new Pawn(PAWN, WHITE));
		boardArray[i + 1][2] = white_pieces.back();
	}

	for (int i = 0; i < 8; i++) {
		black_pieces.push_back(new Pawn(PAWN, BLACK));
		boardArray[i + 1][7] = black_pieces.back();
	}
					
	//Pieces

	boardArray[1][1] = white_pieces.at(LEFT_ROOK);
	boardArray[2][1] = white_pieces.at(LEFT_KNIGHT);
	boardArray[3][1] = white_pieces.at(LEFT_BISHOP);
	boardArray[4][1] = white_pieces.at(KING);
	boardArray[5][1] = white_pieces.at(QUEEN);
	boardArray[6][1] = white_pieces.at(RIGHT_BISHOP);
	boardArray[7][1] = white_pieces.at(RIGHT_KNIGHT);
	boardArray[8][1] = white_pieces.at(RIGHT_ROOK);

	boardArray[1][8] = black_pieces.at(LEFT_ROOK);
	boardArray[2][8] = black_pieces.at(LEFT_KNIGHT);
	boardArray[3][8] = black_pieces.at(LEFT_BISHOP);
	boardArray[4][8] = black_pieces.at(KING);
	boardArray[5][8] = black_pieces.at(QUEEN);
	boardArray[6][8] = black_pieces.at(RIGHT_BISHOP);
	boardArray[7][8] = black_pieces.at(RIGHT_KNIGHT);
	boardArray[8][8] = black_pieces.at(RIGHT_ROOK);

	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (boardArray[i][j] != nullptr) {
				this->board.insert({ Position(i,j), boardArray[i][j] });
			}
		}
	}
}

BoardData::~BoardData() {
	for (Piece* white : white_pieces) {
		delete white;
	}
	for (Piece* black : black_pieces) {
		delete black;
	}
	for (int i = 0; i < 9; i++) {
		delete[] boardArray[i];
	}
	delete[] boardArray;
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

void BoardData::move_piece(const Move& move) {
	Position from(move.from.col, move.from.row);
	Position to(move.to.col, move.to.row);
	this->board[to] = this->board[from];
	this->board.erase(from);
	
	boardArray[to.col][to.row] = boardArray[from.col][from.row];
	boardArray[from.col][from.row] = nullptr;

	if (this->get_type(move.from) == PAWN) {
		if (abs(move.to.row - move.from.row) == 2) {
			this->pawn_double_move = move;
		}
	}
	else {
		this->pawn_double_move = Move();
	}

}

bool BoardData::validate_move(const Move& move) {
	Piece* moving_piece = this->get_piece(move.from);

	switch (this->get_type(move.from)) {
	case KING: moving_piece->validate_move(move); moving_piece->validate_move(move);  break;
		case QUEEN: moving_piece->validate_move(move); break;
		case LEFT_BISHOP: moving_piece->validate_move(move); 
		case RIGHT_BISHOP: moving_piece->validate_move(move); break;
		case LEFT_KNIGHT: moving_piece->validate_move(move); 
		case RIGHT_KNIGHT: moving_piece->validate_move(move); break;
		case LEFT_ROOK: moving_piece->validate_move(move); 
		case RIGHT_ROOK: moving_piece->validate_move(move); break;
		case PAWN: moving_piece->validate_move(move); break;
		default: return false;
	}
}

