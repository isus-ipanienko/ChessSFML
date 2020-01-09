#include "GameEngine.h"

GameEngine::GameEngine()
{
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
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}



		// draw //

		window.clear();

		window.draw(Background);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (ChessBoard.getPiece(i, j))
					window.draw(ChessBoard.getPiece(i, j)->getSprite());
			}
		}

		window.display();
	}
}
