#include "pch.h"
#include "Board.h"
#include <iostream>
#include "BoardData.h"

Board::Board(int board_width_px, int board_height_px,
	int field_width_px, int field_height_px,
	SDL_Renderer* renderer, SDL_PixelFormat* format,
		std::map<std::pair<int, int>, std::pair<int, bool>> pieces) {

	this->board_width_px = board_width_px;
	this->board_height_px = board_height_px;
	this->field_height_px = field_height_px;
	this->field_width_px = field_width_px;
	bool c = 0;

	this->array_of_fields = new Field * [10];
	for (int i = 0; i < 10; i++) {
		this->array_of_fields[i] = new Field[10];
	}

	this->array_of_pieces = new Field * [10];
	for (int i = 0; i < 10; i++) {
		this->array_of_pieces[i] = new Field[10];
	}

	for (int w = -75; w < this->board_width_px; w += 100) {
		for (int h = -75; h < this->board_height_px; h += 100) {

			int x = (int)(w / 100);
			int y = (int)(h / 100);
			if (w > 0) x++;
			if (h > 0) y++;
			std::cout << "x: " << x << "  y:  " << y << std::endl;
			std::cout << this->array_of_fields[x][y].position->x << std::endl;

			this->array_of_fields[x][y].position->x = w;
			this->array_of_fields[x][y].position->y = h;

			this->array_of_pieces[x][y].position->x = w;
			this->array_of_pieces[x][y].position->y = h;

			if (y < 1 && y > 8) {
				this->array_of_fields[x][y].position->row = -1;
				this->array_of_pieces[x][y].position->row = -1;
			}
			else {
				this->array_of_fields[x][y].position->row = y;
				this->array_of_pieces[x][y].position->row = y;
			}

			if (x < 1 && x > 8) {
				this->array_of_fields[x][y].position->col = -1;
				this->array_of_pieces[x][y].position->col = -1;
			}
			else {
				this->array_of_fields[x][y].position->col = x;
				this->array_of_pieces[x][y].position->col = x;
			}
			if (c) {
				this->array_of_fields[x][y].picture->init("resources/black_field.bmp", renderer);
			}
			else {
				this->array_of_fields[x][y].picture->init("resources/white_field.bmp", renderer);
			}
			this->array_of_fields[x][y].picture->setSourceRect(0, 0, this->field_width_px, this->field_height_px);
			this->array_of_fields[x][y].picture->setDestinationRect(w, h, this->field_width_px, this->field_height_px);

			c = !c;
		}
		c = !c;
	}
	// White pieces
	/*for (int x = 1; x <= 8; x++) {
		this->array_of_pieces[x][2].picture->init("resources/white_pawn.bmp", renderer);
		this->array_of_pieces[x][2].picture->setSourceRect(0, 0, this->field_width_px, this->field_height_px);
		this->array_of_pieces[x][2].picture->setDestinationRect(25 + (x - 1) * 100, 125, this->field_width_px, this->field_height_px);
		//this->array_of_fields[x][2].picture->setBlendMode(SDL_BLENDMODE_NONE);
	}

	// Black pieces
	for (int x = 1; x <= 8; x++) {
		this->array_of_pieces[x][7].picture->init("resources/black_pawn.bmp", renderer);
		this->array_of_pieces[x][7].picture->setSourceRect(0, 0, this->field_width_px, this->field_height_px);
		this->array_of_pieces[x][7].picture->setDestinationRect(25 + (x - 1) * 100, 625, this->field_width_px, this->field_height_px);
		//this->array_of_fields[x][7].picture->setBlendMode(SDL_BLENDMODE_BLEND);
	}
	*/
	for (auto p : pieces) {
		int x = p.first.first;
		int y = p.first.second;
		Piece piece = (Piece)p.second.first;
		PlayerColor color = (PlayerColor)p.second.second;
		std::string image_source = "";

		if (color == WHITE) {
			switch (piece) {
				case KING: image_source = "resources/white_king.bmp"; break;
				case QUEEN:image_source = "resources/white_queen.bmp";break;
				case BISHOP:image_source = "resources/white_bishop.bmp";break;
				case KNIGHT:image_source = "resources/white_knight.bmp";break;
				case ROOK:image_source = "resources/white_rook.bmp";break;
				case PAWN:image_source = "resources/white_pawn.bmp";break;
				default:
					break;
			}
		}
		else {
			switch (piece) {
				case KING: image_source = "resources/black_king.bmp"; break;
				case QUEEN:image_source = "resources/black_queen.bmp";break;
				case BISHOP:image_source = "resources/black_bishop.bmp";break;
				case KNIGHT:image_source = "resources/black_knight.bmp";break;
				case ROOK:image_source = "resources/black_rook.bmp";break;
				case PAWN:image_source = "resources/black_pawn.bmp";break;
				default:
					break;
			}
		}
		//std::cout << "x,y: " << x << ',' << y << "  Piece, color:  " << piece << "," << color << std::endl;
		this->array_of_pieces[x][y].picture->init(image_source, renderer);
		this->array_of_pieces[x][y].picture->setSourceRect(0, 0, this->field_width_px, this->field_height_px);
		this->array_of_pieces[x][y].picture->setDestinationRect(25 + (x - 1) * 100, 25 + (y-1)*100, this->field_width_px, this->field_height_px);
		
	}

}

//void Board::change_position(int which_row, int which_col, int to_x_px, int to_y_px) {
//	int x = (int)(to_x_px / 100);
//	int y = (int)(to_y_px / 100);
//	if (to_x_px > 0) x++;
//	if (to_y_px > 0) y++;
//	this->array_of_pieces[x][y].position->x = to_x_px;
//	this->array_of_pieces[x][y].position->y = to_y_px;
//}

void Board::render_board(SDL_Renderer* renderer) {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			this->array_of_fields[i][j].picture->render(renderer);
			this->array_of_pieces[i][j].picture->render(renderer);
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
