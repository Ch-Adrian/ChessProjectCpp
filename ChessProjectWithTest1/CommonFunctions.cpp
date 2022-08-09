#include "pch.h"
#include "CommonFunctions.h"
#include "Settings.h"

bool CommonFunctions::validate_move(IShareBoardData* iShare, Move* move){ 
	
	int piece_type = iShare->get_type(Position(move->from.col, move->from.row));

	switch (piece_type) {
	case KING: return king_move(iShare, move);
		break;
	case QUEEN: return queen_move(iShare, move);
		break;
	case BISHOP:  return bishop_move(iShare, move);
		break;	
	case KNIGHT:  return knight_move(iShare, move);
		break;
	case ROOK:	return rook_move(iShare, move);
		break;
	case PAWN:	return pawn_move(iShare, move);
		break;
	default:	return false;
		break;
	}

	return false; 
}

int CommonFunctions::convX_to_pixels(int pos){
	return 25+(pos-1)*FIELD_WIDTH;
}
int CommonFunctions::convX_to_position(int pix){
	return (pix-25)/FIELD_WIDTH + 1;
}
int CommonFunctions::convY_to_pixels(int pos){
	return 25*(pos-1)*FIELD_HEIGHT;
}
int CommonFunctions::convY_to_position(int pix){
	return (pix-25)/FIELD_HEIGHT + 1;
}


bool CommonFunctions::king_move(IShareBoardData* iShare, Move* move){ 
	int from_x = move->from.col;
	int from_y = move->from.row;
	int to_x = move->to.col;
	int to_y = move->to.row;

	if (to_x - from_x <= 1 && to_x - from_x >= -1) {
		if (to_y - from_y <= 1 && to_y - from_y >= -1) {
			
		}
	}
	
	

	return false; 
}

bool CommonFunctions::queen_move(IShareBoardData* iShare, Move* move){
	int from_x = move->from.col;
	int from_y = move->from.row;
	int to_x = move->to.col;
	int to_y = move->to.row; 

	if (king_move(iShare, move)) return true;

	return false;
}
bool CommonFunctions::bishop_move(IShareBoardData* iShare, Move* move){
	int from_x = move->from.col;
	int from_y = move->from.row;
	int to_x = move->to.col;
	int to_y = move->to.row;



	return false;

}
bool CommonFunctions::knight_move(IShareBoardData* iShare, Move* move){ 
	int from_x = move->from.col;
	int from_y = move->from.row;
	int to_x = move->to.col;
	int to_y = move->to.row; 
	return false;
}

bool CommonFunctions::rook_move(IShareBoardData* iShare, Move* move){ 
	int from_x = move->from.col;
	int from_y = move->from.row;
	int to_x = move->to.col;
	int to_y = move->to.row; 
	return false;
}

bool CommonFunctions::pawn_move(IShareBoardData* iShare, Move* move){ 
	int from_x = move->from.col;
	int from_y = move->from.row;
	int to_x = move->to.col;
	int to_y = move->to.row; 
	return false;
}

