#include "pch.h"
#include "Pawn.h"
#include "Settings.h"

Pawn::Pawn(PieceType type, PlayerColor color): Piece(type, color) {

	this->firstMove = true;
	if (color == WHITE) {
		this->image_source = "resources/white_pawn.bmp";
	}
	else {
		this->image_source = "resources/black_pawn.bmp";
	}
}

bool Pawn::validate_move(IShareBoardData& share, const Move& move){

	if (share.get_type(move.from) != PAWN){
		return false;
	}

	for (Position p : this->get_available_positions(share, move.from)) {
		if (p == move.to) {
			return true;
		}
	}

	return false;
}

std::vector<Position> Pawn::get_available_positions(IShareBoardData& share, const Position& pos) {
	std::vector<Position> availablePositions;

	if (share.get_type(pos) != PAWN) {
		return availablePositions;
	}
	
	//std::cout << "pawn color: " << share.get_color(pos) << std::endl;

	if (share.get_color(pos) == WHITE) {

		//std::cout << "pawn white" << std::endl;
		// going forward
		if (position_inside_board(Position(pos.col, pos.row + 1)) && 
			share.get_piece(Position(pos.col, pos.row + 1)) == nullptr) {
			availablePositions.push_back(Position(pos.col, pos.row + 1));
			if (position_inside_board(Position(pos.col, pos.row + 2)) && 
				firstMove && share.get_piece(Position(pos.col, pos.row + 2)) == nullptr) {
				availablePositions.push_back(Position(pos.col, pos.row + 2));
			}
		}
		
		// assult
		if (position_inside_board(Position(pos.col - 1, pos.row + 1)) && 
			share.get_color(Position(pos.col - 1, pos.row + 1)) == BLACK) {
			availablePositions.push_back(Position(pos.col - 1, pos.row + 1));
		}
		if (position_inside_board(Position(pos.col + 1, pos.row + 1)) && 
			share.get_color(Position(pos.col + 1, pos.row + 1)) == BLACK) {
			availablePositions.push_back(Position(pos.col + 1, pos.row + 1));
		}

		// en passant
		std::cout << "en passant " << std::endl;
		if (!share.get_last_pawn_move().isEmpty()) {
			std::cout << "last pawn move is not empty " << std::endl;
			if (share.get_color(share.get_last_pawn_move().to) == BLACK) {
				std::cout << "get color: black " << std::endl;
				if (share.get_last_pawn_move().to.row == pos.row) {
					std::cout << "rows are equal " << std::endl;
					Position next_position(share.get_last_pawn_move().to.col, share.get_last_pawn_move().to.row + 1);
					if (share.get_piece(next_position) == nullptr) {
						std::cout << "next position is accessible" << std::endl;
						if (share.get_last_pawn_move().to.col - 1 == pos.col || 
							share.get_last_pawn_move().to.col + 1 == pos.col) {
							std::cout << "columns differ by one" << std::endl;
							availablePositions.push_back(next_position);
						}
					}
				}
			}
		}

	}
	else if(share.get_color(pos) == BLACK) {

		//std::cout << "black pawn" << std::endl;
		if (position_inside_board(Position(pos.col, pos.row - 1)) && 
			share.get_piece(Position(pos.col, pos.row - 1)) == nullptr) {
			availablePositions.push_back(Position(pos.col, pos.row - 1));
			if (position_inside_board(Position(pos.col, pos.row - 1)) && 
				firstMove && share.get_piece(Position(pos.col, pos.row - 2)) == nullptr) {
				availablePositions.push_back(Position(pos.col, pos.row - 2));
			}
		}
		//std::cout << "black assault" << std::endl;

		if (position_inside_board(Position(pos.col - 1, pos.row - 1)) && 
			share.get_color(Position(pos.col - 1, pos.row - 1)) == WHITE) {
			availablePositions.push_back(Position(pos.col - 1, pos.row - 1));
		}
		if (position_inside_board(Position(pos.col + 1, pos.row - 1)) && 
			share.get_color(Position(pos.col + 1, pos.row - 1)) == WHITE) {
			availablePositions.push_back(Position(pos.col + 1, pos.row - 1));
		}

		//std::cout << "black en passant " << std::endl;

		// en passant
		if (!share.get_last_pawn_move().isEmpty()) {
			if (share.get_color(share.get_last_pawn_move().to) == WHITE) {
				if (share.get_last_pawn_move().to.row == pos.row) {
					Position next_position(share.get_last_pawn_move().to.col, share.get_last_pawn_move().to.row - 1);
					if (share.get_piece(next_position) == nullptr) {
						if (share.get_last_pawn_move().to.col - 1 == pos.col || 
							share.get_last_pawn_move().to.col + 1 == pos.col) {
							availablePositions.push_back(next_position);
						}
					}
				}
			}
		}



	}

	//std::cout << "Showing available positions for pawn: " << std::endl;
	//for (Position p : availablePositions) {
		//std::cout << "pos: " << p.col << ", " << p.row << std::endl;
	//}

	return availablePositions;

}

std::vector<Position> Pawn::get_positions_under_attack(IShareBoardData& share, const Position& pos) {
	std::vector<Position> availablePositions;

	if (share.get_type(pos) != PAWN) {
		return availablePositions;
	}
	
	//std::cout << "pawn color: " << share.get_color(pos) << std::endl;

	if (share.get_color(pos) == WHITE) {
		
		// assult
		if (position_inside_board(Position(pos.col - 1, pos.row + 1))) {
			availablePositions.push_back(Position(pos.col - 1, pos.row + 1));
		}
		if (position_inside_board(Position(pos.col + 1, pos.row + 1))) {
			availablePositions.push_back(Position(pos.col + 1, pos.row + 1));
		}
	}
	else if(share.get_color(pos) == BLACK) {
		if (position_inside_board(Position(pos.col - 1, pos.row - 1))) {
			availablePositions.push_back(Position(pos.col - 1, pos.row - 1));
		}
		if (position_inside_board(Position(pos.col + 1, pos.row - 1))) {
			availablePositions.push_back(Position(pos.col + 1, pos.row - 1));
		}
	}
	
	std::cout << "Showing positions under attack for pawn: " << std::endl;
	for (Position p : availablePositions) {
		std::cout << "pos: " << p.col << ", " << p.row << std::endl;
	}

	return availablePositions;
}

std::string Pawn::get_image_source() {
	return this->image_source;
}

void Pawn::make_first_move() {
	this->firstMove = false;
}