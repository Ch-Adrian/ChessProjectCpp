#include "pch.h"
#pragma once
#include "Move.h"
#include "Piece.h"
#include "IShareBoardData.h"

class CommonFunctions
{
public:

	static bool validate_move(IShareBoardData* iShare, Move* move);
	static int convX_to_pixels(int pos);
	static int convX_to_position(int pix);
	static int convY_to_pixels(int pos);
	static int convY_to_position(int pix);

private:

	static bool king_move(IShareBoardData* iShare, Move* move);
	static bool queen_move(IShareBoardData* iShare, Move* move);
	static bool bishop_move(IShareBoardData* iShare, Move* move);
	static bool knight_move(IShareBoardData* iShare, Move* move);
	static bool rook_move(IShareBoardData* iShare, Move* move);
	static bool pawn_move(IShareBoardData* iShare, Move* move);
};

