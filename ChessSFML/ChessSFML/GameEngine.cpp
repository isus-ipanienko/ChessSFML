#include "GameEngine.h"


GameEngine::GameEngine()
{
	position = "";
	dragging = false;
	playerTurn = true;
	gameState = "game";
	turnsWithNoCapture = 0;
	turn = 0;
	promotions = "";
}

void GameEngine::updateGameState()
{
	auto size = position.size();
	if (turnsWithNoCapture == 50) // by 50 moves
		gameState = "draw";
	if (size > 59) // by repetition
		if (position.substr(size - 60, 20) == position.substr(size - 20, 20)
			&& position.substr(size - 60, 20) == position.substr(size - 40, 20))
			gameState = "draw";
}

std::string GameEngine::convert2Chess(sf::Vector2f v)
{
	std::string temp = "";
	temp += char(v.x / 50 + 97);
	temp += char(7 - v.y / 50 + 49);
	return temp;
}

bool GameEngine::isStillCheck(std::string move)
{
	std::string tempPos = position + move + " ";
	bool check = false; 
	sf::Vector2i kingPos = sf::Vector2i(-1, -1);
	Board TestBoard = Board();

	TestBoard.setBoard(position, false, promotions);
	TestBoard.movePiece(move);

	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 8; j++)
	{ // find the king
		if(TestBoard.getPiece(i, j))
		if (TestBoard.getPiece(i, j)->getType() == "King"
			&& TestBoard.getPiece(i, j)->isWhite() == playerTurn)
		{
			kingPos = sf::Vector2i(i, j);
			break;
		}
		if (kingPos.x != -1) break;
	}

	// check for queens and rooks (vertical and horizontal)
	for (int i = kingPos.x - 1; i > -1; i--) 
	{ // check left
		if (TestBoard.getPiece(i, kingPos.y))
		{
			if ((TestBoard.getPiece(i, kingPos.y)->getType() != "Queen"
				&& TestBoard.getPiece(i, kingPos.y)->getType() != "Rook")
				|| TestBoard.getPiece(i, kingPos.y)->isWhite() == playerTurn)
				break;
			else
				return true;
		}
	}
	for (int i = kingPos.x + 1; i < 8; i++) 
	{ // check right
		if (TestBoard.getPiece(i, kingPos.y))
		{
			if ((TestBoard.getPiece(i, kingPos.y)->getType() != "Queen"
				&& TestBoard.getPiece(i, kingPos.y)->getType() != "Rook")
				|| TestBoard.getPiece(i, kingPos.y)->isWhite() == playerTurn)
				break;
			else
				return true;
		}
	}
	for (int j = kingPos.y - 1; j > -1; j--) 
	{ // check down
		if (TestBoard.getPiece(kingPos.x, j))
		{
			if ((TestBoard.getPiece(kingPos.x, j)->getType() != "Queen"
				&& TestBoard.getPiece(kingPos.x, j)->getType() != "Rook")
				|| TestBoard.getPiece(kingPos.x, j)->isWhite() == playerTurn)
				break;
			else
				return true;
		}
	}
	for (int j = kingPos.y + 1; j < 8; j++) 
	{ // check up
		if (TestBoard.getPiece(kingPos.x, j))
		{
			if ((TestBoard.getPiece(kingPos.x, j)->getType() != "Queen"
				&& TestBoard.getPiece(kingPos.x, j)->getType() != "Rook")
				|| TestBoard.getPiece(kingPos.x, j)->isWhite() == playerTurn)
				break;
			else
				return true;
		}
	}
	// end queens and rooks


	// check for queens and bishops (radiant)
	for (int i = 1; i < 8; i++)
		if (kingPos.x + i < 8 && kingPos.y + i < 8)
		{ // check up-right
			if (TestBoard.getPiece(kingPos.x + i, kingPos.y + i))
			{
				if ((TestBoard.getPiece(kingPos.x + i, kingPos.y + i)->getType() != "Queen"
					&& TestBoard.getPiece(kingPos.x + i, kingPos.y + i)->getType() != "Bishop")
					|| TestBoard.getPiece(kingPos.x + i, kingPos.y + i)->isWhite() == playerTurn)
					break;
				else 
					return true;
			}
		}
	for (int i = 1; i < 8; i++)
		if (kingPos.x + i < 8 && kingPos.y - i > -1)
		{ // check down-right
			if (TestBoard.getPiece(kingPos.x + i, kingPos.y - i))
			{
				if ((TestBoard.getPiece(kingPos.x + i, kingPos.y - i)->getType() != "Queen"
					&& TestBoard.getPiece(kingPos.x + i, kingPos.y - i)->getType() != "Bishop")
					|| TestBoard.getPiece(kingPos.x + i, kingPos.y - i)->isWhite() == playerTurn)
					break;
				else 
					return true;
			}
		}
	for (int i = 1; i < 8; i++)
		if (kingPos.x - i > -1 && kingPos.y + i < 8)
		{ // check up-left
			if (TestBoard.getPiece(kingPos.x - i, kingPos.y + i))
			{
				if ((TestBoard.getPiece(kingPos.x - i, kingPos.y + i)->getType() != "Queen"
					&& TestBoard.getPiece(kingPos.x - i, kingPos.y + i)->getType() != "Bishop")
					|| TestBoard.getPiece(kingPos.x - i, kingPos.y + i)->isWhite() == playerTurn)
					break;
				else 
					return true;
			}
		}
	for (int i = 1; i < 8; i++)
		if (kingPos.x - i > -1 && kingPos.y - i > -1)
		{ // check down-left
			if (TestBoard.getPiece(kingPos.x - i, kingPos.y - i))
			{
				if ((TestBoard.getPiece(kingPos.x - i, kingPos.y - i)->getType() != "Queen"
					&& TestBoard.getPiece(kingPos.x - i, kingPos.y - i)->getType() != "Bishop")
					|| TestBoard.getPiece(kingPos.x - i, kingPos.y - i)->isWhite() == playerTurn)
					break;
				else 
					return true;
			}
		}
	// end queens and bishops


	// check for knights

	// up-right
	if (kingPos.x + 1 < 8 && kingPos.y + 2 < 8)
		if (TestBoard.getPiece(kingPos.x + 1, kingPos.y + 2))
			if (TestBoard.getPiece(kingPos.x + 1, kingPos.y + 2)->getType() == "Knight"
				&& TestBoard.getPiece(kingPos.x + 1, kingPos.y + 2)->isWhite() != playerTurn)
				return true;
	if (kingPos.x + 2 < 8 && kingPos.y + 1 < 8)
		if (TestBoard.getPiece(kingPos.x + 2, kingPos.y + 1))
			if (TestBoard.getPiece(kingPos.x + 2, kingPos.y + 1)->getType() == "Knight"
				&& TestBoard.getPiece(kingPos.x + 2, kingPos.y + 1)->isWhite() != playerTurn)
				return true;

	// up-left
	if (kingPos.x + 1 < 8 && kingPos.y - 2 > -1)
		if (TestBoard.getPiece(kingPos.x + 1, kingPos.y - 2))
			if (TestBoard.getPiece(kingPos.x + 1, kingPos.y - 2)->getType() == "Knight"
				&& TestBoard.getPiece(kingPos.x + 1, kingPos.y - 2)->isWhite() != playerTurn)
				return true;
	if (kingPos.x + 2 < 8 && kingPos.y - 1 > -1)
		if (TestBoard.getPiece(kingPos.x + 2, kingPos.y - 1))
			if (TestBoard.getPiece(kingPos.x + 2, kingPos.y - 1)->getType() == "Knight"
				&& TestBoard.getPiece(kingPos.x + 2, kingPos.y - 1)->isWhite() != playerTurn)
				return true;

	// down-right
	if (kingPos.x - 1 > -1 && kingPos.y + 2 < 8)
		if (TestBoard.getPiece(kingPos.x - 1, kingPos.y + 2))
			if (TestBoard.getPiece(kingPos.x - 1, kingPos.y + 2)->getType() == "Knight"
				&& TestBoard.getPiece(kingPos.x - 1, kingPos.y + 2)->isWhite() != playerTurn)
				return true;
	if (kingPos.x - 2 > -1 && kingPos.y + 1 < 8)
		if (TestBoard.getPiece(kingPos.x - 2, kingPos.y + 1))
			if (TestBoard.getPiece(kingPos.x - 2, kingPos.y + 1)->getType() == "Knight"
				&& TestBoard.getPiece(kingPos.x - 2, kingPos.y + 1)->isWhite() != playerTurn)
				return true;

	// down-left
	if (kingPos.x - 1 > -1 && kingPos.y - 2 > -1)
		if (TestBoard.getPiece(kingPos.x - 1, kingPos.y - 2))
			if (TestBoard.getPiece(kingPos.x - 1, kingPos.y - 2)->getType() == "Knight"
				&& TestBoard.getPiece(kingPos.x - 1, kingPos.y - 2)->isWhite() != playerTurn)
				return true;
	if (kingPos.x - 2 > -1 && kingPos.y - 1 > -1)
		if (TestBoard.getPiece(kingPos.x - 2, kingPos.y - 1))
			if (TestBoard.getPiece(kingPos.x - 2, kingPos.y - 1)->getType() == "Knight"
				&& TestBoard.getPiece(kingPos.x - 2, kingPos.y - 1)->isWhite() != playerTurn)
				return true;

	// end knights

	// pawns
	if (playerTurn) // white king
	{
		if (kingPos.x - 1 > -1 && kingPos.y + 1 < 8)
		{
			if (TestBoard.getPiece(kingPos.x - 1, kingPos.y + 1))
				if (TestBoard.getPiece(kingPos.x - 1, kingPos.y + 1)->getType() == "Pawn"
					&& TestBoard.getPiece(kingPos.x - 1, kingPos.y + 1)->isWhite() != playerTurn)
					return true;
		}
		else if (kingPos.x + 1 < 8 && kingPos.y + 1 < 8)
		{
			if (TestBoard.getPiece(kingPos.x + 1, kingPos.y + 1))
				if (TestBoard.getPiece(kingPos.x + 1, kingPos.y + 1)->getType() == "Pawn"
					&& TestBoard.getPiece(kingPos.x + 1, kingPos.y + 1)->isWhite() != playerTurn)
					return true;
		}

	}
	else // black king
	{
		if (kingPos.x - 1 > -1 && kingPos.y - 1 > -1)
		{
			if (TestBoard.getPiece(kingPos.x - 1, kingPos.y - 1))
				if (TestBoard.getPiece(kingPos.x - 1, kingPos.y - 1)->getType() == "Pawn"
					&& TestBoard.getPiece(kingPos.x - 1, kingPos.y - 1)->isWhite() != playerTurn)
					return true;
		}
		else if (kingPos.x + 1 < 8 && kingPos.y - 1 > -1)
		{
			if (TestBoard.getPiece(kingPos.x + 1, kingPos.y - 1))
				if (TestBoard.getPiece(kingPos.x + 1, kingPos.y - 1)->getType() == "Pawn"
					&& TestBoard.getPiece(kingPos.x + 1, kingPos.y - 1)->isWhite() != playerTurn)
					return true;
		}
	}

	// end pawns

	return check;
}
bool GameEngine::isPseudoLegal(std::string move) // doesn't check pins
{
	std::string tempName = ChessBoard.getPiece(int(move[0]) - 97, int(move[1]) - 49)->getType();
	sf::Vector2i prevPos = sf::Vector2i(int(move[0]) - 97, int(move[1]) - 49);
	sf::Vector2i nextPos = sf::Vector2i(int(move[2]) - 97, int(move[3]) - 49);
	int dx = nextPos.x - prevPos.x;
	int dy = nextPos.y - prevPos.y;


	if (tempName == "Pawn")
	{ // Pawn first move and take and en-passant and Pawn blocking override (in order)
		int c = -1;
		if (ChessBoard.getPiece(prevPos)->isWhite()) c = 1;

		if (dx == 0 && dy == 2 * c)
		{// double move
			std::string firstMove = "";
			firstMove += char(prevPos.x + 97);
			firstMove += char(prevPos.y + 49);
			if (position.find(firstMove) == -1)
				return !ChessBoard.getPiece(nextPos);
		}

		if (std::abs(dx) == 1 && dy == c)
		{
			if (ChessBoard.getPiece(nextPos)) return true;

			// en-passant
			if (ChessBoard.getPiece(prevPos)->isWhite() && prevPos.y == 4)
			{ // white en-passant
				std::string enPassant = "";
				enPassant += char(nextPos.x + 97);
				enPassant += char(nextPos.y + 49 + 1);
				enPassant += char(nextPos.x + 97);
				enPassant += char(nextPos.y + 49 - 1);

				if (position.substr(position.size() - 5, 4) == enPassant &&
					ChessBoard.getPiece(nextPos.x, nextPos.y - 1)->getType() == "Pawn")
				{
					ChessBoard.take(sf::Vector2i(nextPos.x, nextPos.y - 1));
					return true;
				}
			}
			else if (prevPos.y == 3)
			{ // black en-passant
				std::string enPassant = "";
				enPassant += char(nextPos.x + 97);
				enPassant += char(nextPos.y + 49 - 1);
				enPassant += char(nextPos.x + 97);
				enPassant += char(nextPos.y + 49 + 1);

				if (position.substr(position.size() - 5, 4) == enPassant &&
					ChessBoard.getPiece(nextPos.x, nextPos.y + 1)->getType() == "Pawn")
				{
					ChessBoard.take(sf::Vector2i(nextPos.x, nextPos.y + 1));
					return true;
				}
			}
		}

		if (ChessBoard.getPiece(prevPos)->checkLegality(prevPos, nextPos))
		{ // blocked
			return !ChessBoard.getPiece(nextPos);
		}
	}


	if (ChessBoard.getPiece(prevPos)->checkLegality(prevPos, nextPos) || tempName == "King")
	{ // check if nothing is in the way

		if (dy == 0)
		{ // for horizontal movement
			if (dx > 0)
			{
				for (int i = 1; i < dx; i++)
					if (ChessBoard.getPiece(prevPos.x + i, prevPos.y)) return false;
			}
			else
			{
				for (int i = -1; i > dx; i--)
					if (ChessBoard.getPiece(prevPos.x + i, prevPos.y)) return false;
			}
		}
		if (dx == 0)
		{ // for vertical movement
			if (dy > 0)
			{
				for (int i = 1; i < dy; i++)
					if (ChessBoard.getPiece(prevPos.x, prevPos.y + i)) return false;
			}
			else
			{
				for (int i = -1; i > dy; i--)
					if (ChessBoard.getPiece(prevPos.x, prevPos.y + i)) return false;
			}
		}
		if (std::abs(dx) == std::abs(dy))
		{ // for radiant movement
			for (int i = 1; i < std::abs(dx); i++)
			{
				if (dx > 0 && dy > 0)
					if (ChessBoard.getPiece(prevPos.x + i, prevPos.y + i)) return false;
				if (dx > 0 && dy < 0)
					if (ChessBoard.getPiece(prevPos.x + i, prevPos.y - i)) return false;
				if (dx < 0 && dy > 0)
					if (ChessBoard.getPiece(prevPos.x - i, prevPos.y + i)) return false;
				if (dx < 0 && dy < 0)
					if (ChessBoard.getPiece(prevPos.x - i, prevPos.y - i)) return false;
			}
		}


		if (tempName == "King")
		{ // castling override
			if (move == "e1c1" && position.find("e1") == -1 && position.find("a1") == -1)
			{
				ChessBoard.movePiece("a1d1");
				ChessBoard.getPiece(3, 0)->getSprite().setPosition(150, 350);
				return true;
			}
			if (move == "e1g1" && position.find("e1") == -1 && position.find("h1") == -1)
			{
				ChessBoard.movePiece("h1f1");
				ChessBoard.getPiece(5, 0)->getSprite().setPosition(250, 350);
				return true;
			}
			if (move == "e8c8" && position.find("e8") == -1 && position.find("a8") == -1)
			{
				ChessBoard.movePiece("a8d8");
				ChessBoard.getPiece(3, 7)->getSprite().setPosition(150, 0);
				return true;
			}
			if (move == "e8g8" && position.find("e8") == -1 && position.find("h8") == -1)
			{
				ChessBoard.movePiece("h8f8");
				ChessBoard.getPiece(5, 7)->getSprite().setPosition(250,0);
				return true;
			}
			return ChessBoard.getPiece(prevPos)->checkLegality(prevPos, nextPos);
		}


		return true;
	}
	return false;
}
bool GameEngine::isValidMove(std::string move)
{
	if (lastPosition == nextPosition) return false;
	if (ChessBoard.getPiece(draggedCoords)->isWhite() != playerTurn) return false;
	if (ChessBoard.getPiece(sf::Vector2i(int(move[2]) - 97, int(move[3]) - 49)))
		if (ChessBoard.getPiece(draggedCoords)->isWhite()
			== ChessBoard.getPiece(sf::Vector2i(int(move[2]) - 97, int(move[3]) - 49))->isWhite()) return false;
	if (!isPseudoLegal(move)) return false;
	if (isStillCheck(move)) return false;
	return true;
}

