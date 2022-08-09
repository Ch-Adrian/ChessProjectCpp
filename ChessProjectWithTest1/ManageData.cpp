#include "pch.h"
#include "ManageData.h"

bool ManageData::validate_move(std::map<std::pair<int, int>, Piece*> pieces, Move move) {

	auto piece_from = pieces[std::make_pair(move.from.col, move.from.row)];
	
	switch (piece_from->get_type()) {
			case KING: ; break;
			case QUEEN: ; break;
			case BISHOP: ; break;
			case KNIGHT: ; break;
			case ROOK: ; break;
			case PAWN: ; break;
			default:
				break;
		}
	return false;
}

