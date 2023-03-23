#pragma once
#include "Position.h"
#include "Move.h"
#include "IShareBoardData.h"

class Piece
{
private:
	PieceType type;
	PlayerColor color;
	int id;

public:

	Piece(PieceType type, PlayerColor color);

	virtual bool validate_move(IShareBoardData& share, const Move& move) = 0;
	virtual std::vector<Position> get_available_positions(IShareBoardData& share, const Position& pos) = 0;
	virtual std::vector<Position> get_positions_under_attack(IShareBoardData& share, const Position& pos) = 0;
	virtual std::string get_image_source() = 0;
	static bool position_inside_board(const Position& pos);

	//virtual bool validate_move(Position* from, Position* to);
	PieceType get_type();
	PlayerColor get_color();
	int get_id();
	void set_id(int id);
	friend std::ostream& operator<<(std::ostream& out, Piece& piece);

};

