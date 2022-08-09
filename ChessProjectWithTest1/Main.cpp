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

int main(int argc, char** argv) {


/*
	std::map<std::pair<int,int> , Piece> mapa;

	mapa.insert({ { std::make_pair(1,1), "1,1" }, { std::make_pair(1,2), "1,2"}});

	for (const auto& value : mapa) {
		std::cout << '[' << value.first.first << " , " << value.first.second << "] = " << value.second << "; " << std::endl;
	}

	return 0;
	*/

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw InitializationException("Cannot initialize SDL!: " + std::string(SDL_GetError()) + "\n");
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw InitializationException(&std::string("SDL_image failed to initialize: " + std::string(IMG_GetError()) + "\n")[0]);
	}

	try {

		Window mainWindow{ "Chess", BOARD_WIDTH, BOARD_HEIGHT };
		BoardData boardData;
		Board board(mainWindow.getRenderer(), boardData.get_board());
		ManageData dataManager;
		/*
		Picture picture;
		picture.init("resources/black_pawn.bmp", mainWindow.getRenderer());
		picture.setSourceRect(0, 0, 500, 500);
		picture.setDestinationRect(0, 0, 100, 100);
		Picture picture_background;
		picture_background.init("resources/black_field.bmp", mainWindow.getRenderer());
		picture_background.setSourceRect(0, 0, 100, 100);
		picture_background.setDestinationRect(0, 0, 100, 100);
		*/

		bool quit = false;
		SDL_Event event;
		bool onDrag = false;
		int moving_picture_init_col = -1;
		int moving_picture_init_row = -1;
		Move* mv = new Move(Position(1, 1), Position(2, 2));
		CommonFunctions::validate_move(&boardData,mv);
		delete mv;
		while (!quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					int mouse_position_x_px = event.button.x - BOARD_BORDER_WIDTH;
					int mouse_position_y_px = event.button.y - BOARD_BORDER_WIDTH;
					std::cout << "mouse y: " << mouse_position_y_px << std::endl;
					moving_picture_init_col = mouse_position_x_px / FIELD_WIDTH + 1;
					moving_picture_init_row = mouse_position_y_px / FIELD_HEIGHT + 1;

					std::cout << mouse_position_x_px << std::endl;
					
					onDrag = true;

				}
				if (event.type == SDL_MOUSEBUTTONUP) {
					int mouse_position_x_px = event.button.x - BOARD_BORDER_WIDTH;
					int mouse_position_y_px = event.button.y - BOARD_BORDER_WIDTH;
					int moving_picture_final_row = mouse_position_y_px / FIELD_HEIGHT + 1;
					int moving_picture_final_col = mouse_position_x_px / FIELD_WIDTH + 1;

				/*	dataManager.validate_move(
						boardData.get_board(), 
						Move(
							new Position(25+(moving_picture_init_col-1)*100, 25 + (moving_picture_init_row-1)*100, moving_picture_init_row, moving_picture_init_col),
							new Position(25+(moving_picture_final_col-1)*100, 25+(moving_picture_final_row-1)*100, moving_picture_final_row, moving_picture_final_col)));
							*/
					onDrag = false;
				}
				if (event.type == SDL_MOUSEMOTION) {
					int mouse_position_x_px = event.button.x - BOARD_BORDER_WIDTH;
					int mouse_position_y_px = event.button.y - BOARD_BORDER_WIDTH;
					
					if (onDrag) {
						std::cout << mouse_position_y_px << std::endl;
						std::cout << "row: " << moving_picture_init_row << std::endl;
						board.drag_piece(moving_picture_init_row, moving_picture_init_col, mouse_position_x_px - FIELD_WIDTH/2, mouse_position_y_px - FIELD_WIDTH/2);
					}
					
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