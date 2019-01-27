#include "coronation.h"

void coronation(Checker *crownPretendent, Queen *newQueen)
{
	newQueen->X = crownPretendent->X;
	newQueen->Y = crownPretendent->Y;
	crownPretendent->X = 0;
	crownPretendent->Y = 0;
	crownPretendent->isCoronated = true;
	if ((crownPretendent->value) == 1)
	{
		newQueen->value = 3;
	}
	else if ((crownPretendent->value) == 2)
	{
		newQueen->value = 4;
	}
}