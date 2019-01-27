#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

using namespace sf;
using namespace std;

class Menu
{
public:
	Texture newGameTex, loadGameTex, exitTex;
	Sprite newGame, loadGame, exit;
	bool isMenu;

	Menu();
	void draw(RenderWindow &);
};

