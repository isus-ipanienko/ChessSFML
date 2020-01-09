#include "GameEngine.h"

GameEngine::GameEngine()
{
	position = "";
	dragging = false;
	playerTurn = true;
}

std::string GameEngine::convert2Chess(sf::Vector2f v)
{
	std::string temp = "";
	temp += char(v.x / 50 + 97);
	temp += char(7 - v.y / 50 + 49);
	return temp;
}


bool GameEngine::isValidMove(std::string move) // TODO
{
	if (lastPosition == nextPosition) return false;
	if (ChessBoard.getPiece(draggedCoords)->isWhite() != playerTurn) return false;
	return true;
}

void GameEngine::play()
{
	sf::RenderWindow window(sf::VideoMode(500, 400), "Title");
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

			// pick up //
			
			if (e.type == sf::Event::MouseButtonPressed)
				if (e.key.code == sf::Mouse::Left)
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
				{
					dragging = false;
					
					//  + sf::Vector2f(25, 25) = "recenter piece"
					sf::Vector2f temp = ChessBoard.getPiece(draggedCoords)->getSprite().getPosition() + sf::Vector2f(25, 25);
					nextPosition = sf::Vector2f(50 * int(temp.x / 50), 50 * int(temp.y / 50));

					// convert move to chess notation
					std::string tempMove = convert2Chess(lastPosition) + convert2Chess(nextPosition);

					if (isValidMove(tempMove)) {
						ChessBoard.getPiece(draggedCoords)->getSprite().setPosition(nextPosition);
						ChessBoard.movePiece(tempMove);
						position += tempMove + " ";
						playerTurn = !playerTurn;
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
		
		if(dragging)
			ChessBoard.getPiece(draggedCoords)->getSprite().setPosition(mousePosition.x - draggingDistance.x, mousePosition.y - draggingDistance.y);
	
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (ChessBoard.getPiece(i, j))
					window.draw(ChessBoard.getPiece(i, j)->getSprite());
			}
		}
		//window.draw(ChessBoard.getPiece(draggedCoords)->getSprite());

		window.display();

		//////////
	}
}
