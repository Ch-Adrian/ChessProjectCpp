#include "pch.h"
#include "Board.h"
#include <iostream>
#include "Settings.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "ApplicationView.h"
#include <math.h>

Board::Board(Window& mainWindow): mainWindow(mainWindow) {

	std::map<Position, Piece*> pieces = this->boardData.get_board();

	this->renderer = mainWindow.getRenderer();

	bool c = 0;

	this->array_of_fields = new Field * [10];
	for (int i = 0; i < 10; i++) {
		this->array_of_fields[i] = new Field[10];
		for (int j = 0; j < 10; j++) {
			this->array_of_fields[i][j].picture = new Picture();
		}
	}

	this->array_of_pieces = new Field*[10];
	for (int i = 0; i < 10; i++) {
		this->array_of_pieces[i] = new Field[10];
	}

	for (int i = 0; i < 32; i++) {
		ordered_picture_pieces.push_back(new Picture());
	}
	
	for (int w = -75; w < ApplicationView::BOARD_WIDTH; w += 100) {
		for (int h = -75; h < ApplicationView::BOARD_HEIGHT; h += 100) {

			int x = (int)(w / 100);
			int y = (int)(h / 100);
			if (w > 0) x++;
			if (h > 0) y++;
			std::cout << "x: " << x << "  y:  " << y << std::endl;
			std::cout << this->array_of_fields[x][y].absolutePosition.x << std::endl;

			this->array_of_fields[x][y].absolutePosition.x = w;
			this->array_of_fields[x][y].absolutePosition.y = h;

			this->array_of_pieces[x][y].absolutePosition.x = w;
			this->array_of_pieces[x][y].absolutePosition.y = h;

			if (y < 1 && y > 8) {
				this->array_of_fields[x][y].position.row = -1;
				this->array_of_pieces[x][y].position.row = -1;
			}
			else {
				this->array_of_fields[x][y].position.row = y;
				this->array_of_pieces[x][y].position.row = y;
			}

			if (x < 1 && x > 8) {
				this->array_of_fields[x][y].position.col = -1;
				this->array_of_pieces[x][y].position.col = -1;
			}
			else {
				this->array_of_fields[x][y].position.col = x;
				this->array_of_pieces[x][y].position.col = x;
			}
			if (c) {
				this->array_of_fields[x][y].picture->init("resources/black_field.bmp", renderer);
			}
			else {
				this->array_of_fields[x][y].picture->init("resources/white_field.bmp", renderer);
			}
			this->array_of_fields[x][y].picture->setSourceRect(0, 0, ApplicationView::FIELD_WIDTH, ApplicationView::FIELD_HEIGHT);
			this->array_of_fields[x][y].picture->setDestinationRect(w, h, ApplicationView::FIELD_WIDTH, ApplicationView::FIELD_HEIGHT);

			c = !c;
		}
		c = !c;
	}
	// White pieces
	/*for (int x = 1; x <= 8; x++) {
		this->array_of_pieces[x][2].picture->>init("resources/white_pawn.bmp", renderer);
		this->array_of_pieces[x][2].picture->>setSourceRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT);
		this->array_of_pieces[x][2].picture->>setDestinationRect(25 + (x - 1) * 100, 125, FIELD_WIDTH, FIELD_HEIGHT);
		//this->array_of_fields[x][2].picture->>setBlendMode(SDL_BLENDMODE_NONE);
	}

	// Black pieces
	for (int x = 1; x <= 8; x++) {
		this->array_of_pieces[x][7].picture->>init("resources/black_pawn.bmp", renderer);
		this->array_of_pieces[x][7].picture->>setSourceRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT);
		this->array_of_pieces[x][7].picture->>setDestinationRect(25 + (x - 1) * 100, 625, FIELD_WIDTH, FIELD_HEIGHT);
		//this->array_of_fields[x][7].picture->>setBlendMode(SDL_BLENDMODE_BLEND);
	}
	*/

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->array_of_pieces[i][j].picture = nullptr;
		}
	}

	for (auto p : pieces) {

		int x = p.first.col;
		int y = p.first.row;
		if (p.second->get_id() < this->ordered_picture_pieces.size()) {
			this->array_of_pieces[x][y].picture = this->ordered_picture_pieces[p.second->get_id()];
		}
		else {
			//TODO
		}
	
		this->array_of_pieces[x][y].picture->init(p.second->get_image_source(), renderer);
		this->array_of_pieces[x][y].picture->setSourceRect(0, 0, ApplicationView::FIELD_WIDTH, ApplicationView::FIELD_HEIGHT);
		this->array_of_pieces[x][y].picture->setDestinationRect(25 + (x - 1) * 100, 25 + (y-1)*100, ApplicationView::FIELD_WIDTH, ApplicationView::FIELD_HEIGHT);
		
	}

	this->picture_black_queen.init("resources/black_queen.bmp", renderer);
	this->picture_black_queen.setSourceRect(0, 0, 500, 500);
	this->picture_black_queen.setDestinationRect(0, 0, 100, 100);

	this->picture_white_queen.init("resources/white_queen.bmp", renderer);
	this->picture_white_queen.setSourceRect(0, 0, 500, 500);
	this->picture_white_queen.setDestinationRect(0, 0, 100, 100);

	this->picture_black_knight.init("resources/black_knight.bmp", renderer);
	this->picture_black_knight.setSourceRect(0, 0, 500, 500);
	this->picture_black_knight.setDestinationRect(100, 0, 100, 100);

	this->picture_white_knight.init("resources/white_knight.bmp", renderer);
	this->picture_white_knight.setSourceRect(0, 0, 500, 500);
	this->picture_white_knight.setDestinationRect(100, 0, 100, 100);

	this->picture_background.init("resources/black_field.bmp", renderer);
	this->picture_background.setSourceRect(0, 0, 100, 100);
	this->picture_background.setDestinationRect(0, 0, 100, 100);

	this->picture_background2.init("resources/black_field.bmp", renderer);
	this->picture_background2.setSourceRect(0, 0, 100, 100);
	this->picture_background2.setDestinationRect(100, 0, 100, 100);

}

