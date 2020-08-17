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
#include <string.h>
#include "jecoopt.h"
#include "jecolib.h"
#include "jecoconsole.h"
#include "universe.hpp"

universe::universe()
{
	poptions = new eco_option;
	initialize_options(poptions);
	init_universe();
}

universe::universe(eco_option * poptions_in)
{
	poptions = new eco_option;
	memcpy(poptions, poptions_in, sizeof(eco_option));
	init_universe();
}

void universe::init_universe()
{
	display_init();
	get_screen_xy(&screen_x, &screen_y);
	if (poptions->x == 0)
	{
		poptions->x = screen_x;
	}

	if (poptions->y == 0)
	{
		poptions->y = screen_y;
		poptions->y -= 2;
	}
	if (poptions->iterations > 0)
	{
		iterations = poptions->iterations;
	}
	else
	{
		iterations = 1;
	}

	srand(poptions->seed);
	if (poptions->log) 
	{
		logfile.open("jecology.log",ios::out | ios::trunc);
		if (!logfile.is_open()) 
		{
			printf("Problem opening the logfile.  Exiting\n");
			exit(1);
		}
	}
}


void universe::initialize_universe_data()
{
	::initialize_universe(&universe_data, poptions);
}

void universe::seed_universe_data()
{
	::seed_universe(universe_data, poptions);
}

void universe::create_creatures(unsigned int num_creatures, unsigned int level)
{
	::create_creatures(universe_data, num_creatures, level, poptions);
}

void universe::remove_dead_bodies(base_creature_class *** new_universe_data)
{
	::remove_dead_bodies(new_universe_data, poptions->x, poptions->y);
}

bool universe::universe_is_alive()
{
	return ::universe_is_alive(universe_data, poptions->x, poptions->y);
}
	
unsigned int universe::get_animate_population()
{
	return ::get_animate_population(universe_data, poptions->x, poptions->y);
}

base_creature_class *** universe::copy_universe_data()
{
	return ::copy_universe(universe_data, poptions->x, poptions->y);
}

void universe::update_universe_data(base_creature_class *** new_universe)
{
	update_universe(universe_data, new_universe, poptions);
}

void universe::cleanup_universe_data(bool destroy_creatures)
{
	::cleanup_universe(&universe_data, poptions->x, poptions->y, destroy_creatures);
}

void universe::cleanup_universe_data(base_creature_class **** puniverse_data, bool destroy_creatures)
{
	::cleanup_universe(puniverse_data, poptions->x, poptions->y, destroy_creatures);
}

void universe::update()
{
	base_creature_class *** new_universe_data;

	if (poptions->log)
	{
		log_to_file(&logfile, universe_data, poptions);
	}

	new_universe_data = copy_universe_data();
	update_universe_data(new_universe_data);
	remove_dead_bodies(new_universe_data);
	creature_count = get_animate_population();
	Display(new_universe_data, universe_data, universe_age, creature_count, poptions);
	cleanup_universe_data(false);
	universe_data = new_universe_data;
}

void universe::run()
{
	unsigned int universe_count;

	universe_count = 0;

	while (universe_count < iterations)
	{
		if (poptions->iterations > 0)
		{
			universe_count++;
		}
		universe_age = 0;
		creature_count = 0;
		
		initialize_universe_data();
		seed_universe_data();
		Simple_Display(universe_data, universe_age, creature_count, poptions);
		while (universe_is_alive())
		{
			update();
			universe_age++;
			Delay(poptions->delay);
		}
	}
	end_display();
}


universe::~universe()
{
	if (poptions->log)
	{
		logfile.close();
	}
	cleanup_universe_data(true);
	delete poptions;
}

