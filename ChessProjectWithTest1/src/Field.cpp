#include "pch.h"
#include "Field.h"

Field::Field()
{
	this->picture = nullptr;
}

void Field::set_picture(std::string path_to_image, SDL_Renderer* renderer)
{
	if (this->picture != nullptr) {
		this->picture->init(path_to_image, renderer);
	}
}

Field::~Field() {
	if (this->picture != nullptr) {
		this->picture->clearAll();
		delete this->picture;
	}
	
}