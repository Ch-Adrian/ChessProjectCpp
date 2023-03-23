#include "pch.h"
#include "Knight.h"
#include "Settings.h"

Knight::Knight(PieceType type, PlayerColor color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_knight.bmp";
	}
	else {
		this->image_source = "resources/black_knight.bmp";
	}
}

bool Knight::validate_move(IShareBoardData& share, const Move& move) {

	if (share.get_type(move.from) != LEFT_KNIGHT && share.get_type(move.from) != RIGHT_KNIGHT) {
		return false;
	}

	for (Position p : this->get_available_positions(share, move.from)) {
		if (p == move.to) {
			return true;
		}
	}

	return false;

}

std::vector<Position> Knight::get_available_positions(IShareBoardData& share, const Position& pos) {

	std::vector<Position> availablePositions;

	if (share.get_type(pos) != LEFT_KNIGHT && share.get_type(pos) != RIGHT_KNIGHT) {
		return availablePositions;
	}

	PlayerColor opponent_color = share.get_color(pos) == WHITE ? BLACK : WHITE;
	Position next_position(pos.col - 2, pos.row - 2);

	for (int i = 0; i <= 15; i++){


		if (i % 2) {
			if (position_inside_board(next_position)) {
				if (share.get_piece(next_position) == nullptr ||
					share.get_color(next_position) == opponent_color) {
					availablePositions.push_back(next_position);
				}
			}
		}

		switch (i / 4) {
		case 0:
			next_position.col++; break;
		case 1:
			next_position.row++; break;
		case 2:
			next_position.col--; break;
		case 3:
			next_position.row--; break;
		}
	
	}

	return availablePositions;

}

std::vector<Position> Knight::get_positions_under_attack(IShareBoardData& share, const Position& pos) {
	return this->get_available_positions(share, pos);
}

std::string Knight::get_image_source() {
	return this->image_source;
}