void GameEngine::promote(std::string pos)
{
	char choice = 'q';

	sf::RenderWindow pWindow(sf::VideoMode(200, 200), "Chess");
	sf::Event pEvent;

	sf::Texture pBackgroundTexture;
	pBackgroundTexture.loadFromFile("img/promote.bmp");
	sf::Sprite pBackground(pBackgroundTexture);

	while (pWindow.isOpen())
	{
		while (pWindow.pollEvent(pEvent))
		{
			if (pEvent.type == sf::Event::KeyPressed)
				if (pEvent.key.code == sf::Keyboard::V)
				{
					choice = 'q';
					pWindow.close();
				}
			if (pEvent.type == sf::Event::KeyPressed)
				if (pEvent.key.code == sf::Keyboard::B)
				{
					choice = 'b';
					pWindow.close();
				}
			if (pEvent.type == sf::Event::KeyPressed)
				if (pEvent.key.code == sf::Keyboard::N)
				{
					choice = 'k';
					pWindow.close();
				}
			if (pEvent.type == sf::Event::KeyPressed)
				if (pEvent.key.code == sf::Keyboard::M)
				{
					choice = 'r';
					pWindow.close();
				}
		}
		pWindow.clear();
		pWindow.draw(pBackground);
		pWindow.display();
	}

	promotions += char(turn);
	promotions += choice;
	sf::Vector2i promPos = sf::Vector2i(int(pos[0]) - 97, int(pos[1]) - 49);
	ChessBoard.take(promPos); // substitute the pawn
	ChessBoard.place(promPos, choice, playerTurn);
}

