#include "Checker.h"
//#include "main.cpp"

	bool Checker::checkCorrect(Figure *ptr[], int jumpedOne)
	{
		try  // USED TO EASILY LEAVE THE LOOP IF THE MOVE IS INCORRECT
		{
			/// CHECKING IF THERE IS A WALL BEHIND POTENTIAL JUMP
			if ((ptr[jumpedOne]->X > X && ptr[jumpedOne]->Y > Y && (ptr[jumpedOne]->X + 1 + sqsize > 8 * sqsize + border || ptr[jumpedOne]->Y + 1 + sqsize > 8 * sqsize + border))      /// RIGHT DOWN BORDER
				|| (ptr[jumpedOne]->X < X && ptr[jumpedOne]->Y > Y && (ptr[jumpedOne]->X - 1 < border || ptr[jumpedOne]->Y + 1 + sqsize > 8 * sqsize + border))                         /// LEFT DOWN BORDER
				|| (ptr[jumpedOne]->X > X && ptr[jumpedOne]->Y < Y && (ptr[jumpedOne]->X + 1 + sqsize > 8 * sqsize + border || ptr[jumpedOne]->Y - 1 < border))                         /// RIGHT UP BORDER
				|| (ptr[jumpedOne]->X < X && ptr[jumpedOne]->Y < Y && (ptr[jumpedOne]->X - 1 < border || ptr[jumpedOne]->Y - 1 < border)))                                              /// LEFT UP BORDER
			{
				throw 0;
			}
			/// CHECKING IF JUMP IS NOT BLOCKED BY OTHER CHECKER
			for (int j = 0; j < 16; j++)
			{
				if ((ptr[jumpedOne]->X > X && ptr[jumpedOne]->Y > Y) && (ptr[jumpedOne]->X + sqsize == ptr[j]->X  && ptr[jumpedOne]->Y + sqsize == ptr[j]->Y)
					|| (ptr[jumpedOne]->X < X && ptr[jumpedOne]->Y > Y) && (ptr[jumpedOne]->X - sqsize == ptr[j]->X && ptr[jumpedOne]->Y + sqsize == ptr[j]->Y)
					|| (ptr[jumpedOne]->X > X && ptr[jumpedOne]->Y < Y) && (ptr[jumpedOne]->X + sqsize == ptr[j]->X && ptr[jumpedOne]->Y - sqsize == ptr[j]->Y)
					|| (ptr[jumpedOne]->X < X && ptr[jumpedOne]->Y < Y) && (ptr[jumpedOne]->X - sqsize == ptr[j]->X && ptr[jumpedOne]->Y - sqsize == ptr[j]->Y))
				{
					throw 0;
				}
			}
			/// CHECKING IF NOT THE SAME COLOUR
			if ((value == 1 && (ptr[jumpedOne]->value == 1 || ptr[jumpedOne]->value == 3))
				|| (value == 2 && (ptr[jumpedOne]->value == 2 || ptr[jumpedOne]->value == 4)))
			{
				throw 0;
			}
		}
		catch (int a)
		{
			return false;
		}
		return true;
	}

	void Checker::move(Vector2i mousePosition, Figure *ptr[])
	{
		if (mousePosition.x > border && mousePosition.x < 8 * sqsize + border && mousePosition.y > border && mousePosition.y < 8 * sqsize + border)                     /// INSIDE of BOARD
			if ((mousePosition.x > X + sqsize && mousePosition.x < X + 2 * sqsize && mousePosition.y > Y + sqsize && mousePosition.y < Y + 2 * sqsize)                  /// PROPER MOVE (ADJOINT SQUARE)
				|| (mousePosition.x > X - sqsize && mousePosition.x < X && mousePosition.y > Y + sqsize && mousePosition.y < Y + 2 * sqsize)
				|| (mousePosition.x > X + sqsize && mousePosition.x < X + 2 * sqsize && mousePosition.y > Y - sqsize && mousePosition.y < Y)
				|| (mousePosition.x > X - sqsize && mousePosition.x < X && mousePosition.y > Y - sqsize && mousePosition.y < Y))
			{
				{
					for (int i = 0; i < 16; i++)
					{
						if (mousePosition.x > ptr[i]->X && mousePosition.x < ptr[i]->X + sqsize && mousePosition.y >ptr[i]->Y && mousePosition.y < ptr[i]->Y + sqsize)      /// CLICKED ON OTHER CHECKER
						{
							interaction = true;
							jumpedOne = i;
							break;
						}
					}
					if (interaction)
					{
						isCorrect = checkCorrect(ptr, jumpedOne);
					}
					if (interaction && !isCorrect)
					{
						/// INCORRECT ATTEMPT TO JUMP
						isMoved = false;
					}
					else if (interaction && isCorrect)
					{
						/// JUMP
						if (ptr[jumpedOne]->X > X && ptr[jumpedOne]->Y > Y)                                 /// RIGHT DOWN
						{
							X = ((int)((mousePosition.x - border) / sqsize)) * sqsize + border + sqsize;
							Y = ((int)((mousePosition.y - border) / sqsize)) * sqsize + border + sqsize;
						}
						else if (ptr[jumpedOne]->X < X && ptr[jumpedOne]->Y > Y)                            /// LEFT DOWN
						{
							X = ((int)((mousePosition.x - border) / sqsize)) * sqsize + border - sqsize;
							Y = ((int)((mousePosition.y - border) / sqsize)) * sqsize + border + sqsize;
						}
						else if (ptr[jumpedOne]->X > X && ptr[jumpedOne]->Y < Y)                            /// RIGHT UP
						{
							X = ((int)((mousePosition.x - border) / sqsize)) * sqsize + border + sqsize;
							Y = ((int)((mousePosition.y - border) / sqsize)) * sqsize + border - sqsize;
						}
						else if (ptr[jumpedOne]->X < X && ptr[jumpedOne]->Y < Y)                            /// LEFT UP
						{
							X = ((int)((mousePosition.x - border) / sqsize)) * sqsize + border - sqsize;
							Y = ((int)((mousePosition.y - border) / sqsize)) * sqsize + border - sqsize;
						}
						(ptr[jumpedOne]->X) = sqsize * sqsize;

						/// CHECKING IF ANOTHER JUMP IS POSSIBLE
						for (int i = 0; i < 16; i++)
						{
							if ((X + sqsize == ptr[i]->X && Y + sqsize == ptr[i]->Y)
								|| (X - sqsize == ptr[i]->X && Y + sqsize == ptr[i]->Y)
								|| (X + sqsize == ptr[i]->X && Y - sqsize == ptr[i]->Y)
								|| (X - sqsize == ptr[i]->X && Y - sqsize == ptr[i]->Y))
							{
								if (checkCorrect(ptr, i))
								{
									// IF POSSIBLE
									anotherJump = true;
									isMoved = false;
									break;
								}
							}
							else
							{
								anotherJump = false;
								isMoved = true;
							}
						}
					}
					else if (!interaction && !anotherJump)
					{
						// MOVEMENT WITHOUT INTERACTION
						if ((value == 1 && mousePosition.y > Y)
							|| (value == 2 && mousePosition.y < Y))
						{
							X = ((int)((mousePosition.x - border) / sqsize)) * sqsize + border;
							Y = ((int)((mousePosition.y - border) / sqsize)) * sqsize + border;
							isMoved = true;
						}
					}
					interaction = false;
					isCorrect = true;
				}
			}
	}

