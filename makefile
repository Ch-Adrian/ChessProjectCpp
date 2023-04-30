CC=g++ -std=c++11
SDLFLAGS=-lSDL2main -lSDL2 -lSDL2_image
CFLAGS=-Wall -c

run:
	$(CC) $(CFLAGS) src/%.o -o main


compile:
	$(CC) $(CFLAGS) src/AbsolutePosition.cpp -o src/AbsolutePosition.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/ApplicationView.cpp  -o src/ApplicationView.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Bishop.cpp  -o src/Bishop.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Board.cpp  -o src/Board.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/BoardData.cpp  -o src/BoardData.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Field.cpp  -o src/Field.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/InitializationException.cpp  -o src/InitializationException.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/King.cpp  -o src/King.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Knight.cpp  -o src/Knight.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Main.cpp  -o src/Main.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Move.cpp  -o src/Move.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/NullPointerException.cpp  -o src/NullPointerException.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Pawn.cpp  -o src/Pawn.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/pch.cpp  -o src/pch.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Picture.cpp  -o src/Picture.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Piece.cpp  -o src/Piece.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Position.cpp  -o src/Position.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Queen.cpp  -o src/Queen.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Rook.cpp  -o src/Rook.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/test.cpp  -o src/test.o $(SDLFLAGS)
	$(CC) $(CFLAGS) src/Window.cpp  -o src/Window.o $(SDLFLAGS)

clear:
	rm src/*.o

run2:
	$(CC) src/AbsolutePosition.o src/ApplicationView.o src/Bishop.o src/BoardData.o src/Board.o src/Field.o src/InitializationException.o src/King.o src/Knight.o src/Main.o src/Move.o src/NullPointerException.o src/Pawn.o  src/pch.o  src/Picture.o  src/Piece.o src/Position.o src/Queen.o src/Rook.o src/test.o src/Window.o -o main $(SDLFLAGS)
