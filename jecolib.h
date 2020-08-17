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
#ifndef JECOLIB_H
#define JECOLIB_H
#include <fstream>
#include "basecreature.hpp"
using namespace std;

void Delay(float dtime);

void initialize_universe(base_creature_class **** pcreatures, eco_option * poptions);

void seed_universe(base_creature_class *** creatures, eco_option * poptions);

void create_creatures(base_creature_class *** creatures, unsigned int num_creatures, unsigned int level, 
		eco_option * poptions);

void update_universe(base_creature_class *** creatures, base_creature_class *** new_universe, eco_option * poptions);

void remove_dead_bodies(base_creature_class *** creatures, unsigned int x, unsigned int y);

bool universe_is_alive(base_creature_class *** creatures, unsigned int x, unsigned int y);

unsigned int get_animate_population(base_creature_class *** creatures, unsigned int x, unsigned int y);

base_creature_class *** copy_universe(base_creature_class *** creatures, unsigned int x, unsigned int y);

void cleanup_universe(base_creature_class **** pcreatures, unsigned int x, unsigned int y, bool destroy_creatures);

void log_to_file(ofstream * pfile, base_creature_class *** creatures, eco_option * poptions);
#endif
