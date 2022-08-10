#include "pch.h"
#include "Knight.h"
#include "Settings.h"

Knight::Knight(int type, int color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_knight.bmp";
	}
	else {
		this->image_source = "resources/black_knight.bmp";
	}
}

bool Knight::validate_move(const Move& move){
	return false;
}

std::vector<Position> Knight::get_available_positions(const Position& pos) {
	std::vector<Position> emptyVector;
	return emptyVector;

}

std::string Knight::get_image_source() {
	return this->image_source;
}






