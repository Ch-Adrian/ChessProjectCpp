#include "pch.h"
#include "Position.h"

Position::Position() {
	this->row = -1;
	this->col = -1;
}

Position::Position(int col, int row){
	this->row = row;
	this->col = col;
}

bool Position::operator<(const Position& pos) const{
	return this->col < pos.col || (this->col == pos.col && this->row < pos.row);
}

bool Position::operator==(const Position& pos) const {
	if (this->col == pos.col && this->row == pos.row) {
		return true;
	}
	return false;
}

Position& Position::operator=(const Position& pos) {
	this->col = pos.col;
	this->row = pos.row;
	return *this;
}

bool Position::isEmpty() const {
	if (this->row == -1 || this->col == -1) {
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const Position& pos) {
	out << "Position: " << pos.col << " , " << pos.row;
	return out;
}