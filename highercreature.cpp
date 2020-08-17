/*
Copyright (C) 2005  James Hamilton

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include <stdio.h>
#include <stdlib.h>
#include "lowestcreature.hpp"
#include "highercreature.hpp"

higher_creature::higher_creature(unsigned int maxturns, unsigned int repro)
{
	alive = true;
	max_turns_without_food = maxturns;
	turns_without_food = 0;
	food_count = 0;
	repro_thres = repro;
}

bool higher_creature::getAlive()
{
	return alive;
}

void higher_creature::setDead()
{
	alive = false;
}


void higher_creature::Reproduce(base_creature_class *** new_universe, eco_option * poptions)
{
	unsigned int creature_count, delta_x, delta_y, new_level, repro_roll;
	long tempx, tempy;
	for (creature_count = 0; creature_count < poptions->max_offspring; creature_count++)
	{
		delta_x = (int)((double)3*(rand()/(double)RAND_MAX));
		delta_y = (int)((double)3*(rand()/(double)RAND_MAX));
		delta_x--;
		delta_y--;
		tempx = getX() + delta_x;
		tempy = getY() + delta_y;
		if (!((tempx < 0) || (tempy < 0) || (tempy >= poptions->y) || (tempx >= poptions->x)))
		{
			if (new_universe[tempx][tempy] == NULL)
			{
				new_universe[tempx][tempy] = new higher_creature(max_turns_without_food + 1, repro_thres);
				new_level = getLevel();
				if (poptions->mutates_flag)
				{
					repro_roll = (int)((double)100*(rand()/(double)RAND_MAX));
					if (repro_roll < poptions->mutation1)
					{
						new_level++;
					}
					else if (repro_roll <= poptions->mutation1 + poptions->mutation2)
					{
						new_level += 2;
					}
					else if (repro_roll <= poptions->mutation1 + poptions->mutation2 + poptions->mutation3)
					{
						new_level += 3;
					}
				}

				(new_universe[tempx][tempy])->setLevel(new_level);
				(new_universe[tempx][tempy])->setX(tempx);
				(new_universe[tempx][tempy])->setY(tempy);
			}
		}
	}
}


bool find_alternate_move(base_creature_class *** creatures, unsigned int x, unsigned int y, 
			int * pdeltax, int * pdeltay, int xmax, int ymax)
{
	/*
	-1 -1
	-1  0
	-1  1
	 0 -1
	 0  1
	 1 -1
	 1  0
	 1  1*/
	if (*pdeltax == -1)
	{
		if (*pdeltay == -1)
		{
			if (x != 0)
			{
				if (creatures[x-1][y] == NULL)
				{
					*pdeltay = 0;
					return true;
				}
			}
			if (y < ymax - 1)
			{
				if (creatures[x][y-1] == NULL)
				{
					*pdeltax = 0;
					return true;
				}
			}
			return false;
		}
		if (*pdeltay == 0)
		{
			if ((x != 0) && (y < ymax - 1))
			{	
				if (creatures[x-1][y+1] == NULL)
				{
					*pdeltay = 1;
					return true;
				}
			}
			if ((x != 0) && (y != 0))
			{
				if (creatures[x-1][y-1] == NULL)
				{
					*pdeltay = -1;
					return true;
				}
			}
			return false;
		}
		if (*pdeltay == 1)
		{
			if (y < ymax - 1)
			{
				if (creatures[x][y+1] == NULL)
				{
					*pdeltax = 0;
					return true;
				}
			}
			if (x != 0)
			{
				if (creatures[x-1][y] == NULL)
				{
					*pdeltay = 0;
					return true;
				}
			}
			return false;
		}
		return false;
	}
	if (*pdeltax == 0)
	{
		if (*pdeltay == 1)
		{
			if ((x < xmax - 1) && (y < ymax - 1))
			{
				if (creatures[x+1][y+1] == NULL)
				{
					*pdeltax = 1;
					return true;
				}
			}
			if ((x != 0) && (y < ymax - 1))
			{
				if (creatures[x-1][y+1] == NULL)
				{
					*pdeltax = -1;
					return true;
				}
			}
		}
		if (*pdeltay == -1)
		{
			if ((x < xmax - 1) && (y != 0))
			{
				if (creatures[x+1][y-1] == NULL)
				{
					*pdeltax = 1;
					return true;
				}
			}
			if ((x != 0) && (y != 0))
			{
				if (creatures[x-1][y-1] == NULL)
				{
					*pdeltax = -1;
					return true;
				}
			}
		}
		return false;
	}
	if (*pdeltax == 1)
	{
		if (*pdeltay == -1)
		{
			if (x < xmax - 1)
			{
				if (creatures[x+1][y] == NULL)
				{
					*pdeltay = 0;
					return true;
				}
			}
			if (y != 0)
			{
				if (creatures[x][y-1] == NULL)
				{
					*pdeltax = 0;
					return true;
				}
			}
			return false;
		}
		if (*pdeltay == 0)
		{
			if ((x < xmax - 1) && (y < ymax - 1))
			{
				if (creatures[x+1][y+1] == NULL)
				{
					*pdeltay = 1;
					return true;
				}
			}
			if ((x < xmax - 1) && (y != 0))
			{
				if (creatures[x+1][y-1] == NULL)
				{
					*pdeltay = -1;
					return true;
				}
			}
			return false;
		}
		if (*pdeltay == 1)
		{
			if (y < ymax - 1)
			{
				if (creatures[x][y+1] == NULL)
				{
					*pdeltax = 0;
					return true;
				}
			}
			if (x < xmax - 1)
			{
				if (creatures[x+1][y] == NULL)
				{
					*pdeltay = 0;
					return true;
				}
			}
			return false;
		}
		return false;
	}
	return false;
}

