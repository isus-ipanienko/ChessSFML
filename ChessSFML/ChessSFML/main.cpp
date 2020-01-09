#include <iostream>
#include "GameEngine.h"

int main()
{
	GameEngine chess = GameEngine();
	chess.play();

	// char to int test
	char a = 'a';
	std::cout << int(a);
	// result =>  a = 97

}
