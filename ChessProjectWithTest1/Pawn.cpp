#include "pch.h"
#include "Pawn.h"
#include "Settings.h"

Pawn::Pawn(int type, int color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_pawn.bmp";
	}
	else {
		this->image_source = "resources/black_pawn.bmp";
	}
}

bool Pawn::validate_move(const Move& move){
	return false;
}

std::vector<Position> Pawn::get_available_positions(const Position& pos) {
	std::vector<Position> emptyVector;
	return emptyVector;

}

std::string Pawn::get_image_source() {
	return this->image_source;
}





