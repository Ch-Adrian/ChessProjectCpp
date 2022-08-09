#pragma once
#include "Field.h"
#include "Piece.h"
#include "Move.h"
#include "IShareBoardData.h"

class BoardData: public IShareBoardData
{
private:
	std::map<Position, Piece*> board;
	//Piece** boardArray;

public:

	BoardData();
	virtual const std::map<Position, Piece*> get_board();
	virtual Piece* get_piece(const Position& pos);
	virtual int get_type(const Position& pos);
	virtual int get_color(const Position& pos);
	void move_piece(Move move);

};

