#pragma once
#include "SdlIncludes.h"
#include "InitializationException.h"
#include "NullPointerException.h"

class Picture
{
private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	int width;
	int height;
	bool is_initialized;


	SDL_Rect* sourceRect;
	SDL_Rect* destinationRect;
	double angle;
	SDL_Point* rotationCenter;
	SDL_RendererFlip flip;

	void loadSurface(std::string pathToImage) throw(InitializationException);
	void loadSurface_with_format(std::string pathToImage, SDL_PixelFormat* format) throw(InitializationException);
	void loadPicture(SDL_Renderer* windowRenderer) throw(InitializationException);

public:

	Picture();
	~Picture();

	void init(std::string pathToImage, SDL_Renderer* windowRenderer) throw(InitializationException);
	void init_with_format(std::string pathToImage, SDL_Renderer* windowRenderer, SDL_PixelFormat* format) throw(InitializationException);
	void clearAll();
	void render(SDL_Renderer* windowRenderer) throw(NullPointerException);

	int getWidth() const;
	int getHeight() const;

	void setColor(Uint8 red, Uint8 green, Uint8 blue) throw(NullPointerException);
	void setBlendMode(SDL_BlendMode blendMode) throw(NullPointerException);
	void setAlpha(Uint8 aplha) throw(NullPointerException);
	void setSourceRect(const int& x, const int& y, const int& w, const int& h);
	void setDestinationRect(const int& x, const int& y, const int& w, const int& h);
	void setAngle(const double ang);
	void setRotationCenter(SDL_Point* center);
	void setFlip(SDL_RendererFlip f);
};

