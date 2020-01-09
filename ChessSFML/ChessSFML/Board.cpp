#include "Board.h"

void Board::movePiece(std::string pos)
{
	board[int(pos[2]) - 97][int(pos[3])] = board[int(pos[0]) - 97][int(pos[1])];
	board[int(pos[0]) - 97][int(pos[1])] = nullptr;
	return;
};

Piece*& Board::getPiece(std::string pos)
{
	return board[int(pos[0]) - 97][int(pos[1])];
};
Piece*& Board::getPiece(int i, int j)
{
	return board[i][j];
};

void Board::setBoard(std::string pos, bool reset)
{
	if (reset) {
		for (int j = 0; j < 8; j++)
		{
			for (int i = 0; i < 8; i++)
				delete board[i][j];
		}
	}

	if (pos == "start")
	{
		// white pieces
		
		board[0][0] = new Rook(true);
		board[1][0] = new Knight(true);
		board[2][0] = new Bishop(true);
		board[3][0] = new Queen(true);
		board[4][0] = new King(true);
		board[5][0] = new Bishop(true);
		board[6][0] = new Knight(true);
		board[7][0] = new Rook(true);

		// black pieces

		board[0][7] = new Rook(false);
		board[1][7] = new Knight(false);
		board[2][7] = new Bishop(false);
		board[3][7] = new Queen(false);
		board[4][7] = new King(false);
		board[5][7] = new Bishop(false);
		board[6][7] = new Knight(false);
		board[7][7] = new Rook(false);

		// pawns

		for (int i = 0; i < 8; i++)
		{
			board[i][1] = new Pawn(true);
			board[i][6] = new Pawn(false);
		}

		// empty spots

		for (int j = 2; j < 6; j++)
		{
			for (int i = 0; i < 8; i++)
				board[i][j] = nullptr;
		}
	}
	else {
		setBoard("start", true);
		for (int i = 0; i < (pos.length() / 5); i++)
		{
			movePiece(pos.substr(5 * i, 4));
		}
	}
}


void Board::loadBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j])
				board[i][j]->getSprite().setPosition(i * 50, j * 50);
		}
	}
}


sf::Texture Piece::textures[12];
Board::Board()
{
	Piece::textures[0].loadFromFile("img/white_pawn.png");
	Piece::textures[1].loadFromFile("img/black_pawn.png");
	Piece::textures[2].loadFromFile("img/white_rook.png");
	Piece::textures[3].loadFromFile("img/black_rook.png");
	Piece::textures[4].loadFromFile("img/white_knight.png");
	Piece::textures[5].loadFromFile("img/black_knight.png");
	Piece::textures[6].loadFromFile("img/white_bishop.png");
	Piece::textures[7].loadFromFile("img/black_bishop.png");
	Piece::textures[8].loadFromFile("img/white_queen.png");
	Piece::textures[9].loadFromFile("img/black_queen.png");
	Piece::textures[10].loadFromFile("img/white_king.png");
	Piece::textures[11].loadFromFile("img/black_king.png");

	setBoard();
	loadBoard();
}

Board::~Board()
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
			delete board[i][j];
	}
}
