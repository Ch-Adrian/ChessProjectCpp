#include "pch.h"
#pragma once
#include "Piece.h"

class IShareBoardData {

public:

	virtual const std::map<Position, Piece*> get_board() = 0;
	virtual Piece* get_piece(const Position& pos) = 0;
	virtual int get_type(const Position& pos) = 0;
	virtual int get_color(const Position& pos) = 0;

};
