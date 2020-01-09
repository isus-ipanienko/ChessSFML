#pragma once
#include "Board.h"

class GameEngine
{
private:
	Board ChessBoard;
	std::string position;

	sf::Vector2f lastPosition;
	sf::Vector2f nextPosition;

	sf::Vector2i mousePosition;
	sf::Vector2f draggingDistance;

	sf::Vector2i draggedCoords;
	bool dragging;

	bool playerTurn; // white = 1, black = 0
public:
	std::string convert2Chess(sf::Vector2f);
	bool isValidMove(std::string);
	GameEngine();
	void play();
};
