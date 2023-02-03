#include "pch.h"
#include "ApplicationView.h"
#include "CommonFunctions.h"

ApplicationView::ApplicationView():
	mainWindow(Window{"Chess", BOARD_WIDTH, BOARD_HEIGHT}),
	board(Board{ mainWindow.getRenderer() }) {

	this->picture_black_queen.init("resources/black_queen.bmp", mainWindow.getRenderer());
	this->picture_black_queen.setSourceRect(0, 0, 500, 500);
	this->picture_black_queen.setDestinationRect(0, 0, 100, 100);

	this->picture_white_queen.init("resources/white_queen.bmp", mainWindow.getRenderer());
	this->picture_white_queen.setSourceRect(0, 0, 500, 500);
	this->picture_white_queen.setDestinationRect(0, 0, 100, 100);

	this->picture_black_knight.init("resources/black_knight.bmp", mainWindow.getRenderer());
	this->picture_black_knight.setSourceRect(0, 0, 500, 500);
	this->picture_black_knight.setDestinationRect(100, 0, 100, 100);

	this->picture_white_knight.init("resources/white_knight.bmp", mainWindow.getRenderer());
	this->picture_white_knight.setSourceRect(0, 0, 500, 500);
	this->picture_white_knight.setDestinationRect(100, 0, 100, 100);

	this->picture_background.init("resources/black_field.bmp", mainWindow.getRenderer());
	this->picture_background.setSourceRect(0, 0, 100, 100);
	this->picture_background.setDestinationRect(0, 0, 100, 100);

	this->picture_background2.init("resources/black_field.bmp", mainWindow.getRenderer());
	this->picture_background2.setSourceRect(0, 0, 100, 100);
	this->picture_background2.setDestinationRect(100, 0, 100, 100);

	this->originViewPort.x = 0;
	this->originViewPort.y = 0;
	this->originViewPort.w = BOARD_WIDTH;
	this->originViewPort.h = BOARD_HEIGHT;

	this->middleViewPort.x = (BOARD_WIDTH - FIELD_WIDTH - 50) / 2;
	this->middleViewPort.y = (BOARD_HEIGHT - FIELD_HEIGHT) / 2;
	this->middleViewPort.h = FIELD_HEIGHT;
	this->middleViewPort.w = 2 * FIELD_WIDTH;

}

void ApplicationView::actionClick(SDL_Event& event) {
	int mouse_position_x_px = event.button.x - BOARD_BORDER_WIDTH;
	int mouse_position_y_px = event.button.y - BOARD_BORDER_WIDTH;
	std::cout << "mouse y: " << mouse_position_y_px << std::endl;
	moving_picture_init_col = mouse_position_x_px / FIELD_WIDTH + 1;
	moving_picture_init_row = mouse_position_y_px / FIELD_HEIGHT + 1;

	std::cout << mouse_position_x_px << std::endl;

	if (show_middleViewPort) {

	}
	else {
		board.mark_accesible_fields(this->board.boardData.get_all_available_positions(Position(moving_picture_init_col, moving_picture_init_row)));
		onDrag = true;
	}
}

