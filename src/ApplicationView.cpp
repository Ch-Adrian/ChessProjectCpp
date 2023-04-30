#include "pch.h"
#include "ApplicationView.h"

ApplicationView::ApplicationView():
	mainWindow(Window{"Chess", BOARD_WIDTH, BOARD_HEIGHT}),
	board(Board{ mainWindow }), boardData(this->board.getBoardData()){

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
	
	moving_picture_init_col = mouse_position_x_px / FIELD_WIDTH + 1;
	moving_picture_init_row = mouse_position_y_px / FIELD_HEIGHT + 1;
	Position picture_pos(moving_picture_init_col, moving_picture_init_row);

	if (show_middleViewPort) {
		if (mouse_position_x_px >= middleViewPort.x && mouse_position_x_px <= middleViewPort.x + 2 * FIELD_WIDTH) {
			if (mouse_position_y_px >= middleViewPort.y && mouse_position_y_px <= middleViewPort.y + FIELD_HEIGHT) {
				show_middleViewPort = false;
				board.exchange_pawn(mouse_position_x_px < middleViewPort.x + FIELD_WIDTH, exchange_color);
			}
		}
	}
	else {
		if (this->boardData.hasTurn(picture_pos)) {
			board.mark_accesible_fields(moving_picture_init_col, moving_picture_init_row);
			onDrag = true;
		}
	}
}

bool ApplicationView::actionRelease(SDL_Event& event) {

	int mouse_position_x_px = event.button.x - BOARD_BORDER_WIDTH;
	int mouse_position_y_px = event.button.y - BOARD_BORDER_WIDTH;
	int moving_picture_final_row = mouse_position_y_px / FIELD_HEIGHT + 1;
	int moving_picture_final_col = mouse_position_x_px / FIELD_WIDTH + 1;

	if (show_middleViewPort || !onDrag) { return false; }

	Move next_move = Move(Position(moving_picture_init_col, moving_picture_init_row), Position(moving_picture_final_col, moving_picture_final_row));
	bool move_acceptance = this->boardData.validate_move(next_move);
	bool not_moving_at_all = next_move.isBackToTheSamePlace();
	bool king_checked = this->boardData.isKingChecked();
	bool king_released = !king_checked;
	PlayerColor releasedKingColor = PlayerColor::EMPTY;

	if (!not_moving_at_all && move_acceptance) {
		releasedKingColor = this->boardData.simulateKingIsReleased(next_move);
		if (releasedKingColor != PlayerColor::EMPTY) {
			king_released = false;
		}
		else {
			king_released = true;
		}
	}
	

	if (move_acceptance && !next_move.isBackToTheSamePlace() && !(king_checked && !king_released) && 
		!(!king_checked && !king_released && this->boardData.getTurn() == releasedKingColor) ) {

		int field_next_position_x_px = convX_to_pixels(convX_to_position(event.button.x));
		int field_next_position_y_px = convY_to_pixels(convY_to_position(event.button.y));

		board.drag_piece(moving_picture_init_row, moving_picture_init_col, field_next_position_x_px, field_next_position_y_px);
		int ret_val = this->boardData.move_piece(next_move);
		board.apply_pieces();

		if (ret_val == PAWN_TOP) {
			show_middleViewPort = true;
			exchange_color = PlayerColor::BLACK;
		}
		else if (ret_val == PAWN_BOTTOM) {
			exchange_color = PlayerColor::WHITE;
			show_middleViewPort = true;
		}
		
		this->boardData.unCheckKing();
		this->boardData.changeTurn();
		this->boardData.checkKingIsThreatened();
	}
	else {

		int field_next_position_x_px = convX_to_pixels(moving_picture_init_col);
		int field_next_position_y_px = convY_to_pixels(moving_picture_init_row);

		board.drag_piece(moving_picture_init_row, moving_picture_init_col, field_next_position_x_px, field_next_position_y_px);

	}

	onDrag = false;
	board.clean_light();
	return true;
}

void ApplicationView::actionDrag(SDL_Event& event) {
	AbsolutePosition mouse_position(event.button.x, event.button.y);
	
	SDL_RenderClear(mainWindow.getRenderer());

	if (onDrag) {

		board.drag_piece(Position(moving_picture_init_col, moving_picture_init_row),
					mouse_position);
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
			this->board.render_selection(exchange_color);
		}

		SDL_RenderPresent(mainWindow.getRenderer());

	}
}

int ApplicationView::convX_to_pixels(int pos){
	return BOARD_BORDER_WIDTH+(pos-1)*FIELD_WIDTH;
}

int ApplicationView::convX_to_position(int pix){
	return (pix-BOARD_BORDER_WIDTH)/ FIELD_WIDTH + 1;
}

int ApplicationView::convY_to_pixels(int pos){
	return BOARD_BORDER_WIDTH+(pos-1)* FIELD_HEIGHT;
}

int ApplicationView::convY_to_position(int pix){
	return (pix-BOARD_BORDER_WIDTH)/ FIELD_HEIGHT + 1;
}
