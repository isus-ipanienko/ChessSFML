#pragma once
#include "Board.h"

class GameEngine
{
private:
	Board ChessBoard; // the board's representation in the pc
	std::string position; // moves taken during the game

	sf::Vector2f lastPosition; // in pixels
	sf::Vector2f nextPosition; // in pixels

	sf::Vector2i mousePosition; // in pixels
	sf::Vector2f draggingDistance; // in pixels

	sf::Vector2i draggedCoords; // which piece is being dragged?
	bool dragging; // is a piece being dragged?

	bool playerTurn; // white = 1, black = 0
	int turn; // which turn is it?

	std::string gameState; // current game state
	int turnsWithNoCapture; // draw by 50 turns counter

	void updateGameState(); // check for gamestate updates
	void promote(std::string); // promotion pop-up
	std::string promotions; // when and what to?
	std::string convert2Chess(sf::Vector2f); // convert coordinates to chess notation

	// move validation
	bool isStillCheck(std::string); // is my king in check?
	bool isPseudoLegal(std::string); // is this move legal? (checks ommited)
	bool isValidMove(std::string); // is this move valid?
public:
	GameEngine();
	void play(); // play the game
};
