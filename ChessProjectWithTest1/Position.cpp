#include "pch.h"
#include "Position.h"

Position::Position() {
	this->x = 0;
	this->y = 0;
	this->row = 0;
	this->col = 0;
}

Position::Position(int x, int y, int row, int col) {
	this->x = x;
	this->y = y;
	this->row = row;
	this->col = col;
}
