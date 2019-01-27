#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "Figure.h"
#include "Queen.h"

using namespace sf;
using namespace std;

class Checker;

class Queen : public Figure
{
	bool onWay;
public:
	Queen();
	bool checkCorrect(Figure*[], int);
	void move(Vector2i, Figure *[]);
	friend void coronation(Checker*, Queen*);
};

