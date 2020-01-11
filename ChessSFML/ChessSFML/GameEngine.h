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

	std::string gameState;
	int turnsWithNoCapture;
public:
	Board getBoard();
	void updateGameState();
	void promote(std::string);
	std::string convert2Chess(sf::Vector2f);
	bool isStillCheck(std::string);
	bool isPseudoLegal(std::string);
	bool isValidMove(std::string);
	GameEngine();
	void play();
};
