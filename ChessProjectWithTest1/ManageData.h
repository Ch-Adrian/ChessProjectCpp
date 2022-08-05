#include "pch.h"
#include "Move.h"
#include "Field.h"
#include "Piece.h"
#include "Settings.h"

class ManageData {

public:
	std::vector<Move> get_all_moves_for_position(Field** f, Position p, bool color);
	std::vector<Move> get_all_moves_for_player(Field** f, bool color);
	void change_position(Move move);
	bool validate_move(std::map<std::pair<int, int>, Piece*> pieces, Move move);

};
