#pragma once
#include "Picture.h"
#include "Position.h"

class Field
{
public:

	Picture* picture;
	Position* position;

	Field(const SDL_PixelFormat* fmt);
	Field();
	~Field();
	void set_picture(std::string path_to_image, SDL_Renderer* renderer);
	void set_format();
	void set_position(Position p);
	void set_board_position();
	void set_absolute_position();

};

