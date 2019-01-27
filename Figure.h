#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

using namespace sf;
using namespace std;

extern int sqsize;
extern int radius;
extern int border;

class Figure
{
public:
	bool isCoronated;
	int X, Y;
	int value;
	int jumpedOne;
	bool isMoved, interaction, isCorrect, anotherJump;
	Sprite picture;
	virtual void move(Vector2i mousePosition, Figure *ptr[]) = 0;
	virtual bool checkCorrect(Figure*[], int) = 0;
	Figure();
};

