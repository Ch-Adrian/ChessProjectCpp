#pragma once
#include "Field.h"

enum Piece { EMPTY, KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN };
enum PlayerColor { WHITE = false, BLACK = true};

class BoardData
{
private:
	std::map<std::pair<int, int>, std::pair<int, bool>> board;

public:

	BoardData();
	BoardData(Field** board);
	const std::map<std::pair<int, int>, std::pair<int, bool>> get_board();

};

