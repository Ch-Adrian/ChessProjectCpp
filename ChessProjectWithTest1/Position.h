#include "pch.h"
#pragma once

class Position
{
public:
	int row;
	int col;

	Position(int col, int row);
	Position();

	bool operator<(const Position& pos) const;
	bool operator==(const Position& pos) const;
	Position& operator=(const Position& pos) ;
	bool isEmpty() const;
};

