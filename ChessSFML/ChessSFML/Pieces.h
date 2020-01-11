#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>

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
	virtual bool checkLegality(sf::Vector2i, sf::Vector2i) = 0;
};


class Pawn : public Piece
{
public:
	bool checkLegality(sf::Vector2i, sf::Vector2i);
	Pawn(bool);
};


class Rook : public Piece
{
public:
	bool checkLegality(sf::Vector2i, sf::Vector2i);
	Rook(bool);
};


class Bishop : public Piece
{
public:
	bool checkLegality(sf::Vector2i, sf::Vector2i);
	Bishop(bool);
};


class Knight : public Piece
{
public:
	bool checkLegality(sf::Vector2i, sf::Vector2i);
	Knight(bool);
};


class Queen : public Piece
{
public:
	bool checkLegality(sf::Vector2i, sf::Vector2i);
	Queen(bool);
};


class King : public Piece
{
public:
	bool checkLegality(sf::Vector2i, sf::Vector2i);
	King(bool);
};
