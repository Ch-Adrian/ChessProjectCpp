#include "pch.h"
#include "Queen.h"
#include "Settings.h"

Queen::Queen(int type, int color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_queen.bmp";
	}
	else {
		this->image_source = "resources/black_queen.bmp";
	}
}

bool Queen::validate_move(IShareBoardData& share, const Move& move) {

	if (share.get_type(move.from) != QUEEN){
		return false;
	}

	for (Position p : this->get_available_positions(share, move.from)) {
		if (p == move.to) {
			return true;
		}
	}

	return false;
}

void increase_position_bishop_like(Position& next_position, int i) {

	switch (i % 4) {
		case 0: next_position.col += 1; next_position.row += -1; break;
		case 1: next_position.col += -1; next_position.row += -1; break;
		case 2: next_position.col += 1; next_position.row += 1; break;
		case 3: next_position.col += -1; next_position.row += 1; break;
	}
	
}

void increase_position_rook_like(Position& next_position, int i) {

		switch (i % 4) {
			case 0: next_position.row--; break;
			case 1: next_position.col++; break;
			case 2: next_position.row++; break;
			case 3: next_position.col--; break;
		}
}

std::vector<Position> Queen::get_available_positions(IShareBoardData& share, const Position& pos) {
	std::vector<Position> availablePositions;

	if (share.get_type(pos) != QUEEN){
		return availablePositions;
	}

	PlayerColor opponent_color = share.get_color(pos) == WHITE ? BLACK : WHITE;
	Position next_position(pos);

	for (int i = 0; i < 4; i++) {

		increase_position_bishop_like(next_position, i);
		while (position_inside_board(next_position) && share.get_piece(next_position) == nullptr) {
			availablePositions.push_back(next_position);
			increase_position_bishop_like(next_position, i);
		}

		if (position_inside_board(next_position) && share.get_color(next_position) == opponent_color) {
			availablePositions.push_back(next_position);
		}
		next_position = pos;

	}
	
	next_position = pos;
	for (int i = 0; i < 4; i++) {
		
		increase_position_rook_like(next_position, i);

		while (position_inside_board(next_position) && share.get_piece(next_position) == nullptr) {
			availablePositions.push_back(next_position);
			increase_position_rook_like(next_position, i);
		}

		if (position_inside_board(next_position) && share.get_color(next_position) == opponent_color) {
			availablePositions.push_back(next_position);
		}
		next_position = pos;

	}

	return availablePositions;
}

std::vector<Position> Queen::get_positions_under_attack(IShareBoardData& share, const Position& pos) {
	return this->get_available_positions(share, pos);
}

std::string Queen::get_image_source() {
	return this->image_source;
}



