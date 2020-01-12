#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>

class Piece
{
protected:
	bool colour; // white = 1, black = 0
	std::string type; // pawn / rook / knight / bishop / queen / king
	sf::Sprite sprite; // piece's sprite
public:
	void setColour(bool); // white = 1, black = 0
	bool isWhite(); // white = 1, black = 0

	void setType(std::string); // pawn / rook / knight / bishop / queen / king
	std::string getType(); // pawn / rook / knight / bishop / queen / king

	sf::Sprite& getSprite(); // get &sprite

	static sf::Texture textures[12]; // static for textures

	virtual bool checkLegality(sf::Vector2i, sf::Vector2i) = 0; // is this move legal?
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
