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
#ifndef JECOOPT_H
#define JECOOPT_H
typedef struct eco_option_struct
{
	unsigned int mutates_flag;  
	unsigned int display_age_flag; 
	unsigned int display_population_flag;
	unsigned int seed;

	unsigned int distance;
	
	unsigned int reproduction_thres;	
	unsigned int maturity_cycle;
	unsigned int max_offspring;
	unsigned int mutation1;
	unsigned int mutation2;
	unsigned int mutation3;
	unsigned int number_of_base_life;
	unsigned int number_of_higher_life;
	unsigned int initial_turns_without_food;
	unsigned int x;
	unsigned int y;
	unsigned int iterations;
	float delay;

	unsigned int log;

	unsigned int eats_below;
}eco_option;

void print_help();

void print_defaults();

void option_conjunction_error();

void initialize_options(eco_option * poptions);

void print_arg_error(char opt, bool is_int, bool zero_allowed);

bool check_arg(char * arg, char opt, bool is_int, bool zero_allowed);

unsigned int process_options(int argc, char ** argv, eco_option * poptions);
#endif