void higher_creature::Update(base_creature_class *** creatures, base_creature_class *** new_universe, eco_option * poptions)
{
	unsigned int xcount, ycount;
	unsigned int currentx, currenty;

	long xnearest = -1, ynearest = -1;

	unsigned int largest;

	bool isFood;

	int deltax = 0, deltay = 0;
	
	currentx = getX();
	currenty = getY();
	
	age++;


	for (ycount = 0; ycount < poptions->y; ycount++)
	{
		for (xcount = 0; xcount < poptions->x; xcount++)
		{
			if (creatures[xcount][ycount] != NULL)
			{
				isFood = false;
				if (((creatures[xcount][ycount])->getLevel() < getLevel()) &&
					(getLevel() - (creatures[xcount][ycount])->getLevel() < poptions->eats_below + 1))
				{
					if ((creatures[xcount][ycount])->getLevel() == 0)
					{
						if (((lowest_creature *)creatures[xcount][ycount])->getMature())
						{
							isFood = true;
						}
					}
					else
					{
						isFood = true;
					}
				}
				if (isFood)
				{
					if (xnearest == -1)
					{
						xnearest = xcount;
						ynearest = ycount;
						if (labs((long)currentx - (long)xcount) > labs((long)currenty - (long)ycount))
						{
							largest = labs((long)currentx - (long)xcount);
						}
						else
						{
							largest = labs((long)currenty - (long)ycount);
						}
					}
					else
					{
						if (labs((long)currentx - (long)xcount) > labs((long)currenty - (long)ycount))
						{
							if (labs((long)currentx - (long)xcount) < largest)
							{
								xnearest = xcount;
								ynearest = ycount;
								largest = labs((long)currentx - (long)xcount);
							}	
						}
						else
						{
							if (labs((long)currenty - (long)ycount) < largest)
							{
								xnearest = xcount;
								ynearest = ycount;
								largest = labs((long)currenty - (long)ycount);
							}	
						}
					}
					
				}
			}
		}
	}
	if (poptions->distance>0)
  	{
    		if (largest > poptions->distance)
      		{
			xnearest=-1;
			ynearest=-1;
      		}
  	}
	if (xnearest != -1)
	{
		if (largest == 1)
		{
			food_count++;
			turns_without_food = 0;
			if ((creatures[xnearest][ynearest])->getLevel() == 0)
			{
				((lowest_creature *)creatures[xnearest][ynearest])->setImmature();	
				
			}
			else
			{
				((higher_creature *)creatures[xnearest][ynearest])->setDead();
			}
			if (food_count == repro_thres)
			{
				Reproduce(new_universe, poptions);
				food_count = 0;
			}
		
		}
		else
		{
			turns_without_food++;
			if (turns_without_food == max_turns_without_food)
			{
				alive = false;
				return;
			}
			deltax = 0;
			deltay = 0;
			if (currentx > xnearest)
			{
				deltax = -1;
			}
			else if (currentx < xnearest)
			{
				deltax = 1;
			}
			if (currenty > ynearest)
			{
				deltay = -1;
			}
			else if (currenty < ynearest)
			{
				deltay = 1;
			}

			

			if (((currentx + deltax) >= 0) && ((currentx + deltax) < poptions->x) &&
				((currenty + deltay) >= 0) && ((currenty + deltay) < poptions->y))
			{
				if (new_universe[currentx + deltax][currenty + deltay] != NULL)
				{
					find_alternate_move(new_universe, currentx, currenty, 
						&deltax, &deltay, poptions->x, poptions->y);
				}

				if (new_universe[currentx + deltax][currenty + deltay] == NULL)
				{
					new_universe[currentx + deltax][currenty + deltay] = creatures[currentx][currenty];
					new_universe[currentx][currenty] = NULL;
					setX(currentx + deltax);
					setY(currenty + deltay);
				}
			}
		}
	}
	else
	{
		turns_without_food++;
		if (turns_without_food == max_turns_without_food)
		{
			alive = false;
		}
	}
}
