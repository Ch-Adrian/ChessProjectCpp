#include "pch.h"
#include "Move.h"
#include "Field.h"

class ManageData {

public:
	std::vector<Move> show_all_moves_for_position(Field** f, Position p, bool color);
	std::vector<Move> show_all_moves_for_player(Field** f, bool color);
	void change_position(Move move);

private:
	bool validate_move(Field**, Move move);

};