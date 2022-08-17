#include "pch.h"
#include "Board.h"
#include <iostream>
#include "Settings.h"

Board::Board(SDL_Renderer* renderer, std::map<Position, Piece*> pieces) {

	this->renderer = renderer;

	bool c = 0;

	this->array_of_fields = new Field * [10];
	for (int i = 0; i < 10; i++) {
		this->array_of_fields[i] = new Field[10];
	}

	this->array_of_pieces = new Field * [10];
	for (int i = 0; i < 10; i++) {
		this->array_of_pieces[i] = new Field[10];
	}

	for (int w = -75; w < BOARD_WIDTH; w += 100) {
		for (int h = -75; h < BOARD_HEIGHT; h += 100) {

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
				this->array_of_fields[x][y].picture.init("resources/black_field.bmp", renderer);
			}
			else {
				this->array_of_fields[x][y].picture.init("resources/white_field.bmp", renderer);
			}
			this->array_of_fields[x][y].picture.setSourceRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT);
			this->array_of_fields[x][y].picture.setDestinationRect(w, h, FIELD_WIDTH, FIELD_HEIGHT);

			c = !c;
		}
		c = !c;
	}
	// White pieces
	/*for (int x = 1; x <= 8; x++) {
		this->array_of_pieces[x][2].picture->init("resources/white_pawn.bmp", renderer);
		this->array_of_pieces[x][2].picture->setSourceRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT);
		this->array_of_pieces[x][2].picture->setDestinationRect(25 + (x - 1) * 100, 125, FIELD_WIDTH, FIELD_HEIGHT);
		//this->array_of_fields[x][2].picture->setBlendMode(SDL_BLENDMODE_NONE);
	}

	// Black pieces
	for (int x = 1; x <= 8; x++) {
		this->array_of_pieces[x][7].picture->init("resources/black_pawn.bmp", renderer);
		this->array_of_pieces[x][7].picture->setSourceRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT);
		this->array_of_pieces[x][7].picture->setDestinationRect(25 + (x - 1) * 100, 625, FIELD_WIDTH, FIELD_HEIGHT);
		//this->array_of_fields[x][7].picture->setBlendMode(SDL_BLENDMODE_BLEND);
	}
	*/

	for (auto p : pieces) {
		int x = p.first.col;
		int y = p.first.row;
		this->array_of_pieces[x][y].picture.init(p.second->get_image_source(), renderer);
		this->array_of_pieces[x][y].picture.setSourceRect(0, 0, FIELD_WIDTH, FIELD_HEIGHT);
		this->array_of_pieces[x][y].picture.setDestinationRect(25 + (x - 1) * 100, 25 + (y-1)*100, FIELD_WIDTH, FIELD_HEIGHT);
		
	}

}

void Board::change_position(int which_col, int which_row, int to_x_px, int to_y_px) {

	int x = (int)(to_x_px / 100);
	int y = (int)(to_y_px / 100);
	if (to_x_px > 0) x++;
	if (to_y_px > 0) y++;
	this->array_of_pieces[x][y].absolutePosition.x = to_x_px;
	this->array_of_pieces[x][y].absolutePosition.y = to_y_px;
	this->array_of_pieces[which_col][which_row].picture.clearAll();

}

void Board::render_board() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			this->array_of_fields[i][j].picture.render(renderer);
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			this->array_of_pieces[i][j].picture.render(renderer);
		}
	}
}

void Board::drag_piece(int row, int col, int destination_x, int destination_y) {
	this->array_of_pieces[col][row].picture.setDestinationRect(destination_x, destination_y, FIELD_WIDTH, FIELD_HEIGHT);
	this->array_of_pieces[col][row].picture.render(renderer);
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
