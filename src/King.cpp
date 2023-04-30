#include "pch.h"
#include "King.h"
#include "Settings.h"
#include <set>

King::King(PieceType type, PlayerColor color): Piece(type, color) {

	this->firstMove = false;

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

	std::vector<Position> vec = this->get_available_positions(share, move.from);
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

	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			Piece* piece2 = (share.get_array_board())[i][j];
			if (piece2 == nullptr || piece2->get_type() == KING) continue;

			if (piece2 != nullptr && piece2->get_color() == opponent_color) {
				for (Position p : piece2->get_positions_under_attack(share, Position(i, j))) {
					enemyMapPositions.insert(p);
					enemyPositions.push_back(p);
				}
			}
		}
	}

	Position next_position(pos);
	next_position.col--; next_position.row--;

	for (int i = 0; i < 8; i++) {

		bool cond0 = position_inside_board(next_position);
		bool cond1 = enemyMapPositions.find(next_position) == enemyMapPositions.end();
		bool cond2 = share.get_piece(next_position) == nullptr;
		bool cond3 = share.get_color(next_position) == opponent_color;


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

	if (this->firstMove == false) {

		bool threatened_left = false;
		bool threatened_right = false;

		bool free_space_left = false;
		bool free_space_right = false;


		Position pos_left(pos);
		Position pos_right(pos);
		
		while (position_inside_board(pos_left)) {
			if (enemyMapPositions.find(pos_left) != enemyMapPositions.end()) {
				threatened_left = true;
				break;
			}
			
			pos_left.col--;
		}
		
		while (position_inside_board(pos_right)) {
			if (enemyMapPositions.find(pos_right) != enemyMapPositions.end()) {
				threatened_right = true;
				break;
			}

			pos_right.col++;
		}

		Position check_blank_left(pos);
		if (share.get_type(check_blank_left) == PieceType::KING) {
			check_blank_left.col--;
			if (share.get_type(check_blank_left) == PieceType::NONE) {
				check_blank_left.col--;
				if (share.get_type(check_blank_left) == PieceType::NONE) {
					check_blank_left.col--;
					if (share.get_type(check_blank_left) == PieceType::LEFT_ROOK) {
						free_space_left = true;
					}
				}
			}
		}

		if (free_space_left && !threatened_left) {
			Position left_pos(pos);
			left_pos.col -= 2;
			availablePositions.push_back(left_pos);
		}
		
		
		Position check_blank_right(pos);
		if (share.get_type(check_blank_right) == PieceType::KING) {
			check_blank_right.col++;
			if (share.get_type(check_blank_right) == PieceType::NONE) {
				check_blank_right.col++;
				if (share.get_type(check_blank_right) == PieceType::NONE) {
					check_blank_right.col++;
					if (share.get_type(check_blank_right) == PieceType::NONE) {
						check_blank_right.col++;
						if (share.get_type(check_blank_right) == PieceType::RIGHT_ROOK) {
							free_space_right = true;
						}
					}
				}
			}
		}

		if (free_space_right && !threatened_right) {
			Position right_pos(pos);
			right_pos.col += 2;
			availablePositions.push_back(right_pos);
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

void King::make_first_move() {
	this->firstMove = true;
}

void King::undo_first_move() {
	this->firstMove = false;
}

