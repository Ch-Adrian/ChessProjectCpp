#include "pch.h"
#include "BoardData.h"
#include "Settings.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Piece.h"
#include <math.h>
#include <iostream>

BoardData::BoardData() {

	this->board = std::map<Position, Piece*>();
	this->turn = PlayerColor::BLACK;
	this->kingsChecked = PlayerColor::EMPTY;

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

PieceType BoardData::get_type(const Position& pos) {
	if (pos.col <= 8 && pos.col >= 1 && pos.row <= 8 && pos.row >= 1) {
		if (this->board.find(Position(pos.col, pos.row)) != this->board.end())
			return this->board.at(Position(pos.col, pos.row))->get_type();

		//if (this->boardArray[pos.col][pos.row] != nullptr) {
			//return this->boardArray[pos.col][pos.row]->get_type();
		//}
	}
	return PieceType::NONE;
}

PlayerColor BoardData::get_color(const Position& pos) {
	if (pos.col <= 8 && pos.col >= 1 && pos.row <= 8 && pos.row >= 1) {
		if (this->board.find(Position(pos.col, pos.row)) != this->board.end())
			return this->board.at(Position(pos.col, pos.row))->get_color();

		//if(this->boardArray[pos.col][pos.row] != nullptr)
			//return this->boardArray[pos.col][pos.row]->get_color();
	}
	return PlayerColor::EMPTY;
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
						// std::cout << "en passant succeed" << std::endl;
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
						// std::cout << "en passant succeed" << std::endl;
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

void BoardData::exchange_pawn(PieceType type, PlayerColor color) {
	
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

bool BoardData::hasTurn(const Position& pos) {
	if (this->turn == this->get_color(pos)) {
		return true;
	}
	return false;
}

PlayerColor BoardData::getTurn() {
	return this->turn;
}

void BoardData::changeTurn() {
	if (this->turn == PlayerColor::BLACK) {
		this->turn = PlayerColor::WHITE;
	}
	else {
		this->turn = PlayerColor::BLACK;
	}
}


bool BoardData::checkKingChecked(PlayerColor color) {
	
	std::cout << "Checking king's position ... " << std::endl;
	Position* king_position = findKingPosition(color, this->board);
	if (king_position == nullptr) return false;
	std::cout << "Kings position: " << *king_position << std::endl;

	std::map<Position, Piece*>::iterator map_it;
	for (map_it = this->board.begin(); map_it != this->board.end(); map_it++) {
		Piece* piece = map_it->second;
		Position piece_pos = map_it->first;
		
		if (piece->get_color() == color) continue;

		for (Position pos : piece->get_positions_under_attack(*this, piece_pos)) {
			std::cout << "piece: " << *piece << " pos: " << pos << std::endl;
			if (pos == *king_position) {
				delete king_position;
				return true;
			}
		}

	}

	delete king_position;
	return false;
	
}

Position* BoardData::findKingPosition(PlayerColor color, std::map<Position, Piece*>& board) {

	std::map<Position, Piece*>::iterator map_it;
	for (map_it = board.begin(); map_it != board.end(); map_it++) {
		Piece* piece = map_it->second;
		Position* piece_pos = new Position(map_it->first);
		
		if (piece->get_type() == PieceType::KING && piece->get_color() == color){ 
			return piece_pos;
		}
		delete piece_pos;

	}
	return nullptr;
}

bool BoardData::checkKingIsThreatened() {

	if (this->checkKingChecked(PlayerColor::BLACK)) {
		this->kingsChecked = PlayerColor::BLACK;
		return true;
	}

	if (this->checkKingChecked(PlayerColor::WHITE)) {
		this->kingsChecked = PlayerColor::WHITE;
		return true;
	}

	return false;

}

PlayerColor BoardData::simulateKingIsReleased(Move move) {
	Position from(move.from.col, move.from.row);
	Position to(move.to.col, move.to.row);
	PlayerColor return_value = PlayerColor::EMPTY;

	Position* en_passant_top = nullptr;
	Piece* board_array_element_top = nullptr;
	Position* en_passant_bottom = nullptr;
	Piece* board_array_element_bottom = nullptr;

	bool pawn_first_move = false;
	bool pawn_double_move = false;
	Move pawn_double_move2;
	if (this->get_type(move.from) == PAWN) {

		((Pawn*)(this->get_piece(move.from)))->make_first_move();
		pawn_first_move = true;

		// double squre move
		if (abs(move.to.row - move.from.row) == 2) {
			pawn_double_move2 = this->pawn_double_move;
			this->pawn_double_move = move;
			pawn_double_move = true;
		}

		//en passant
		if (abs(move.to.col - move.from.col) == 1 &&
			this->get_piece(move.to) == nullptr) {
			if (this->get_color(move.from) == WHITE) {
				Piece* enemy = this->get_piece(Position(move.to.col, move.from.row));
				if (enemy != nullptr) {
					if (enemy->get_color() == BLACK &&
						enemy->get_type() == PAWN) {
						en_passant_top = new Position(move.to.col, move.from.row);
						// std::cout << "en passant succeed" << std::endl;

						board_array_element_top = boardArray[move.to.col][move.from.row];
						boardArray[move.to.col][move.from.row] = nullptr;
						board.erase(*en_passant_top);
					}
				}
			}
			else if(this->get_color(move.from) == BLACK) {
				Piece* enemy = this->get_piece(Position(move.to.col, move.from.row));
				if (enemy != nullptr) {
					if (enemy->get_color() == WHITE &&
						enemy->get_type() == PAWN) {
						en_passant_bottom = new Position(move.to.col, move.from.row);
						// std::cout << "en passant succeed" << std::endl;

						board_array_element_bottom = boardArray[move.to.col][move.from.row];
						boardArray[move.to.col][move.from.row] = nullptr;
						board.erase(*en_passant_bottom);
					}
				}

			}

		}

	}

	Piece* assulted_piece = boardArray[to.col][to.row];
	boardArray[to.col][to.row] = boardArray[from.col][from.row];
	boardArray[from.col][from.row] = nullptr;
	board.erase(Position(to));
	board.insert({ Position(to), boardArray[to.col][to.row] });
	board.erase(Position(from));

	//Move has been made.

	if (this->checkKingChecked(PlayerColor::BLACK)) {
		return_value = PlayerColor::BLACK;
	}else if( this->checkKingChecked(PlayerColor::WHITE) ) {
		return_value = PlayerColor::WHITE;
	}
	
	// revert changes
	if (en_passant_bottom != nullptr) {
		boardArray[(*en_passant_bottom).col][(*en_passant_bottom).row] = board_array_element_bottom;
		board.insert({ *en_passant_bottom, boardArray[(*en_passant_bottom).col][(*en_passant_bottom).row] });
	}

	if (en_passant_top != nullptr) {
		boardArray[(*en_passant_top).col][(*en_passant_top).row] = board_array_element_top;
		board.insert({ *en_passant_top, boardArray[(*en_passant_top).col][(*en_passant_top).row] });
	}

	board.erase(Position(to));
	board.erase(Position(from));
	board.insert({ Position(from), boardArray[to.col][to.row] });
	boardArray[from.col][from.row] = boardArray[to.col][to.row];
	boardArray[to.col][to.row] = assulted_piece;

	if (pawn_double_move) {
		this->pawn_double_move = pawn_double_move2;
	}

	if (pawn_first_move) {
		((Pawn*)(this->get_piece(move.from)))->undo_first_move();
	}
	return return_value;
}

void BoardData::unCheckKing() {
	this->kingsChecked = PlayerColor::EMPTY;
}

bool BoardData::isKingChecked() {
	return PlayerColor::EMPTY != this->kingsChecked;
}


PlayerColor BoardData::colorOfCheckedKing() {
	return this->kingsChecked;
}
