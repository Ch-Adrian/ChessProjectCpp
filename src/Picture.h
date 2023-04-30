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

	void loadSurface(std::string pathToImage) ;
	void loadSurface_with_format(std::string pathToImage, SDL_PixelFormat* format) ;
	void loadPicture(SDL_Renderer* windowRenderer) ;

public:

	Picture();
	~Picture();

	void init(std::string pathToImage, SDL_Renderer* windowRenderer) ;
	void init_with_format(std::string pathToImage, SDL_Renderer* windowRenderer, SDL_PixelFormat* format) ;
	void clearAll();
	void render(SDL_Renderer* windowRenderer) ;

	int getWidth() const;
	int getHeight() const;

	void setColor(Uint8 red, Uint8 green, Uint8 blue) ;
	void setBlendMode(SDL_BlendMode blendMode) ;
	void setAlpha(Uint8 aplha) ;
	void setSourceRect(const int& x, const int& y, const int& w, const int& h);
	void setDestinationRect(const int& x, const int& y, const int& w, const int& h);
	void setAngle(const double ang);
	void setRotationCenter(SDL_Point* center);
	void setFlip(SDL_RendererFlip f);
};

