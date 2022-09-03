#pragma once

#define BOARD_WIDTH 850
#define BOARD_HEIGHT 850
#define FIELD_WIDTH 100
#define FIELD_HEIGHT 100
#define BOARD_BORDER_WIDTH 25

enum PieceType { LEFT_ROOK, LEFT_KNIGHT, LEFT_BISHOP, 
	KING, QUEEN, RIGHT_BISHOP,
	RIGHT_KNIGHT, RIGHT_ROOK, PAWN };

enum PlayerColor { WHITE = false, BLACK = true};

enum PawnSide{ PAWN_BOTTOM = 1, PAWN_TOP = 2};

