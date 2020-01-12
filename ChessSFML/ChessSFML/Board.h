#pragma once
#include "Pieces.h"

class Board
{
private:
	Piece* board[8][8]; // pointers to the pieces
public:
	// piece handling
	void movePiece(std::string); // move (and take) a piece
	void take(sf::Vector2i); // take a piece
	void place(sf::Vector2i, char, bool); // place a piece on the board

	Piece*& getPiece(std::string); // get a piece
	Piece*& getPiece(int, int); // get a piece
	Piece*& getPiece(sf::Vector2i); // get a piece

	void setBoard(std::string = "start", bool = false, std::string = ""); // board setup
	void loadBoard(); // sprite setup

	Board();
	~Board();
};
