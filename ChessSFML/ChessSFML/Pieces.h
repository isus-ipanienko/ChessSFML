#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Piece
{
protected:
	bool colour; // white = 1, black = 0
	std::string type;
	sf::Sprite sprite;
public:
	void setColour(bool);
	bool isWhite();
	void setType(std::string);
	std::string getType();
	sf::Sprite& getSprite();
	static sf::Texture textures[12];
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
