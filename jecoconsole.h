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
#ifndef JECOCONSOLE_H
#define JECOCONSOLE_H
#include "jecoopt.h"
#include "basecreature.hpp"

void display_init();


void get_screen_xy(unsigned int * px, unsigned int * py);

void Display_Lowest(unsigned int x_coord, unsigned int y_coord, bool fMature);


void Display_Higher(unsigned int x_coord, unsigned int y_coord, unsigned int level);


void error_log(char * pszerror);

void Simple_Display(base_creature_class *** creatures, unsigned int universe_age, 
		unsigned int creature_count, eco_option * poptions);

void Display(base_creature_class *** new_universe, base_creature_class *** old_universe, 
		unsigned int universe_age, unsigned int creature_count, eco_option * poptions);

void end_display();
#endif
