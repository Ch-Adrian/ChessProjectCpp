#include "pch.h"
#pragma once
#include "Settings.h"

class Piece;

class IShareBoardData {

public:

	virtual const std::map<Position, Piece*> get_board() = 0;
	virtual Piece*** get_array_board() = 0;
	virtual Piece* get_piece(const Position& pos) = 0;
	virtual PieceType get_type(const Position& pos) = 0;
	virtual PlayerColor get_color(const Position& pos) = 0;
	virtual const Move& get_last_pawn_move() = 0;
	virtual const std::vector<Piece*> get_one_side_pieces(PlayerColor side) = 0;
	virtual bool hasTurn(const Position& pos) = 0;

};
