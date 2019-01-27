#include "Queen.h"

	Queen::Queen() : onWay(false) {}

	bool Queen::checkCorrect(Figure *ptr[], int jumpedOne)
	{
		try  // USED TO EASILY LEAVE THE LOOP IF THE MOVE IS INCORRECT
		{
			for (int j = 0; j < 16; j++)
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
				if ((value == 3 && (ptr[jumpedOne]->value == 1 || ptr[jumpedOne]->value == 3))
					|| (value == 4 && (ptr[jumpedOne]->value == 2 || ptr[jumpedOne]->value == 4)))
				{
					throw 0;
				}
				/// CHECKING IF NOTHING WAS INBETWEEN
				for (int j = 0; j < 16; j++)
					for (int k = 1; k<8; k++)
					{
						if (((ptr[jumpedOne]->X > X && ptr[jumpedOne]->Y > Y) && (ptr[j]->X > X && ptr[j]->X < ptr[jumpedOne]->X && ptr[j]->Y > Y && ptr[j]->Y < ptr[jumpedOne]->Y) && (ptr[j]->X == X + k * sqsize) && (ptr[j]->Y == Y + k * sqsize))                  /// RIGHT DOWN
							|| ((ptr[jumpedOne]->X < X && ptr[jumpedOne]->Y > Y) && (ptr[j]->X < X && ptr[j]->X > ptr[jumpedOne]->X && ptr[j]->Y > Y && ptr[j]->Y < ptr[jumpedOne]->Y) && (ptr[j]->X == X - k * sqsize) && (ptr[j]->Y == Y + k * sqsize))           /// LEFT DOWN
							|| ((ptr[jumpedOne]->X > X && ptr[jumpedOne]->Y < Y) && (ptr[j]->X > X && ptr[j]->X < ptr[jumpedOne]->X && ptr[j]->Y < Y && ptr[j]->Y > ptr[jumpedOne]->Y) && (ptr[j]->X == X + k * sqsize) && (ptr[j]->Y == Y - k * sqsize))           /// RIGHT UP
							|| ((ptr[jumpedOne]->X < X && ptr[jumpedOne]->Y < Y) && (ptr[j]->X < X && ptr[j]->X > ptr[jumpedOne]->X && ptr[j]->Y < Y && ptr[j]->Y > ptr[jumpedOne]->Y) && (ptr[j]->X == X - k * sqsize) && (ptr[j]->Y == Y - k * sqsize)))          /// LEFT UP
						{
							throw 0;
						}
					}
			}
		}
		catch (int a)
		{
			return false;
		}
		return true;
	}

	void Queen::move(Vector2i mousePosition, Figure *ptr[])
	{
		for (int i = 1; i < 8; i++)
		{
			/// CHECKING IF PROPER SQUARE WAS CLICKED
			if ((mousePosition.x > border && mousePosition.x < 8 * sqsize + border && mousePosition.y > border && mousePosition.y < 8 * sqsize + border) &&     /// INSIDE OF BOARD
				(((mousePosition.x > X + i * sqsize && mousePosition.x < X + (i + 1) * sqsize) &&                   ////// DOWN RIGHT //////
				(mousePosition.y > Y + i * sqsize && mousePosition.y < Y + (i + 1) * sqsize))
					|| ((mousePosition.x > X - i * sqsize && mousePosition.x < X - (i - 1) * sqsize) &&             ////// DOWN LEFT ///////
					(mousePosition.y > Y + i * sqsize && mousePosition.y < Y + (i + 1) * sqsize))
					|| ((mousePosition.x > X + i * sqsize && mousePosition.x < X + (i + 1) * sqsize) &&             ////// UP RIGHT //////
					(mousePosition.y > Y - i * sqsize && mousePosition.y < Y - (i - 1)*sqsize))
					|| ((mousePosition.x > X - i * sqsize && mousePosition.x < X - (i - 1) * sqsize) &&             ////// UP LEFT ///////
					(mousePosition.y > Y - i * sqsize && mousePosition.y < Y - (i - 1)*sqsize))))
			{
				for (int j = 0; j < 16; j++)
				{
					if (mousePosition.x > ptr[j]->X && mousePosition.x < ptr[j]->X + sqsize && mousePosition.y >ptr[j]->Y && mousePosition.y < ptr[j]->Y + sqsize)      /// CLICKED ON OTHER CHECKER
					{
						interaction = true;
						jumpedOne = j;
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
					interaction = false;
					isCorrect = true;
					break;
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

					interaction = false;
					isCorrect = true;
					break;
				}
				else if (!interaction && !anotherJump)
				{
					/// MOVEMENT WITHOUT INTERACTION
					for (int j = 0; j < 16; j++)
					{
						for (int k = 1; k < 8; k++)
						{
							if (((mousePosition.x > X && mousePosition.y > Y) && (ptr[j]->X > X && ptr[j]->X < mousePosition.x && ptr[j]->Y > Y && ptr[j]->Y < mousePosition.y) && (ptr[j]->X == X + k * sqsize) && (ptr[j]->Y == Y + k * sqsize))              /// RIGHT DOWN
								|| ((mousePosition.x < X && mousePosition.y > Y) && (ptr[j]->X < X && ptr[j]->X > mousePosition.x && ptr[j]->Y > Y && ptr[j]->Y < mousePosition.y) && (ptr[j]->X == X - k * sqsize) && (ptr[j]->Y == Y + k * sqsize))           /// LEFT DOWN
								|| ((mousePosition.x > X && mousePosition.y < Y) && (ptr[j]->X > X && ptr[j]->X < mousePosition.x && ptr[j]->Y < Y && ptr[j]->Y > mousePosition.y) && (ptr[j]->X == X + k * sqsize) && (ptr[j]->Y == Y - k * sqsize))           /// RIGHT UP
								|| ((mousePosition.x < X && mousePosition.y < Y) && (ptr[j]->X < X && ptr[j]->X > mousePosition.x && ptr[j]->Y < Y && ptr[j]->Y > mousePosition.y) && (ptr[j]->X == X - k * sqsize) && (ptr[j]->Y == Y - k * sqsize)))          /// LEFT UP
							{
								/// SOMETHING WAS ON THE WAY
								onWay = true;
								break;
							}
						}
						if (onWay)
						{
							break;
						}
					}

					if (onWay)
					{
						isMoved = false;
					}
					else
					{
						isMoved = true;
					}

					if (isMoved)
					{
						X = ((int)((mousePosition.x - border) / sqsize)) * sqsize + border;
						Y = ((int)((mousePosition.y - border) / sqsize)) * sqsize + border;
					}

					interaction = false;
					isCorrect = true;
					onWay = false;
					break;
				}
			}
		}
	}
