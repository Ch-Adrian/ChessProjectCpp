#include "pch.h"
#include "ManageData.h"

bool ManageData::validate_move(std::map<std::pair<int, int>, Piece*> pieces, Move move) {

	auto piece_from = pieces[std::make_pair(move.from->x, move.from->y)];
	
	switch (piece_from->get_type()) {
			case KING: image_source = "resources/white_king.bmp";  break;
			case QUEEN:image_source = "resources/white_queen.bmp";break;
			case BISHOP:image_source = "resources/white_bishop.bmp";break;
			case KNIGHT:image_source = "resources/white_knight.bmp";break;
			case ROOK:image_source = "resources/white_rook.bmp";break;
			case PAWN:image_source = "resources/white_pawn.bmp";break;
			default:
				break;
		}
	}

}

