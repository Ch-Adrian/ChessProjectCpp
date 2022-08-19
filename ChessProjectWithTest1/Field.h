#include "pch.h"
#pragma once
#include "Picture.h"
#include "Position.h"
#include "AbsolutePosition.h"

class Field
{
public:

	Picture* picture;
	Position position;
	AbsolutePosition absolutePosition;

	Field();
	~Field();
	void set_picture(std::string path_to_image, SDL_Renderer* renderer);
	//void set_format();
	//void set_position(const Position& p);
	//void set_absolute_position(AbsolutePosition* p);
	//void set_board_position();
	//void set_absolute_position();

};