void Board::apply_pieces() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->array_of_pieces[i][j].picture = nullptr;
		}
	}

	for (auto p : boardData.get_board()) {

		int x = p.first.col;
		int y = p.first.row;
		if (p.second->get_id() != -1 && p.second->get_id() < this->ordered_picture_pieces.size()) {
			this->array_of_pieces[x][y].picture = this->ordered_picture_pieces[p.second->get_id()];
		}
		else if(p.second->get_id() != -1){
			this->ordered_picture_pieces.push_back(new Picture());
			this->ordered_picture_pieces.back()->init(p.second->get_image_source(), renderer);
			this->ordered_picture_pieces.back()->setSourceRect(0, 0, ApplicationView::FIELD_WIDTH, ApplicationView::FIELD_HEIGHT);
			this->ordered_picture_pieces.back()->setDestinationRect(25 + (x - 1) * 100, 25 + (y-1)*100, ApplicationView::FIELD_WIDTH, ApplicationView::FIELD_HEIGHT);
			this->array_of_pieces[x][y].picture = this->ordered_picture_pieces[p.second->get_id()];

		}
		else {

		}
		std::cout << "apply_pieces: " << x << ", " << y << " " << 25 + (x - 1) * 100 << std::endl;
		this->array_of_pieces[x][y].picture->setDestinationRect(25 + (x - 1) * 100, 25 + (y-1)*100, ApplicationView::FIELD_WIDTH, ApplicationView::FIELD_HEIGHT);

	}

}

void Board::render_board() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if(this->array_of_fields[i][j].picture != nullptr)
				this->array_of_fields[i][j].picture->render(renderer);
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if(this->array_of_pieces[i][j].picture != nullptr)
				this->array_of_pieces[i][j].picture->render(renderer);
		}
	}

}

void Board::drag_piece(int row, int col, int destination_x, int destination_y) {
	if (this->array_of_pieces[col][row].picture == nullptr) {
		return;
	}

	this->array_of_pieces[col][row].
		picture->setDestinationRect(destination_x, 
					destination_y, 
					ApplicationView::FIELD_WIDTH, 
					ApplicationView::FIELD_HEIGHT);
	//this->array_of_pieces[col][row].picture->render(renderer);
}

void Board::drag_piece(Position pos, AbsolutePosition abs_pos){
	if (this->array_of_pieces[pos.col][pos.row].picture == nullptr) {
		return;
	}

	this->array_of_pieces[pos.col][pos.row].
		picture->setDestinationRect(
				abs_pos.x - ApplicationView::FIELD_WIDTH/2,
				abs_pos.y - ApplicationView::FIELD_HEIGHT/2, 
				ApplicationView::FIELD_WIDTH, 
				ApplicationView::FIELD_HEIGHT);
}

void Board::mark_accesible_fields(int moving_picture_init_col, int moving_picture_init_row) {

	for (Position p : boardData.get_all_available_positions(Position(moving_picture_init_col, moving_picture_init_row))) {
		if (this->array_of_pieces[p.col][p.row].picture != nullptr) {
			this->array_of_fields[p.col][p.row].picture->setColor(200, 0, 0);
		}
		else {
			this->array_of_fields[p.col][p.row].picture->setColor(50, 150, 50);
		}
	}
		
}

void Board::clean_light() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->array_of_fields[i][j].picture->setColor(255, 255, 255);
		}
	}
}

Board::~Board() {

	for (int i = 0; i < 10; i++) {
		delete[] array_of_pieces[i];
	}
	delete[] array_of_pieces;

	for (int i = 0; i < 10; i++) {
		delete[] array_of_fields[i];
	}
	delete[] array_of_fields;
}

void Board::render_selection(PlayerColor exchange_color){

	picture_background.render(renderer);
	picture_background2.render(renderer);
	if (exchange_color == BLACK) {
		picture_black_knight.render(renderer);
		picture_black_queen.render(renderer);
	}
	else {
		picture_white_queen.render(renderer);
		picture_white_knight.render(renderer);
	}

}

void Board::exchange_pawn(bool isQueen, PlayerColor exchange_color){
	
	if (isQueen) {
		boardData.exchange_pawn(PieceType::QUEEN, exchange_color);
	}
	else {
		boardData.exchange_pawn(PieceType::LEFT_KNIGHT, exchange_color);
	}
	
	apply_pieces();

}


int Board::move_piece(const Move& move){
	return this->boardData.move_piece(move);
}

bool Board::validate_move(const Move& move){
	return this->boardData.validate_move(move);
}