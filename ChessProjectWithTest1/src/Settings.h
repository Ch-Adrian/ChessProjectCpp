#pragma once

enum PieceType {
	LEFT_ROOK, LEFT_KNIGHT, LEFT_BISHOP,
	KING, QUEEN, RIGHT_BISHOP,
	RIGHT_KNIGHT, RIGHT_ROOK, PAWN, NONE
};

enum PlayerColor { WHITE = 0, BLACK = 1, EMPTY = -1 };

enum PawnSide { PAWN_BOTTOM = 1, PAWN_TOP = 2 };

enum Turn { WHITE_TURN = 0, BLACK_TURN = 1 };


