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
#include <curses.h>
#include "basecreature.hpp"
#include "lowestcreature.hpp"
#include "highercreature.hpp"
#include "jecoconsole.h"


void display_init()
{
	initscr();
	cbreak();
	noecho(); 
	nodelay(stdscr, TRUE);
	start_color();
	clear();
        init_pair(1, COLOR_WHITE,   COLOR_BLACK);
        init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
   	init_pair(6, COLOR_RED,     COLOR_BLACK);
        init_pair(7, COLOR_GREEN,   COLOR_BLACK);
}

void get_screen_xy(unsigned int * px, unsigned int * py)
{
 	getmaxyx(stdscr, *py, *px);    
}

void Display_Lowest(unsigned int x_coord, unsigned int y_coord, bool fMature)
{
	attron(COLOR_PAIR(7));
	if (fMature)
	{
		mvprintw(y_coord, x_coord, "A");
	}
	else
	{
		mvprintw(y_coord, x_coord, "a");
	}
}

void Display_Higher(unsigned int x_coord, unsigned int y_coord, unsigned int level)
{
	attron(COLOR_PAIR(level % 6 + 1));
	mvprintw(y_coord, x_coord, "%c", 'A' + level);
}

void Simple_Display(base_creature_class *** creatures, unsigned int universe_age, 
		unsigned int creature_count, eco_option * poptions) 
{
	unsigned int xcount;
	unsigned int ycount;
	clear();
	for (ycount = 0; ycount < poptions->y; ycount++)
	{
		for (xcount = 0; xcount < poptions->x; xcount++)
		{
			if (creatures[xcount][ycount] != NULL)
			{
				if ((creatures[xcount][ycount])->getLevel())
				{
					Display_Higher(xcount, ycount, 
						(creatures[xcount][ycount])->getLevel());
				}
				else
				{
					Display_Lowest(xcount, ycount, 
						((lowest_creature *)creatures[xcount][ycount])->getMature());
				}
			}
			else
			{
				mvprintw(ycount, xcount, " ");
			}

		}
	}
	attron(COLOR_PAIR(1));
	if (poptions->display_age_flag)
	{
		mvprintw(poptions->y, 0, "%d", universe_age);
	}

	if (poptions->display_population_flag)
	{
		mvprintw(poptions->y, poptions->x/2, "population: %.4d", creature_count);
	}
	refresh();
}


void Display(base_creature_class *** new_universe, base_creature_class *** old_universe, 
		unsigned int universe_age, unsigned int creature_count, eco_option * poptions) 
{
	unsigned int xcount;
	unsigned int ycount;
	for (ycount = 0; ycount < poptions->y; ycount++)
	{
		for (xcount = 0; xcount < poptions->x; xcount++)
		{
			if (old_universe[xcount][ycount] != new_universe[xcount][ycount])
			{			
				if (new_universe[xcount][ycount] != NULL)
				{
					if ((new_universe[xcount][ycount])->getLevel())
					{
						Display_Higher(xcount, ycount, 
							(new_universe[xcount][ycount])->getLevel());
					}
				}
				else
				{
					mvprintw(ycount, xcount, " ");
				}
			}
			else
			{
				if (new_universe[xcount][ycount] != NULL)
				{
				
					if ((new_universe[xcount][ycount])->getLevel() == 0)
					{
			
							Display_Lowest(xcount, ycount, 
								((lowest_creature *)new_universe[xcount][ycount])->getMature());
					}
				}
			}
		}
	}
	attron(COLOR_PAIR(1));

	if (poptions->display_age_flag)
	{
		mvprintw(poptions->y, 0, "%d", universe_age);
	}

	if (poptions->display_population_flag)
	{
		mvprintw(poptions->y, poptions->x/2, "population: %.4d", creature_count);
	}
	refresh();
}

void end_display()
{
	endwin();
}
