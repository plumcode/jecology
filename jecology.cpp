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
#include <curses.h>
#include "lowestcreature.hpp"
#include "highercreature.hpp"
#include "universe.hpp"

int main(int argc, char ** argv)
{
	eco_option options;
	unsigned int opt_retval;
	initialize_options(&options);
	if (opt_retval = process_options(argc, argv, &options))
	{
		return opt_retval;
	}
	universe lone_universe(&options);
	lone_universe.run();
	return 1;
}
