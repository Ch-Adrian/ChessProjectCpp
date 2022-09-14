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

	for (int i = 0; i < white_pieces.size(); i++) {
		white_pieces[i]->set_id(i);
	}

	for (int i = 0; i < black_pieces.size(); i++) {
		black_pieces[i]->set_id(i + white_pieces.size());
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

	for (Piece* addit : additional_pieces) {
		delete addit;
	}

	for (int i = 0; i < 9; i++) {
		delete[] boardArray[i];
	}
	delete[] boardArray;
}

const std::map<Position, Piece*> BoardData::get_board() {
	return this->board;
}

Piece*** BoardData::get_array_board() {
	return this->boardArray;
}

Piece* BoardData::get_piece(const Position& pos) {
	if (pos.col <= 8 && pos.col >= 1 && pos.row <= 8 && pos.row >= 1)
		if (this->board.find(Position(pos.col, pos.row)) != this->board.end())
			return this->board.at(Position(pos.col, pos.row));

		//if (this->boardArray[pos.col][pos.row] != nullptr)
			//return nullptr;
			//return this->boardArray[pos.col][pos.row];
	return nullptr;
}

int BoardData::get_type(const Position& pos) {
	if (pos.col <= 8 && pos.col >= 1 && pos.row <= 8 && pos.row >= 1) {
		if (this->board.find(Position(pos.col, pos.row)) != this->board.end())
			return this->board.at(Position(pos.col, pos.row))->get_type();

		//if (this->boardArray[pos.col][pos.row] != nullptr) {
			//return this->boardArray[pos.col][pos.row]->get_type();
		//}
	}
	return -1;
}

 int BoardData::get_color(const Position& pos) {
	if (pos.col <= 8 && pos.col >= 1 && pos.row <= 8 && pos.row >= 1) {
		if (this->board.find(Position(pos.col, pos.row)) != this->board.end())
			return this->board.at(Position(pos.col, pos.row))->get_color();

		//if(this->boardArray[pos.col][pos.row] != nullptr)
			//return this->boardArray[pos.col][pos.row]->get_color();
	}
	return -1;
}

int BoardData::move_piece(const Move& move) {
	Position from(move.from.col, move.from.row);
	Position to(move.to.col, move.to.row);
	
	int return_value = 0;
	if (this->get_type(move.from) == PAWN) {

		((Pawn*)(this->get_piece(move.from)))->make_first_move();

		// double squre move
		if (abs(move.to.row - move.from.row) == 2) {
			this->pawn_double_move = move;
		}

		//en passant
		if (abs(move.to.col - move.from.col) == 1 &&
			this->get_piece(move.to) == nullptr) {
			if (this->get_color(move.from) == WHITE) {
				Piece* enemy = this->get_piece(Position(move.to.col, move.from.row));
				if (enemy != nullptr) {
					if (enemy->get_color() == BLACK &&
						enemy->get_type() == PAWN) {
						std::cout << "en passant succeed" << std::endl;
						boardArray[move.to.col][move.from.row] = nullptr;
						board.erase(Position(move.to.col, move.from.row));
					}
				}
			}
			else if(this->get_color(move.from) == BLACK) {
				Piece* enemy = this->get_piece(Position(move.to.col, move.from.row));
				if (enemy != nullptr) {
					if (enemy->get_color() == WHITE &&
						enemy->get_type() == PAWN) {
						std::cout << "en passant succeed" << std::endl;
						boardArray[move.to.col][move.from.row] = nullptr;
						board.erase(Position(move.to.col, move.from.row));
					}
				}

			}

		}

		if (this->get_color(move.from) == BLACK && move.to.row == 1) {
			this->edge_pawn_position = move.to;
			return_value = PAWN_TOP;
		}
		else if (this->get_color(move.from) == WHITE && move.to.row == 8) {
			this->edge_pawn_position = move.to;
			return_value = PAWN_BOTTOM;
		}

	}
	else {
		if(!this->pawn_double_move.isEmpty())
			this->pawn_double_move = Move();
	}

	boardArray[to.col][to.row] = boardArray[from.col][from.row];
	boardArray[from.col][from.row] = nullptr;
	board.erase(Position(to));
	board.insert({ Position(to), boardArray[to.col][to.row] });
	board.erase(Position(from));

	return return_value;

}

void BoardData::exchange_pawn(int type, bool color) {
	
	switch (type) {
	case QUEEN: 
			additional_pieces.push_back(new Queen(QUEEN, color));
		break;
	case LEFT_KNIGHT:
			additional_pieces.push_back(new Knight(LEFT_KNIGHT, color));
		break;
	case RIGHT_KNIGHT:
			additional_pieces.push_back(new Knight(RIGHT_KNIGHT, color));
		break;
	default:
		return;
	}

	for (int i = 0; i < additional_pieces.size(); i++) {
		additional_pieces[i]->set_id(black_pieces.back()->get_id() + i + 1);
	}
	
	this->boardArray[this->edge_pawn_position.col][this->edge_pawn_position.row] = additional_pieces.back();
	this->board.erase(Position(edge_pawn_position));
	this->board.insert({ Position(edge_pawn_position), additional_pieces.back() });

}

bool BoardData::validate_move( const Move& move) {
	Piece* moving_piece = this->get_piece(move.from);

	if (moving_piece == nullptr) return false;
	return moving_piece->validate_move(*this, move);

}

std::vector<Position> BoardData::get_all_available_positions(const Position& pos) {
	Piece* moving_piece = this->get_piece(pos);

	std::vector<Position> available_positions;
		
	if (moving_piece == nullptr) return available_positions;
	available_positions = moving_piece->get_available_positions(*this, pos);

	return available_positions;
	
}

const Move& BoardData::get_last_pawn_move() {
	return this->pawn_double_move;
}

const std::vector<Piece*> BoardData::get_one_side_pieces(PlayerColor side) {

	if (side == BLACK) {
		return this->black_pieces;
	}
	else {
		return this->white_pieces;
	}

}