bool ApplicationView::actionRelease(SDL_Event& event) {
	int mouse_position_x_px = event.button.x - BOARD_BORDER_WIDTH;
	int mouse_position_y_px = event.button.y - BOARD_BORDER_WIDTH;
	int moving_picture_final_row = mouse_position_y_px / FIELD_HEIGHT + 1;
	int moving_picture_final_col = mouse_position_x_px / FIELD_WIDTH + 1;

	if (show_middleViewPort) {

		if (mouse_position_x_px >= middleViewPort.x && mouse_position_x_px <= middleViewPort.x + 2 * FIELD_WIDTH) {
			if (mouse_position_y_px >= middleViewPort.y && mouse_position_y_px <= middleViewPort.y + FIELD_HEIGHT) {
				show_middleViewPort = false;
				if (mouse_position_x_px < middleViewPort.x + FIELD_WIDTH) {
					this->board.boardData.exchange_pawn(QUEEN, exchange_color);
				}
				else {
					this->board.boardData.exchange_pawn(LEFT_KNIGHT, exchange_color);

				}
				board.apply_pieces(this->board.boardData.get_board());
			}
		}

		return false;
	}

	std::cout << "initial: " << moving_picture_init_col << ", " << moving_picture_init_row << std::endl;
	std::cout << "final: " << moving_picture_final_col << ", " << moving_picture_final_row << std::endl;
	Move next_move = Move(Position(moving_picture_init_col, moving_picture_init_row), Position(moving_picture_final_col, moving_picture_final_row));
	bool move_acceptance = this->board.boardData.validate_move(next_move);
	std::cout << "validate: " << move_acceptance << std::endl;

	if (move_acceptance) {

		int field_next_position_x_px = CommonFunctions::convX_to_pixels(CommonFunctions::convX_to_position(event.button.x));
		int field_next_position_y_px = CommonFunctions::convY_to_pixels(CommonFunctions::convY_to_position(event.button.y));
		std::cout << "next: " << field_next_position_x_px << ", " << field_next_position_y_px << std::endl;
		board.drag_piece(moving_picture_init_row, moving_picture_init_col, field_next_position_x_px, field_next_position_y_px);
		int ret_val = this->board.boardData.move_piece(next_move);
		board.apply_pieces(this->board.boardData.get_board());
		//board.change_position(next_move.from.col, next_move.from.row, field_next_position_x_px, field_next_position_y_px );
		if (ret_val == PAWN_TOP) {
			show_middleViewPort = true;
			exchange_color = true;
		}
		else if (ret_val == PAWN_BOTTOM) {
			exchange_color = false;
			show_middleViewPort = true;
		}
	}
	else {

		int field_next_position_x_px = CommonFunctions::convX_to_pixels(moving_picture_init_col);
		int field_next_position_y_px = CommonFunctions::convY_to_pixels(moving_picture_init_row);
		std::cout << "next: " << field_next_position_x_px << ", " << field_next_position_y_px << std::endl;
		board.drag_piece(moving_picture_init_row, moving_picture_init_col, field_next_position_x_px, field_next_position_y_px);

	}

	onDrag = false;
	board.clean_light();
	return true;
}

void ApplicationView::actionDrag(SDL_Event& event) {
	int mouse_position_x_px = event.button.x;
	int mouse_position_y_px = event.button.y;
	SDL_RenderClear(mainWindow.getRenderer());

	if (onDrag) {
		//std::cout << mouse_position_y_px << std::endl;
		//std::cout << "row: " << moving_picture_init_row << std::endl;
		board.drag_piece(moving_picture_init_row, moving_picture_init_col, mouse_position_x_px - FIELD_WIDTH / 2, mouse_position_y_px - FIELD_WIDTH / 2);
	}
}

bool ApplicationView::handleEvent(SDL_Event& event) {


	if (event.type == SDL_MOUSEBUTTONDOWN) {
		actionClick(event);
	}
	if (event.type == SDL_MOUSEBUTTONUP) {

		if (!actionRelease(event)) {
			return false;
		}
	}
	if (event.type == SDL_MOUSEMOTION) {
		actionDrag(event);
	}

	this->mainWindow.handleEvent(event);
	return true;
}

void ApplicationView::renderView() {

	if (!mainWindow.isMinimized()) {
		SDL_SetRenderDrawColor(mainWindow.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(mainWindow.getRenderer());

		SDL_RenderSetViewport(mainWindow.getRenderer(), &originViewPort);
		board.render_board();

		if (show_middleViewPort) {
			SDL_RenderSetViewport(mainWindow.getRenderer(), &middleViewPort);
			picture_background.render(mainWindow.getRenderer());
			picture_background2.render(mainWindow.getRenderer());
			if (exchange_color == BLACK) {
				picture_black_knight.render(mainWindow.getRenderer());
				picture_black_queen.render(mainWindow.getRenderer());
			}
			else {
				picture_white_queen.render(mainWindow.getRenderer());
				picture_white_knight.render(mainWindow.getRenderer());
			}
		}
		//picture_background.render(mainWindow.getRenderer());
		//picture.render(mainWindow.getRenderer());

		SDL_RenderPresent(mainWindow.getRenderer());

	}
}