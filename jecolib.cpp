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

#include <stdlib.h>
#include <time.h>
#include "lowestcreature.hpp"
#include "highercreature.hpp"
#include "jecoconsole.h"
#include "jecolib.h"

void Delay(float dtime)
{
	unsigned long start;
	unsigned long finish;

	start = clock();
	do
	{
		finish = clock();

	}while((finish - start)/(float) CLOCKS_PER_SEC < dtime);
}

void initialize_universe(base_creature_class **** pcreatures, eco_option * poptions)
{
	unsigned long xcount;
	unsigned long ycount;
	*pcreatures = new base_creature_class **[poptions->x];
	for (xcount = 0; xcount < poptions->x; xcount++)
	{
		(*pcreatures)[xcount] = new base_creature_class *[poptions->y];
		for (ycount = 0; ycount < poptions->y; ycount++)
		{
			(*pcreatures)[xcount][ycount] = NULL;
		}
	}
}

void remove_dead_bodies(base_creature_class *** creatures, unsigned int x, unsigned int y)
{
	unsigned int xcount;
	unsigned int ycount;

	for (ycount = 0; ycount < y; ycount++)
	{
		for (xcount = 0; xcount < x; xcount++)
		{
			if (creatures[xcount][ycount] != NULL)
			{	
				if ((creatures[xcount][ycount])->getLevel())
				{
					if (!(((higher_creature *)creatures[xcount][ycount])->getAlive()))
					{
						delete creatures[xcount][ycount];
						creatures[xcount][ycount] = NULL;
					}
				}
			}
		}
	}
}

void update_universe(base_creature_class *** creatures, base_creature_class *** new_universe, eco_option * poptions)
{
	unsigned int xcount;
	unsigned int ycount;
	char error_string[255];

	for (ycount = 0; ycount < poptions->y; ycount++)
	{
		for (xcount = 0; xcount < poptions->x; xcount++)
		{
			if (creatures[xcount][ycount] != NULL)
			{	
				if ((creatures[xcount][ycount])->getLevel())
				{
					if (((higher_creature *)creatures[xcount][ycount])->getAlive())
					{
						(creatures[xcount][ycount])->Update(creatures, new_universe, poptions);
					}
				}
				else
				{
					(creatures[xcount][ycount])->Update(creatures, new_universe, poptions);
				}	
			}
		}
	}
}

bool universe_is_alive(base_creature_class *** creatures, unsigned int x, unsigned int y)
{
	unsigned int xcount;
	unsigned int ycount;

	for (ycount = 0; ycount < y; ycount++)
	{
		for (xcount = 0; xcount < x; xcount++)
		{
			if (creatures[xcount][ycount] != NULL)
			{
				if ((creatures[xcount][ycount])->getLevel() > 0)
				{
					return true;
				}	
			}
		}
	}
	return false;
}

unsigned int get_animate_population(base_creature_class *** creatures, unsigned int x, unsigned int y)
{
	unsigned int xcount;
	unsigned int ycount;
	unsigned int creature_count = 0;

	for (ycount = 0; ycount < y; ycount++)
	{
		for (xcount = 0; xcount < x; xcount++)
		{
			if (creatures[xcount][ycount] != NULL)
			{
				if ((creatures[xcount][ycount])->getLevel() > 0)
				{
					creature_count++;
				}	
			}
		}
	}
	return creature_count;
}

base_creature_class *** copy_universe(base_creature_class *** creatures, unsigned int x, unsigned int y)
{
	unsigned long xcount;
	unsigned long ycount;
	base_creature_class *** new_universe;
	new_universe = new base_creature_class **[x];
	for (xcount = 0; xcount < x; xcount++)
	{
		new_universe[xcount] = new base_creature_class *[y];
		for (ycount = 0; ycount < y; ycount++)
		{
			new_universe[xcount][ycount] = creatures[xcount][ycount];
		}
	}
	return new_universe;
	
}

void cleanup_universe(base_creature_class **** pcreatures, unsigned int x, unsigned int y, bool destroy_creatures)
{
	unsigned long xcount;
	unsigned long ycount;
	for (xcount = 0; xcount < x; xcount++)
	{
		for (ycount = 0; ycount < y; ycount++)
		{
			if (destroy_creatures)
			{
				if ((*pcreatures)[xcount][ycount] != NULL)
				{
					delete (*pcreatures)[xcount][ycount];
				}
			}
		}
		delete (*pcreatures)[xcount];
	}
	delete *pcreatures;
}



void seed_universe(base_creature_class *** creatures, eco_option * poptions)
{
	create_creatures(creatures, poptions->number_of_base_life, 0, poptions);
	create_creatures(creatures, poptions->number_of_higher_life, 1, poptions);
}

void create_creatures(base_creature_class *** creatures, unsigned int num_creatures, 
		unsigned int level, eco_option * poptions)
{
	unsigned int creature_count, temp_x, temp_y;
	bool creature_not_created;
	for (creature_count = 0; creature_count < num_creatures; creature_count++)
	{
		creature_not_created = true;
		while (creature_not_created)
		{
			temp_x = (int)((double)(poptions->x)*(rand()/(double)RAND_MAX));
			temp_y = (int)((double)(poptions->y)*(rand()/(double)RAND_MAX));
			if (creatures[temp_x][temp_y] == NULL)
			{
				if (level == 0)
				{
					creatures[temp_x][temp_y] = new lowest_creature;
					((lowest_creature *)creatures[temp_x][temp_y])->setMaturityThres(poptions->maturity_cycle);
				}
				else
				{
					creatures[temp_x][temp_y] = new higher_creature(poptions->initial_turns_without_food,
							poptions->reproduction_thres);
				}	
				(creatures[temp_x][temp_y])->setLevel(level);
				(creatures[temp_x][temp_y])->setX(temp_x);
				(creatures[temp_x][temp_y])->setY(temp_y);
				creature_not_created = false;
			}
		}
	}
}

void log_to_file(ofstream * pfile, base_creature_class *** creatures, eco_option * poptions)
{
	unsigned int i,x,y, levels[26];
	for (i=0; i<26; i++)
	{
		levels[i]=0;
	}
	for (y = 0; y < poptions->y; y++)
	{
		for (x = 0; x < poptions->x; x++)
		{
			if (creatures[x][y] != NULL) 
			{
				levels[(creatures[x][y])->getLevel()]++;
			}
		}
	}
	for (i=0; i<26; i++)
	{
		(*pfile) << levels[i] << " ";
	}
	(*pfile) << '\n';
	pfile->flush();
}	
