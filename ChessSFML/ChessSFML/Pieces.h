#pragma once
#include <string>

class Piece
{
private:
	bool taken;
	bool colour; // white = 1, black = 0
	bool moved;
	std::string type;
public:
	void setColour(bool);
	bool isWhite();
	void setTaken(bool);
	bool isTaken();
	void setMoved(bool);
	bool didMove();
	void setType(std::string);
	std::string getType();
};


class Pawn : public Piece
{
public:
	Pawn(bool);
};


class Rook : public Piece
{
public:
	Rook(bool);
};


class Bishop : public Piece
{
public:
	Bishop(bool);
};


class Knight : public Piece
{
public:
	Knight(bool);
};


class Queen : public Piece
{
public:
	Queen(bool);
};


class King : public Piece
{
public:
	King(bool);
};


class Empty : public Piece
{
public:
	Empty(bool);
};
