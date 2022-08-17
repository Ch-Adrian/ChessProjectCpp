#include "pch.h"
#include "Field.h"

Field::Field()
{

}

void Field::set_picture(std::string path_to_image, SDL_Renderer* renderer)
{
	this->picture.init(path_to_image, renderer);
}

Field::~Field() {
}