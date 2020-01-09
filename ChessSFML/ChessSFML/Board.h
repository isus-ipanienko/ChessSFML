#pragma once
#include "Pieces.h"

class Board
{
private:
	Piece* board[8][8];
public:
	void movePiece(std::string);
	Piece*& getPiece(std::string);
	Piece*& getPiece(int, int);
	void setBoard(std::string = "start", bool = false);
	void loadBoard();
	Board();
	~Board();
};
