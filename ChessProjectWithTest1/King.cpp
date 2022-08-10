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

bool King::validate_move(const Move& move){
	return false;
}

std::vector<Position> King::get_available_positions(const Position& pos) {
	std::vector<Position> emptyVector;
	return emptyVector;

}

std::string King::get_image_source() {
	return this->image_source;
}

bool King::checkmate() {
	return false;
}


