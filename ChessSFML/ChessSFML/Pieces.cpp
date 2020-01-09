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

void Piece::setTaken(bool newTaken)
{
	taken = newTaken;
	return;
};

bool Piece::isTaken()
{
	return taken;
};

void Piece::setMoved(bool newMoved)
{
	moved = newMoved;
	return;
};

bool Piece::didMove()
{
	return moved;
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


Pawn::Pawn(bool newColour)
{
	setColour(newColour);
	setType("Pawn");
};


Rook::Rook(bool newColour)
{
	setColour(newColour);
	setType("Rook");
};


Bishop::Bishop(bool newColour)
{
	setColour(newColour);
	setType("Bishop");
};


Knight::Knight(bool newColour)
{
	setColour(newColour);
	setType("Knight");
};


Queen::Queen(bool newColour)
{
	setColour(newColour);
	setType("Queen");
};


King::King(bool newColour)
{
	setColour(newColour);
	setType("King");
};


Empty::Empty(bool newColour)
{
	setColour(newColour);
	setType("Empty");
};
