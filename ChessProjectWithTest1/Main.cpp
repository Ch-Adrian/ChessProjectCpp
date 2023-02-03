#include "pch.h"
#include <iostream>
#include <cstdlib>
#include "SdlIncludes.h"
#include "Window.h"
#include "InitializationException.h"
#include "Board.h"
#include "BoardData.h"
#include "Piece.h"
#include "Settings.h"
#include "ManageData.h"
#include "CommonFunctions.h"
#include "ApplicationView.h"

int main(int argc, char** argv) {


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw InitializationException("Cannot initialize SDL!: " + std::string(SDL_GetError()) + "\n");
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw InitializationException(&std::string("SDL_image failed to initialize: " + std::string(IMG_GetError()) + "\n")[0]);
	}

	try {

		ApplicationView applicationView;

		bool quit = false;
		SDL_Event event;

		while (!quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				if (!applicationView.handleEvent(event)) {
					continue;
				}
			}
			applicationView.renderView();
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