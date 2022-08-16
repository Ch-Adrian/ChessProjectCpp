#include "pch.h"
#pragma once
#include "Move.h"
#include "Piece.h"
#include "IShareBoardData.h"

class CommonFunctions
{
public:

	static int convX_to_pixels(int pos);
	static int convX_to_position(int pix);
	static int convY_to_pixels(int pos);
	static int convY_to_position(int pix);
	static bool position_inside_board(const Position& pos);
};
