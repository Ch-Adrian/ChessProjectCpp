#include "pch.h"
#include "Field.h"

Field::Field()
{
	this->picture = new Picture();
	this->position = new Position();
}

Field::Field(const SDL_PixelFormat* fmt)
{
	this->picture = new Picture();
	this->position = new Position();
}

void Field::set_picture(std::string path_to_image, SDL_Renderer* renderer)
{
	this->picture = new Picture();
	this->picture->init(path_to_image, renderer);
}

Field::~Field() {

	if (this->picture != nullptr) {
		delete this->picture;
	}

	if (this->position != nullptr) {
		delete this->position;
	}

}