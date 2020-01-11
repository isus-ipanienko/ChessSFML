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


bool Pawn::checkLegality(sf::Vector2i prevPos, sf::Vector2i nextPos)
{
	int dx = nextPos.x - prevPos.x;
	int dy = nextPos.y - prevPos.y;

	if (dx == 0)
	{
		if (isWhite())
		{
			if (dy == 1)
				return true;
		}
		else
		{
			if (dy == -1)
				return true;
		}
	}
	return false;
}

bool Rook::checkLegality(sf::Vector2i prevPos, sf::Vector2i nextPos)
{
	int dx = std::abs(prevPos.x - nextPos.x);
	int dy = std::abs(prevPos.y - nextPos.y);

	return dx == 0 || dy == 0;
}

bool Bishop::checkLegality(sf::Vector2i prevPos, sf::Vector2i nextPos)
{
	int dx = std::abs(prevPos.x - nextPos.x);
	int dy = std::abs(prevPos.y - nextPos.y);

	return dx == dy;
}

bool Knight::checkLegality(sf::Vector2i prevPos, sf::Vector2i nextPos)
{
	int dx = std::abs(prevPos.x - nextPos.x);
	int dy = std::abs(prevPos.y - nextPos.y);

	if ((0 < dx && dx < 3) && (0 < dy && dy < 3)) return dx + dy < 4;
	return false;
}

bool Queen::checkLegality(sf::Vector2i prevPos, sf::Vector2i nextPos)
{
	int dx = std::abs(prevPos.x - nextPos.x);
	int dy = std::abs(prevPos.y - nextPos.y);

	return dx == 0 || dy == 0 || dx == dy;
}

bool King::checkLegality(sf::Vector2i prevPos, sf::Vector2i nextPos)
{
	int dx = std::abs(prevPos.x - nextPos.x);
	int dy = std::abs(prevPos.y - nextPos.y);
	
	return dx + dy < 3 && dx < 2 && dy < 2;
}


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
