#include "pch.h"
#include "Bishop.h"
#include "Settings.h"

Bishop::Bishop(PieceType type, PlayerColor color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_bishop.bmp";
	}
	else {
		this->image_source = "resources/black_bishop.bmp";
	}
}

bool Bishop::validate_move(IShareBoardData& share, const Move& move){

	if (share.get_type(move.from) != LEFT_BISHOP && share.get_type(move.from) != RIGHT_BISHOP) {
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

void increase_position(Position& next_position, int i) {

	switch (i % 4) {
		case 0: next_position.col += 1; next_position.row += -1; break;
		case 1: next_position.col += -1; next_position.row += -1; break;
		case 2: next_position.col += 1; next_position.row += 1; break;
		case 3: next_position.col += -1; next_position.row += 1; break;
	}
	
}

std::vector<Position> Bishop::get_available_positions(IShareBoardData& share, const Position& pos) {
	std::vector<Position> availablePositions;

	if (share.get_type(pos) != LEFT_BISHOP && share.get_type(pos) != RIGHT_BISHOP) {
		return availablePositions;
	}
	//std::cout << "Initial pos bishop: " << std::endl;
	//std::cout << pos << std::endl;
	PlayerColor opponent_color = share.get_color(pos) == WHITE ? BLACK : WHITE;
	Position next_position(pos);

	for (int i = 0; i < 4; i++) {

		increase_position(next_position, i);
		while (position_inside_board(next_position) && share.get_piece(next_position) == nullptr) {
			//std::cout << next_position << std::endl;
			availablePositions.push_back(next_position);
			increase_position(next_position, i);
		}

		if (position_inside_board(next_position) && share.get_color(next_position) == opponent_color) {
			//std::cout << next_position << std::endl;
			availablePositions.push_back(next_position);
		}
		next_position = pos;

	}

	//std::cout << "Positions bishop: " << std::endl;
	//for (Position p : availablePositions) {
		//std::cout << p << std::endl;
	//}

	return availablePositions;
}

std::vector<Position> Bishop::get_positions_under_attack(IShareBoardData& share, const Position& pos) {
	return this->get_available_positions(share, pos);
}

std::string Bishop::get_image_source() {
	return this->image_source;
}


