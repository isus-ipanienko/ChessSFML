#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
	sf::Event e;

	// char to int test
	char a = 'a';
	std::cout << int(a);
	// result =>  a = 97

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}
	}
}
