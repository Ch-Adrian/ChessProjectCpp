#include "pch.h"
#include "King.h"
#include "Settings.h"

King::King(int type, int color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_king.bmp";
	}
	else {
		this->image_source = "resources/black_king.bmp";
	}
}

bool King::validate_move(IShareBoardData& share, const Move& move){

	if (share.get_type(move.from) != KING) {
		return false;
	}

	std::vector<Position>& vec = this->get_available_positions(share, move.from);
	for (Position p : vec) {
		if (p == move.to) {
			return true;
		}
	}

	return false;
}

std::vector<Position> King::get_available_positions(IShareBoardData& share, const Position& pos) {
	std::vector<Position> availablePositions;

	if (share.get_type(pos) != KING) {
		return availablePositions;
	}

	std::vector<Position> enemyPositions;
	std::set<Position> enemyMapPositions;

	PlayerColor opponent_color = share.get_color(pos) == WHITE ? BLACK : WHITE;

/*
	for (Piece* p : share.get_one_side_pieces(opponent_color) ){
		for (Position pos : p->get_available_positions(share, p->)) {
			enemyPositions.push_back(pos);
		}
	}
*/

	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			Piece* piece = (share.get_board()).at(Position(i, j));
			if (piece != nullptr && piece->get_color() == opponent_color) {
				for (Position p : piece->get_available_positions(share, Position(i, j))) {
					enemyMapPositions.insert(Position(i, j));
					enemyPositions.push_back(Position(i, j));
				}
			}
		}
	}

	Position next_position(pos);
	next_position.col--; next_position.row--;

	for (int i = 0; i < 8; i++) {
	
		if (enemyMapPositions.find(next_position) == enemyMapPositions.end()) {
			if (share.get_piece(next_position) == nullptr ||
				share.get_color(next_position) == opponent_color) {
				availablePositions.push_back(next_position);
			}
		}

		switch (i / 2) {
			case 0: next_position.col++; break;
			case 1: next_position.row++; break;
			case 2: next_position.col--; break;
			case 3: next_position.row--; break;
		}

	}

	return availablePositions;
}

std::string King::get_image_source() {
	return this->image_source;
}

bool King::checkmate() {
	return false;
}


