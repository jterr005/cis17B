#include "Ghost.h"
#include "GhostMap.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


Ghost::Ghost()
{
}

//moves 0up, 1down, 2left, 3right
//change to enum later
void Ghost::udlr()
{
	int rmove;

	srand(time(NULL));

	rmove = (rand() % 3);

	if ( rmove== 0)
	{
		dir = 0;
	}
	else if (rmove == 1)
	{
		dir = 1;
	}
	if (rmove == 2)
	{
		dir = 2;
	}
	else if (rmove == 3)
	{
		dir = 3;
	}

}

//what happens when it hits a wall
void Ghost::move(int num)
{
	GameMap graph;

	int a, b;
	if (num == 0)
	{
		if (graph.at(240) != HORIHALL || VERTHALL)
		{
			graph.at(240+1) = 'G';

			if (graph.at(240) == HORIHALL)
			{
				a = rand() % 2;
				switch (a)
				{
				case 0:
					dir = 0;
					break;
				case 1:
					dir = 1;
					break;
				}
			}
			else if (graph.at(240) == VERTHALL)
			{
				b = rand() % 2;
				switch (b)
				{
				case 0:
					dir = 2;
					break;
				case 1:
					dir = 3;
					break;
				}
			}

			
		}

	}

	if (num == 1)
	{
		if (graph.at(240) != HORIHALL || VERTHALL)
		{
			graph.at(240 + 1) = 'G';

			if (graph.at(240) == HORIHALL)
			{
				a = rand() % 2;
				switch (a)
				{
				case 0:
					dir = 0;
					break;
				case 1:
					dir = 1;
					break;
				}
			}
			else if (graph.at(240) == VERTHALL)
			{
				b = rand() % 2;
				switch (b)
				{
				case 0:
					dir = 2;
					break;
				case 1:
					dir = 3;
					break;
				}
			}

		}
	}

	if (num == 2)
	{
		if (graph.at(240) != HORIHALL || VERTHALL)
		{
			graph.at(240 + 1) = 'G';

			if (graph.at(240) == HORIHALL)
			{
				a = rand() % 2;
				switch (a)
				{
				case 0:
					dir = 0;
					break;
				case 1:
					dir = 1;
					break;
				}
			}
			else if (graph.at(240) == VERTHALL)
			{
				b = rand() % 2;
				switch (b)
				{
				case 0:
					dir = 2;
					break;
				case 1:
					dir = 3;
					break;
				}
			}

		}
	}

	if (num == 3)
	{
		if (graph.at(240) != HORIHALL || VERTHALL)
		{
			graph.at(240 + 1) = 'G';

			if (graph.at(240) == HORIHALL)
			{
				a = rand() % 2;
				switch (a)
				{
				case 0:
					dir = 0;
					break;
				case 1:
					dir = 1;
					break;
				}
			}
			else if (graph.at(240) == VERTHALL)
			{
				b = rand() % 2;
				switch (b)
				{
				case 0:
					dir = 2;
					break;
				case 1:
					dir = 3;
					break;
				}
			}

		}
	}


}


