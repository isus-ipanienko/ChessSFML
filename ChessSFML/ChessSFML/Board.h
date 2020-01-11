#pragma once
#include "Pieces.h"

class Board
{
private:
	Piece* board[8][8];
public:
	void movePiece(std::string);
	void take(sf::Vector2i);
	void place(sf::Vector2i, char, bool);
	Piece*& getPiece(std::string);
	Piece*& getPiece(int, int);
	Piece*& getPiece(sf::Vector2i);
	void setBoard(std::string = "start", bool = false);
	void loadBoard();
	Board();
	~Board();
};
