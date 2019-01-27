#include "Menu.h"

	Menu::Menu() : isMenu(true)
	{
		newGameTex.loadFromFile("images/newgame.png");
		loadGameTex.loadFromFile("images/loadgame.png");
		exitTex.loadFromFile("images/exit.png");

		newGame.setTexture(newGameTex);
		loadGame.setTexture(loadGameTex);
		exit.setTexture(exitTex);

		newGame.setPosition(220, 160);
		loadGame.setPosition(220, 370);
		exit.setPosition(220, 580);
	}

	void Menu::draw(RenderWindow &window)
	{
		window.clear();
		window.draw(newGame);
		window.draw(loadGame);
		window.draw(exit);
		window.display();
	}