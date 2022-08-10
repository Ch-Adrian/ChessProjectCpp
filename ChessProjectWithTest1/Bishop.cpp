#include "pch.h"
#include "Bishop.h"
#include "Settings.h"

Bishop::Bishop(int type, int color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_bishop.bmp";
	}
	else {
		this->image_source = "resources/black_bishop.bmp";
	}
}

bool Bishop::validate_move(const Move& move){
	return false;
}

std::vector<Position> Bishop::get_available_positions(const Position& pos) {
	std::vector<Position> emptyVector;
	return emptyVector;

}

std::string Bishop::get_image_source() {
	return this->image_source;
}


