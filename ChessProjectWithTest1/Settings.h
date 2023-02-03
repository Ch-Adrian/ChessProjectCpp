#pragma once

//#define board_width 850
//#define board_height 850
//#define field_width 100
//#define field_height 100
//#define board_border_width 25

enum PieceType {
	LEFT_ROOK, LEFT_KNIGHT, LEFT_BISHOP,
	KING, QUEEN, RIGHT_BISHOP,
	RIGHT_KNIGHT, RIGHT_ROOK, PAWN
};

enum PlayerColor { WHITE = false, BLACK = true };

enum PawnSide { PAWN_BOTTOM = 1, PAWN_TOP = 2 };


