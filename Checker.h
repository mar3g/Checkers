#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "Figure.h"
#include "Checker.h"

using namespace sf;
using namespace std;

class Queen;

class Checker : public Figure
{
public:
	bool checkCorrect(Figure *[], int);
	void move(Vector2i, Figure *[]);
	friend void coronation(Checker*, Queen*);
};

