#pragma once
#include "Field.h"
#include "Piece.h"

class BoardData
{
private:
	std::map<std::pair<int, int>, Piece*> board;

public:

	BoardData();
	BoardData(Field** board);
	const std::map<std::pair<int, int>, Piece*> get_board();

};

