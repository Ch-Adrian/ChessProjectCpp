#pragma once
#include "Position.h"
#include "Move.h"
#include "IShareBoardData.h"

class Piece
{
private:
	int type;
	bool color;
	int id;

public:

	Piece(int type, bool color);

	virtual bool validate_move(IShareBoardData& share, const Move& move) = 0;
	virtual std::vector<Position> get_available_positions(IShareBoardData& share, const Position& pos) = 0;
	virtual std::vector<Position> get_positions_under_attack(IShareBoardData& share, const Position& pos) = 0;
	virtual std::string get_image_source() = 0;

	//virtual bool validate_move(Position* from, Position* to);
	int get_type();
	bool get_color();
	int get_id();
	void set_id(int id);

};

