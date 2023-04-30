#include "pch.h"
#include "AbsolutePosition.h"
#include "Position.h"
#include "ApplicationView.h"

AbsolutePosition::AbsolutePosition() {
	this->x = -1;
	this->y = -1;
}

AbsolutePosition::AbsolutePosition(int x, int y) {
	this->x = x;
	this->y = y;
}
