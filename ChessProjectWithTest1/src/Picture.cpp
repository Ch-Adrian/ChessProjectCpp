#include "pch.h"
#include "Picture.h"
#include "InitializationException.h"
#include "NullPointerException.h"

Picture::Picture()
	: texture(nullptr),
	surface(nullptr),
	width(0),
	height(0),
	sourceRect(nullptr),
	destinationRect(nullptr),
	angle(0.0),
	rotationCenter(nullptr),
	flip(SDL_FLIP_NONE),
	is_initialized(false)
{

}

Picture::~Picture() {
	this->clearAll();
}

void Picture::init(std::string pathToImage, SDL_Renderer* windowRenderer) {
	this->clearAll();
	this->loadSurface(pathToImage);
	this->loadPicture(windowRenderer);
	this->is_initialized = true;
}

void Picture::loadSurface(std::string pathToImage) {
	this->surface = SDL_LoadBMP(pathToImage.c_str());
	if (this->surface == NULL) {
		this->surface = nullptr;
		throw InitializationException("Cannot load from file: " + std::string(SDL_GetError()) + "\n");
	}
	else {
		SDL_SetColorKey(this->surface, SDL_TRUE, SDL_MapRGB(this->surface->format, 0, 0xFF, 0xFF));
	}
}

void Picture::init_with_format(std::string pathToImage, SDL_Renderer* windowRenderer, SDL_PixelFormat* format) {
	this->clearAll();
	this->loadSurface_with_format(pathToImage, format);
	this->loadPicture(windowRenderer);
}

void Picture::loadSurface_with_format(std::string pathToImage, SDL_PixelFormat* format) {
	SDL_Surface* pTemporarySurface = NULL;
	pTemporarySurface = IMG_Load(pathToImage.c_str());
	if (pTemporarySurface) {
		this->surface = SDL_ConvertSurface(pTemporarySurface, format, NULL);
	}
	if (this->surface == NULL) {
		this->surface = nullptr;
		throw InitializationException("Cannot load from file: " + std::string(SDL_GetError()) + "\n");
	}
	else {
		SDL_SetColorKey(this->surface, SDL_TRUE, SDL_MapRGB(this->surface->format, 0, 0xFF, 0xFF));
	}
}

void Picture::loadPicture(SDL_Renderer* windowRenderer) {
	this->texture = SDL_CreateTextureFromSurface(windowRenderer, this->surface);
	if (this->texture == NULL) {
		this->texture = nullptr;
		throw InitializationException("Cannot create texture from surface: " + std::string(SDL_GetError()) + "\n");
	}
	else {
		this->width = this->surface->w;
		this->height = this->surface->h;
	}
}

void Picture::clearAll() {

	if (this->surface != nullptr) {
		SDL_FreeSurface(this->surface);
	}
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}

	this->width = 0;
	this->height = 0;

	if (this->sourceRect != nullptr) delete this->sourceRect;
	this->sourceRect = nullptr;

	if (this->destinationRect != nullptr) delete this->destinationRect;
	this->destinationRect = nullptr;

	this->angle = 0.0;
	this->rotationCenter = nullptr;
	this->flip = SDL_FLIP_NONE;
}

void Picture::render(SDL_Renderer* windowRenderer) {
	if (!this->is_initialized)
		return;
	if (this->texture == nullptr)
		throw NullPointerException("Texture has not been initialized!");
	if (this->sourceRect == nullptr)
		throw NullPointerException("Texture Source has not been initialized!");
	if (this->destinationRect == nullptr)
		throw NullPointerException("Texture destination has not been initialized!");
	SDL_RenderCopy(windowRenderer, this->texture, this->sourceRect, this->destinationRect);
}

int Picture::getWidth() const {
	return this->width;
}

int Picture::getHeight() const {
	return this->height;
}

void Picture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	if (this->texture == nullptr)
		throw NullPointerException("Texture has not been initialized!");
	SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void Picture::setBlendMode(SDL_BlendMode blendMode) {
	if (this->texture == nullptr)
		throw NullPointerException("Texture has not been initialized!");
	SDL_SetTextureBlendMode(this->texture, blendMode);
}

void Picture::setAlpha(Uint8 alpha) {
	if (this->texture == nullptr)
		throw NullPointerException("Texture has not been initialized!");
	SDL_SetTextureAlphaMod(this->texture, alpha);
}

void Picture::setSourceRect(const int& x, const int& y, const int& w, const int& h) {
	if (this->sourceRect != nullptr) delete this->sourceRect;
	this->sourceRect = new SDL_Rect{ x,y,w,h };
}

void Picture::setDestinationRect(const int& x, const int& y, const int& w, const int& h) {
	if (this->destinationRect != nullptr) delete this->destinationRect;
	this->destinationRect = new SDL_Rect{ x,y,w,h };
}

void Picture::setAngle(const double ang) {
	this->angle = ang;
}

void Picture::setRotationCenter(SDL_Point* center) {
	this->rotationCenter = center;
}

void Picture::setFlip(SDL_RendererFlip f) {
	this->flip = f;
}


