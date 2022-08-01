#include "pch.h"
#include <iostream>
#include <cstdlib>
#include "SdlIncludes.h"
#include "Window.h"
#include "InitializationException.h"
#include "Board.h"

#define BOARD_WIDTH 850
#define BOARD_HEIGHT 850
#define FIELD_WIDTH 100
#define FIELD_HEIGHT 100


int main(int argc, char** argv) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw InitializationException("Cannot initialize SDL!: " + std::string(SDL_GetError()) + "\n");
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw InitializationException(&std::string("SDL_image failed to initialize: " + std::string(IMG_GetError()) + "\n")[0]);
	}

	try {

		Window mainWindow{ "Chess", BOARD_WIDTH, BOARD_HEIGHT };
		SDL_Surface* surf = SDL_GetWindowSurface(mainWindow.window);
		Board board(BOARD_WIDTH, BOARD_HEIGHT,
			FIELD_WIDTH, FIELD_HEIGHT,
			mainWindow.getRenderer(), surf->format);
		Picture picture;
		picture.init("resources/black_pawn.bmp", mainWindow.getRenderer());
		picture.setSourceRect(0, 0, 500, 500);
		picture.setDestinationRect(0, 0, 100, 100);
		Picture picture_background;
		picture_background.init("resources/black_field.bmp", mainWindow.getRenderer());
		picture_background.setSourceRect(0, 0, 100, 100);
		picture_background.setDestinationRect(0, 0, 100, 100);

		bool quit = false;
		SDL_Event event;

		while (!quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				mainWindow.handleEvent(event);
			}

			if (!mainWindow.isMinimized()) {
				SDL_SetRenderDrawColor(mainWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(mainWindow.getRenderer());

				board.render_board(mainWindow.getRenderer());
				//picture_background.render(mainWindow.getRenderer());
				//picture.render(mainWindow.getRenderer());

				SDL_RenderPresent(mainWindow.getRenderer());

			}
		}

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::string exception) {
		std::cout << exception << std::endl;
	}

	IMG_Quit();
	SDL_Quit();

	return 0;
}