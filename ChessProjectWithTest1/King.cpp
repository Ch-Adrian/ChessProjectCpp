#include "pch.h"
#include "King.h"
#include "Settings.h"
#include "CommonFunctions.h"

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
			//Piece* piece = (share.get_board()).at(Position(i, j));
			Piece* piece2 = (share.get_array_board())[i][j];
			if (piece2 == nullptr || piece2->get_type() == KING) continue;
			std::cout << "piece found at " << i << ", "<< j << ": " << piece2->get_color() << std::endl;

			if (piece2 != nullptr && piece2->get_color() == opponent_color) {
				std::cout << "stage2" << std::endl;
				for (Position p : piece2->get_positions_under_attack(share, Position(i, j))) {
				std::cout << "stage3" << std::endl;
					std::cout << p << std::endl;
					enemyMapPositions.insert(p);
					enemyPositions.push_back(p);
				}
			}
		}
	}

	Position next_position(pos);
	next_position.col--; next_position.row--;

	std::cout << "King positions: " << std::endl;
	for (Position p : enemyMapPositions) {
		std::cout << p << std::endl;
	}

	for (int i = 0; i < 8; i++) {
		std::cout << "Next Position king: " << next_position << std::endl;

		bool cond0 = CommonFunctions::position_inside_board(next_position);
		bool cond1 = enemyMapPositions.find(next_position) == enemyMapPositions.end();
		bool cond2 = share.get_piece(next_position) == nullptr;
		bool cond3 = share.get_color(next_position) == opponent_color;

		std::cout << "Condition: " << cond0 << " " << cond1 << " " << cond2 << " " << cond3 << " " << ((cond0 && cond1 && (cond2 || cond3)) ? "true" : "false") << std::endl;

		if(cond0 && cond1){
			if(cond2 || cond3){
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

std::vector<Position> King::get_positions_under_attack(IShareBoardData& share, const Position& pos) {
	return this->get_available_positions(share, pos);
}

std::string King::get_image_source() {
	return this->image_source;
}

bool King::checkmate() {
	return false;
}