void GameEngine::play()
{
	sf::RenderWindow window(sf::VideoMode(500, 400), "Chess");
	sf::Event e;

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("img/board.bmp");
	sf::Sprite Background(backgroundTexture);

	while (window.isOpen())
	{
		mousePosition = sf::Mouse::getPosition(window);
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();


			// reset //

			if (e.type == sf::Event::KeyPressed)
				if (e.key.code == sf::Keyboard::R)
				{
					ChessBoard.setBoard();
					ChessBoard.loadBoard();
					position = "";
					dragging = false;
					playerTurn = true;
					gameState = "game";
					turnsWithNoCapture = 0;
					backgroundTexture.loadFromFile("img/board.bmp");
					turn = 0;
					promotions = "";
				}
			
			///////////

			// pick up //

			if (e.type == sf::Event::MouseButtonPressed)
				if (e.key.code == sf::Mouse::Left)
					if (gameState == "game")
						for (int i = 0; i < 8; i++)
						{
							for (int j = 0; j < 8; j++)
							{
								if (ChessBoard.getPiece(i, j))
								{
									if (ChessBoard.getPiece(i, j)->getSprite().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
									{
										dragging = true;
										draggedCoords = sf::Vector2i(i, j);
										draggingDistance.x = mousePosition.x - ChessBoard.getPiece(i, j)->getSprite().getPosition().x;
										draggingDistance.y = mousePosition.y - ChessBoard.getPiece(i, j)->getSprite().getPosition().y;
										lastPosition = ChessBoard.getPiece(i, j)->getSprite().getPosition();
									}
								}
							}
						}
		
			// drop //

			if (e.type == sf::Event::MouseButtonReleased)
				if (e.key.code == sf::Mouse::Left)
					if (gameState == "game")
					{
						dragging = false;

						//  + sf::Vector2f(25, 25) = adjust center
						sf::Vector2f temp = ChessBoard.getPiece(draggedCoords)->getSprite().getPosition() + sf::Vector2f(25, 25);
						nextPosition = sf::Vector2f(50 * int(temp.x / 50), 50 * int(temp.y / 50));

						// convert move to chess notation
						std::string tempMove = convert2Chess(lastPosition) + convert2Chess(nextPosition);

						if (isValidMove(tempMove)) 
						{
							ChessBoard.getPiece(draggedCoords)->getSprite().setPosition(nextPosition);

							if (ChessBoard.getPiece(int(temp.x / 50), int(temp.y / 50)))
								turnsWithNoCapture++;
							else
								turnsWithNoCapture = 0;

							ChessBoard.movePiece(tempMove);
							position += tempMove + " ";

							// Pawn promotion
							if (ChessBoard.getPiece(int(tempMove[2]) - 97, int(tempMove[3]) - 49)->getType() == "Pawn")
							{
								if (playerTurn == true && tempMove[3] == '8')
									promote(tempMove.substr(2, 2));
								else if (playerTurn == false && tempMove[3] == '1')
									promote(tempMove.substr(2, 2));
							}

							playerTurn = !playerTurn;
							turn++;
							updateGameState();
							if (gameState == "draw")
								backgroundTexture.loadFromFile("img/boardDraw.bmp");

						}
						else
						{
							ChessBoard.getPiece(draggedCoords)->getSprite().setPosition(lastPosition);
						}
					}
			
			/////////////
		}



		// draw //

		window.clear();

		window.draw(Background);
		
		if(dragging) // dragging animation
			ChessBoard.getPiece(draggedCoords)->getSprite().setPosition(mousePosition.x - draggingDistance.x, mousePosition.y - draggingDistance.y);
	
		for (int i = 0; i < 8; i++) { // draw the pieces
			for (int j = 0; j < 8; j++) {
				if (ChessBoard.getPiece(i, j))
					window.draw(ChessBoard.getPiece(i, j)->getSprite());
			}
		}


		window.display();

		//////////
	}
}
