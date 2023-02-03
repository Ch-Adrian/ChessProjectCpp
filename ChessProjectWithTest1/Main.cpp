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

		//Window mainWindow{ "Chess", BOARD_WIDTH, BOARD_HEIGHT };
		//BoardData boardData;
		//Board board(mainWindow.getRenderer(), boardData.get_board());
		
		ApplicationView applicationView;

		//Picture picture_black_queen;
		//picture_black_queen.init("resources/black_queen.bmp", mainWindow.getRenderer());
		//picture_black_queen.setSourceRect(0, 0, 500, 500);
		//picture_black_queen.setDestinationRect(0, 0, 100, 100);

		//Picture picture_white_queen;
		//picture_white_queen.init("resources/white_queen.bmp", mainWindow.getRenderer());
		//picture_white_queen.setSourceRect(0, 0, 500, 500);
		//picture_white_queen.setDestinationRect(0, 0, 100, 100);	

		//Picture picture_black_knight;
		//picture_black_knight.init("resources/black_knight.bmp", mainWindow.getRenderer());
		//picture_black_knight.setSourceRect(0, 0, 500, 500);
		//picture_black_knight.setDestinationRect(100, 0, 100, 100);

		//Picture picture_white_knight;
		//picture_white_knight.init("resources/white_knight.bmp", mainWindow.getRenderer());
		//picture_white_knight.setSourceRect(0, 0, 500, 500);
		//picture_white_knight.setDestinationRect(100, 0, 100, 100);	

		//Picture picture_background;
		//picture_background.init("resources/black_field.bmp", mainWindow.getRenderer());
		//picture_background.setSourceRect(0, 0, 100, 100);
		//picture_background.setDestinationRect(0, 0, 100, 100);
		//
		//Picture picture_background2;
		//picture_background2.init("resources/black_field.bmp", mainWindow.getRenderer());
		//picture_background2.setSourceRect(0, 0, 100, 100);
		//picture_background2.setDestinationRect(100, 0, 100, 100);
		

		bool quit = false;
		SDL_Event event;
		//bool onDrag = false;
		//int moving_picture_init_col = -1;
		//int moving_picture_init_row = -1;
		//Move* mv = new Move(Position(1, 1), Position(2, 2));
		//delete mv;

		//SDL_Rect originViewPort;
		//originViewPort.x = 0;
		//originViewPort.y = 0;
		//originViewPort.w = BOARD_WIDTH;
		//originViewPort.h = BOARD_HEIGHT;

		//bool show_middleViewPort = false;
		//SDL_Rect middleViewPort;
		//bool exchange_color = false;
		//middleViewPort.x = (BOARD_WIDTH - FIELD_WIDTH -50) / 2;
		//middleViewPort.y = (BOARD_HEIGHT - FIELD_HEIGHT) / 2;
		//middleViewPort.h = FIELD_HEIGHT;
		//middleViewPort.w = 2 * FIELD_WIDTH;
		//SDL_RenderCopy(mainWindow.getRenderer(), 

		while (!quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				applicationView.handleEvent(event);
				//if (event.type == SDL_MOUSEBUTTONDOWN) {
				//	//int mouse_position_x_px = event.button.x - BOARD_BORDER_WIDTH;
				//	//int mouse_position_y_px = event.button.y - BOARD_BORDER_WIDTH;
				//	//std::cout << "mouse y: " << mouse_position_y_px << std::endl;
				//	//moving_picture_init_col = mouse_position_x_px / FIELD_WIDTH + 1;
				//	//moving_picture_init_row = mouse_position_y_px / FIELD_HEIGHT + 1;

				//	//std::cout << mouse_position_x_px << std::endl;

				//	//if (show_middleViewPort) {

				//	//}
				//	//else {
				//	//	board.mark_accesible_fields(boardData.get_all_available_positions(Position(moving_picture_init_col, moving_picture_init_row)));
				//	//	onDrag = true;
				//	//}

				//	applicationView.actionClick(event);

				//}
				//if (event.type == SDL_MOUSEBUTTONUP) {

				//	if (!applicationView.actionRelease(event)) {
				//		continue;
				//	}
				//	//int mouse_position_x_px = event.button.x - BOARD_BORDER_WIDTH;
				//	//int mouse_position_y_px = event.button.y - BOARD_BORDER_WIDTH;
				//	//int moving_picture_final_row = mouse_position_y_px / FIELD_HEIGHT + 1;
				//	//int moving_picture_final_col = mouse_position_x_px / FIELD_WIDTH + 1;
				//	//
				//	//if (show_middleViewPort) {
				//	//	
				//	//	if (mouse_position_x_px >= middleViewPort.x && mouse_position_x_px <= middleViewPort.x + 2 * FIELD_WIDTH) {
				//	//		if (mouse_position_y_px >= middleViewPort.y && mouse_position_y_px <= middleViewPort.y + FIELD_HEIGHT) {
				//	//			show_middleViewPort = false;
				//	//			if (mouse_position_x_px < middleViewPort.x + FIELD_WIDTH) {
				//	//				boardData.exchange_pawn(QUEEN, exchange_color);
				//	//			}
				//	//			else {
				//	//				boardData.exchange_pawn(LEFT_KNIGHT, exchange_color);

				//	//			}
				//	//			board.apply_pieces(boardData.get_board());
				//	//		}
				//	//	}
				//	//	
				//	//	continue;
				//	//}

				//	//std::cout << "initial: " << moving_picture_init_col << ", " << moving_picture_init_row << std::endl;
				//	//std::cout << "final: " << moving_picture_final_col << ", " << moving_picture_final_row << std::endl;
				//	//Move next_move = Move(Position(moving_picture_init_col, moving_picture_init_row), Position(moving_picture_final_col, moving_picture_final_row));
				//	//bool move_acceptance = boardData.validate_move(next_move);
				//	//std::cout << "validate: " << move_acceptance << std::endl;

				//	//if (move_acceptance) {

				//	//	int field_next_position_x_px = CommonFunctions::convX_to_pixels(CommonFunctions::convX_to_position(event.button.x));
				//	//	int field_next_position_y_px = CommonFunctions::convY_to_pixels(CommonFunctions::convY_to_position(event.button.y));
				//	//	std::cout << "next: " << field_next_position_x_px << ", " << field_next_position_y_px << std::endl;
				//	//	board.drag_piece(moving_picture_init_row, moving_picture_init_col, field_next_position_x_px, field_next_position_y_px);
				//	//	int ret_val = boardData.move_piece(next_move);
				//	//	board.apply_pieces(boardData.get_board());
				//	//	//board.change_position(next_move.from.col, next_move.from.row, field_next_position_x_px, field_next_position_y_px );
				//	//	if (ret_val == PAWN_TOP) {
				//	//		show_middleViewPort = true;
				//	//		exchange_color = true;
				//	//	}
				//	//	else if (ret_val == PAWN_BOTTOM) {
				//	//		exchange_color = false;
				//	//		show_middleViewPort = true;
				//	//	}
				//	//}
				//	//else {

				//	//	int field_next_position_x_px = CommonFunctions::convX_to_pixels(moving_picture_init_col);
				//	//	int field_next_position_y_px = CommonFunctions::convY_to_pixels(moving_picture_init_row);
				//	//	std::cout << "next: " << field_next_position_x_px << ", " << field_next_position_y_px << std::endl;
				//	//	board.drag_piece(moving_picture_init_row, moving_picture_init_col, field_next_position_x_px, field_next_position_y_px);
				//	//	
				//	//}

				//	//onDrag = false;
				//	//board.clean_light();
				//}
				//if (event.type == SDL_MOUSEMOTION) {

				//	applicationView.actionDrag(event);

				//	//int mouse_position_x_px = event.button.x;
				//	//int mouse_position_y_px = event.button.y ;
				//	//SDL_RenderClear(mainWindow.getRenderer());
				//	//
				//	//if (onDrag) {
				//	//	//std::cout << mouse_position_y_px << std::endl;
				//	//	//std::cout << "row: " << moving_picture_init_row << std::endl;
				//	//	board.drag_piece(moving_picture_init_row, moving_picture_init_col, mouse_position_x_px - FIELD_WIDTH/2, mouse_position_y_px - FIELD_WIDTH/2);
				//	//}
				//	
				//}
				//mainWindow.handleEvent(event);
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