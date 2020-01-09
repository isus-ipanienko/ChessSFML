#include "Pieces.h"

void Piece::setColour(bool newColour)
{
	colour = newColour;
	return;
};

bool Piece::isWhite()
{
	return colour;
};

void Piece::setType(std::string newType)
{
	type = newType;
	return;
};

std::string Piece::getType()
{
	return type;
};

sf::Sprite& Piece::getSprite()
{
	return sprite;
};


Pawn::Pawn(bool newColour)
{
	setColour(newColour);
	setType("Pawn");

	if (isWhite())
		sprite.setTexture(Piece::textures[0]);
	else	
		sprite.setTexture(Piece::textures[1]);

};


Rook::Rook(bool newColour)
{
	setColour(newColour);
	setType("Rook");

	if (isWhite())
		sprite.setTexture(Piece::textures[2]);
	else
		sprite.setTexture(Piece::textures[3]);

};


Bishop::Bishop(bool newColour)
{
	setColour(newColour);
	setType("Bishop");

	if (isWhite())
		sprite.setTexture(Piece::textures[6]);
	else
		sprite.setTexture(Piece::textures[7]);

};


Knight::Knight(bool newColour)
{
	setColour(newColour);
	setType("Knight");

	if (isWhite())
		sprite.setTexture(Piece::textures[4]);
	else
		sprite.setTexture(Piece::textures[5]);

};


Queen::Queen(bool newColour)
{
	setColour(newColour);
	setType("Queen");

	if (isWhite())
		sprite.setTexture(Piece::textures[8]);
	else
		sprite.setTexture(Piece::textures[9]);

};


King::King(bool newColour)
{
	setColour(newColour);
	setType("King");

	if (isWhite())
		sprite.setTexture(Piece::textures[10]);
	else
		sprite.setTexture(Piece::textures[11]);

};
