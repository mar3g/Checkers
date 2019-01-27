#include <SFML/Graphics.hpp>
#include <fstream>
#include <Windows.h>

#include "BoardSquare.h"
#include "Menu.h"
#include "Figure.h"
#include "Checker.h"
#include "Queen.h"
#include "coronation.h"

using namespace sf;
using namespace std;

int sqsize = 100;
int radius = 40;
int border = 20;

int main()
{
	RenderWindow window(VideoMode(840, 840), "Checkers", Style::Titlebar | Style::Close); // RESIZING OF THE WINDOW IS BLOCKED

	Menu menu;

	ofstream wtfile;
	ifstream rffile;

	Texture tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8, tex9;
	tex1.loadFromFile("images/greenchecker.png");
	tex2.loadFromFile("images/redchecker.png");
	tex3.loadFromFile("images/greenqueen.png");
	tex4.loadFromFile("images/redqueen.png");
	tex5.loadFromFile("images/board.png");
	tex6.loadFromFile("images/chosengreen.png");
	tex7.loadFromFile("images/chosenred.png");
	tex8.loadFromFile("images/chosengreenqueen.png");
	tex9.loadFromFile("images/chosenredqueen.png");

	Sprite greenChecker(tex1), redChecker(tex2), greenQueen(tex3), redQueen(tex4), chosenGreen(tex6), chosenRed(tex7), chosenGreenQueen(tex8), chosenRedQueen(tex9);
	Sprite spriteBoard(tex5);

	BoardSquare Square[8][8];
	Checker checker[16];                    /////// 0-7 Green, 8-15 Red ////////
	Queen queen[16];
	Figure *figure_ptr[16];

	for (int i = 0; i < 16; i++)            /////// POLYMORPHIC POINTERS SETUP ///////
	{
		figure_ptr[i] = &checker[i];
	}

	for (int i = 0; i < 8; i++)             /////// GREEN CHECKERS STARTING VALUES ///////
	{
		checker[i].value = 1;
		checker[i].picture = greenChecker;
	}

	for (int i = 8; i < 16; i++)            /////// RED CHECKERS STARTING VALUES ///////
	{
		checker[i].value = 2;
		checker[i].picture = redChecker;
	}

	for (int i = 0; i < 8; i++)                 ///// BOARD SQUARES SETUP//////                             
		for (int j = 0; j < 8; j++)
		{
			Square[i][j].minX = i * sqsize + border;
			Square[i][j].maxX = (i + 1) * sqsize + border;
			Square[i][j].minY = j * sqsize + border;
			Square[i][j].maxY = (j + 1) * sqsize + border;
		}

	signed int chosenOne = -1;
	int howManyGreenDied = 0, howManyRedDied = 0;
	int iLoad = 0, whoseMove = 1; // whoseMove - odd(GREEN), even(RED)
	/******************************************************************************************************************************************************************************/

	while (window.isOpen())
	{
		Vector2i mousePosition = Mouse::getPosition(window);
		Event event1;

		if (menu.isMenu)  // MENU
		{
			while (window.pollEvent(event1))
			{
				if (event1.type == Event::KeyPressed && event1.key.code == Keyboard::Escape)
				{
					window.close();
				}

				if (event1.type == Event::MouseButtonPressed && event1.key.code == Mouse::Left)
				{
					if (mousePosition.x > 220 && mousePosition.x < 620 && mousePosition.y > 160 && mousePosition.y < 260)
					{
						// NEW GAME
						whoseMove = 1;
						for (int i = 0; i < 8; i++)             /////// GREEN CHECKERS STARTING VALUES ///////
						{
							checker[i].X = (i * sqsize) + border;
							if (i % 2 == 1)
							{
								checker[i].Y = border;
							}
							else
							{
								checker[i].Y = sqsize + border;
							}
						}

						for (int i = 8; i < 16; i++)            /////// RED CHECKERS STARTING VALUES ///////
						{
							checker[i].X = ((i % 8) * sqsize) + border;
							if (i % 2 == 1)
							{
								checker[i].Y = 6 * sqsize + border;
							}
							else
							{
								checker[i].Y = 7 * sqsize + border;
							}
						}
						menu.isMenu = false;
					}
					else if (mousePosition.x > 220 && mousePosition.x < 620 && mousePosition.y > 580 && mousePosition.y < 680)
					{
						// EXIT
						window.close();
					}
					else if (mousePosition.x > 220 && mousePosition.x < 620 && mousePosition.y > 370 && mousePosition.y < 470)
					{
						rffile.open("state.txt");
						if (rffile.good())
						{
							rffile >> whoseMove;
							rffile >> chosenOne;
							iLoad = 0;
							while (!rffile.eof())
							{
								rffile >> checker[iLoad].value >> checker[iLoad].X >> checker[iLoad].Y >> checker[iLoad].isCoronated;
								if (checker[iLoad].isCoronated == 1 && checker[iLoad].value == 1)
								{
									coronation(&checker[iLoad], &queen[iLoad]);
									queen[iLoad].picture = greenQueen;
									figure_ptr[iLoad] = &queen[iLoad];
								}
								else if (checker[iLoad].isCoronated == 1 && checker[iLoad].value == 2)
								{
									coronation(&checker[iLoad], &queen[iLoad]);
									queen[iLoad].picture = redQueen;
									figure_ptr[iLoad] = &queen[iLoad];
								}
								iLoad++;
							}
						}
						menu.isMenu = false;
						rffile.close();
					}
				}
			}
			menu.draw(window);
		}
		else if (!menu.isMenu) // GAME
		{
			while (window.pollEvent(event1))
			{
				if (event1.type == Event::KeyPressed && (event1.key.code == Keyboard::Escape || event1.key.code == Keyboard::S))    // LEAVE AND SAVE THE GAME
				{
					wtfile.open("state.txt");
					if (wtfile.good())
					{
						wtfile << whoseMove << endl;
						wtfile << chosenOne << endl;
						for (int i = 0; i < 16; i++)
						{
							if (figure_ptr[i]->value == 3)
							{
								wtfile << "1 " << figure_ptr[i]->X << " " << figure_ptr[i]->Y << " 1" << endl;
							}
							else if (figure_ptr[i]->value == 4)
							{
								wtfile << "2 " << figure_ptr[i]->X << " " << figure_ptr[i]->Y << " 1" << endl;
							}
							else
							{
								wtfile << checker[i].value << " " << checker[i].X << " " << checker[i].Y << " 0" << endl;
							}
						}
						wtfile.close();

						if (event1.key.code == Keyboard::Escape)
						{
							menu.isMenu = true;
						}
					}
				}

				/////// MOVEMENT ///////

				if (chosenOne == -1)
				{
					for (int i = 0; i < 16; i++)
					{
						if (event1.type == Event::MouseButtonPressed)
							if (event1.key.code == Mouse::Left)
								if (mousePosition.x >((figure_ptr[i]->X) + (sqsize / 2) - radius) && mousePosition.x < ((figure_ptr[i]->X) + (sqsize / 2) + radius)
									&& mousePosition.y >((figure_ptr[i]->Y) + (sqsize / 2) - radius) && mousePosition.y < ((figure_ptr[i]->Y) + (sqsize / 2) + radius)
									&& ((figure_ptr[i]->value%2 == whoseMove%2)))
								{
									chosenOne = i;
								}
					}
				}

				if (chosenOne != -1)
				{
					if (event1.type == Event::MouseButtonPressed)
						if (event1.key.code == Mouse::Left)
						{
							figure_ptr[chosenOne]->move(mousePosition, figure_ptr);
						}

					if ((figure_ptr[chosenOne]->isMoved) == true)
					{
						(figure_ptr[chosenOne]->isMoved) = false;
						whoseMove++;
						chosenOne = -1;
					}
				}
			}

			/******************************************************************************************************************************************************************************/

			/////// HIGHLIGHTING THE CHOSEN ONE ////////
			if (chosenOne != -1)
			{
				if ((figure_ptr[chosenOne]->value) == 1)
				{
					(figure_ptr[chosenOne]->picture) = chosenGreen;
				}
				else if ((figure_ptr[chosenOne]->value) == 2)
				{
					(figure_ptr[chosenOne]->picture) = chosenRed;
				}
				else if ((figure_ptr[chosenOne]->value) == 3)
				{
					(figure_ptr[chosenOne]->picture) = chosenGreenQueen;
				}
				else if ((figure_ptr[chosenOne]->value) == 4)
				{
					(figure_ptr[chosenOne]->picture) = chosenRedQueen;
				}
			}
			else
			{
				for (int i = 0; i < 16; i++)
				{
					if ((figure_ptr[i]->value) == 1)
					{
						(figure_ptr[i]->picture) = greenChecker;
					}
					else if ((figure_ptr[i]->value) == 2)
					{
						(figure_ptr[i]->picture) = redChecker;
					}
					else if ((figure_ptr[i]->value) == 3)
					{
						(figure_ptr[i]->picture) = greenQueen;
					}
					else if ((figure_ptr[i]->value) == 4)
					{
						(figure_ptr[i]->picture) = redQueen;
					}
				}
			}

			/////// CHANGING CHECKER INTO QUEEN ////////
			for (int i = 0; i < 8; i++)
			{
				if (checker[i].Y == 7 * sqsize + border)
				{
					coronation(&checker[i], &queen[i]);
					queen[i].picture = greenQueen;
					figure_ptr[i] = &queen[i];
				}
			}
			for (int i = 8; i < 16; i++)
			{
				if (checker[i].Y == border)
				{
					coronation(&checker[i], &queen[i]);
					queen[i].picture = redQueen;
					figure_ptr[i] = &queen[i];
				}
			}


			/////// DRAWING BOARD WITH RECENT POSITIONS ///////
			window.clear();
			window.draw(spriteBoard);

			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					for (int k = 0; k < 16; k++)
					{
						if ((figure_ptr[k]->X) + 1 >= Square[i][j].minX && (figure_ptr[k]->X) + 1 <= Square[i][j].maxX && (figure_ptr[k]->Y) + 1 >= Square[i][j].minY && (figure_ptr[k]->Y) + 1 <= Square[i][j].maxY)
						{
							(figure_ptr[k]->picture).setPosition(Square[i][j].minX, Square[i][j].minY);
							window.draw(figure_ptr[k]->picture);
						}
					}

			window.display();

			/////// GAME ENDING CONDITION ///////  
			for (int i = 0; i < 16; i++)
			{
				if (figure_ptr[i]->X == sqsize * sqsize)
				{
					if (figure_ptr[i]->value == 1 || figure_ptr[i]->value == 3)
					{
						howManyGreenDied++;
					}
					if (figure_ptr[i]->value == 2 || figure_ptr[i]->value == 4)
					{
						howManyRedDied++;
					}
				}
			}
			if (howManyGreenDied == 8)
			{
				/// GAME OVER, RED WINS
				Texture redTex;
				redTex.loadFromFile("images/redwin.png");
				Sprite redWin(redTex);
				window.clear();
				window.draw(redWin);
				window.display();
				Sleep(3000);
				window.close();
			}
			else if (howManyRedDied == 8)
			{
				/// GAME OVER, GREEN WINS
				Texture greenTex;
				greenTex.loadFromFile("images/greenwin.png");
				Sprite greenWin(greenTex);
				window.clear();
				window.draw(greenWin);
				window.display();
				Sleep(3000);
				window.close();
			}
			else
			{
				howManyGreenDied = 0;
				howManyRedDied = 0;
			}
		}
	}
	return 0;
}