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
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <fstream>
#include "jecoopt.h"
#include "basecreature.hpp"
using namespace std;

class universe
{
	private:
		base_creature_class *** universe_data;
		eco_option * poptions;
		unsigned int universe_age;
		unsigned int creature_count;
		unsigned int iterations;
		unsigned int screen_x;
		unsigned int screen_y;
		ofstream logfile;

	public:

		universe();
		universe(eco_option * poptions_in);

		void init_universe();
		void initialize_universe_data();
		void create_creatures(unsigned int num_creatures, unsigned int level);
		void seed_universe_data();
		void update_universe_data(base_creature_class *** new_universe);
		void remove_dead_bodies(base_creature_class *** new_universe_data);
		bool universe_is_alive();
		unsigned int get_animate_population();
		base_creature_class *** copy_universe_data();
		void cleanup_universe_data(bool destroy_creatures);
		void cleanup_universe_data(base_creature_class **** puniverse_data, bool destroy_creatures);
		void update();
		void run();
		unsigned int get_universe_age();
		unsigned int get_creature_count();
		~universe();
};

#endif
