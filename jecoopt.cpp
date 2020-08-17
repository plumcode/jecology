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
#include <string.h>
#include <time.h>
#include "jecodefs.h"
#include "getopt.h"
#include "jecoopt.h"


void print_help()
{
	printf("Usage: jecology [options]\n");
	printf("   -a         do not display age of universe\n");
	printf("   -b:num     sets number of base lifeforms\n");
	printf("   -c:num     times to run universe, 0 is forever (cannot be used with -s)\n");
	printf("   -d         prints defaults for all these options\n");
	printf("   -g         write log to jecology.log\n");
	printf("   -h         prints help (this screen)\n");
	printf("   -i:num     initial number of turns higher lifeforms go without food\n");
	printf("   -l:num     initial number of higher lifeforms\n");
	printf("   -m:num     sets the maturity cycle for A's\n");
	printf("   -n         creatures do not mutate\n");
	printf("   -o:num     sets maximum # of offspring\n");
	printf("   -p         do not display population info\n");
	printf("   -r:num     number of lifeforms eaten before reproduction\n");
	printf("   -s:num     use random seed specified (instead of time)\n"); 
	printf("   -t:num     sets time delay in loop (in seconds, decimals allowed)\n");
	printf("   -x:num     sets width of universe\n");
	printf("   -y:num     sets height of universe \n");
	printf("   -0:num     sets distance that creatures can see (0 is infinite)\n");
	printf("   -1:num     sets likelihood of first mutation(out of 100)\n");
	printf("   -2:num     sets likelihood of second mutation(out of 100)\n");
	printf("   -3:num     sets likelihood of third mutation(out of 100)\n");
}


void print_defaults()
{
	printf("jecology defaults:\n\n");
	printf("  reproduction threshold       3\n");
	printf("  A's maturity cycle          20\n");
	printf("  max offsping                 6\n");
	printf("  mutation 1                   3\n");
	printf("  mutation 2                   3\n");
	printf("  mutation 3                   3\n");
	printf("  number of base lifeforms   100\n");
	printf("  number of higher lifeforms  10\n");
	printf("  initial turns without food  20\n");
	printf("  run universe # times         1\n");
	printf("  delay                      0.5\n");
	printf("  distance                   infinite\n");
	printf("\n");
	printf("  Universe age is printed by default.\n");
	printf("  Universe population is printed by default if universe size permits.\n");
	printf("  Creatures mutate by default.\n");
	printf("  Universe size is fitted to terminal size by default.\n");
}

void option_conjunction_error()
{
	printf("\n");
	printf("-d or -h options cannot be used with other options\n");
	printf("    (or even each other).\n\n");
	printf("Type \"jecology -h\" for help.\n");
}

void initialize_options(eco_option * poptions)
{
	poptions->mutates_flag = 1;  //flags: non zero for true, zero for false
	poptions->display_age_flag = 1; 
	poptions->display_population_flag = 1;
	poptions->distance = 0;

	poptions->maturity_cycle = MATURITY_CYCLE;
	poptions->max_offspring = MAX_OFFSPRING;
	poptions->mutation1 = MUTATION1; 
	poptions->mutation2 = MUTATION2; 
	poptions->mutation3 = MUTATION3; 
	poptions->number_of_base_life = NUMBER_OF_BASE_LIFE;
	poptions->number_of_higher_life = NUMBER_OF_HIGHER_LIFE;
	poptions->initial_turns_without_food = INITIAL_TURNS_WITHOUT_FOOD;
	poptions->log = 0;
	poptions->reproduction_thres = REPRO;
	poptions->x = 0;
	poptions->y = 0;
	poptions->iterations = 1;
	poptions->delay = 0.5;
	poptions->seed = (unsigned int) time(NULL);
	poptions->eats_below = 2;
}

void print_arg_error(char opt, bool is_int, bool zero_allowed)
{
	printf("Must be in the form \"jecology -%c:value\" where value ", opt);
   	if (zero_allowed)
	{
		printf("is zero or ");
	}

	if (is_int)
	{
		printf("a positive integer.\n");
		return;
	}
	printf("a positive real number.\n");
	
}

bool check_arg(char * arg, char opt, bool is_int, bool zero_allowed)
{
	unsigned int count = 1;
	char error_string[100];

	if ((arg[0] != ':') || (arg[0] == 0))
	{ 
		print_arg_error(opt, is_int, zero_allowed);
		return false;
	}
	while (arg[count] != 0)
	{
		if (is_int)
		{
			if ((arg[count] > '9') || (arg[count] < '0'))
			{
				print_arg_error(opt, is_int, zero_allowed);
				return false;
			}
		}
		else
		{
			if ((arg[count] != '.') && ((arg[count] > '9') || (arg[count] < '0')))
			{
				print_arg_error(opt, is_int, zero_allowed);
				return false;
			}	
		}
		count++;
	}	
	return true;
}


unsigned int process_options(int argc, char ** argv, eco_option * poptions)
{
 	extern int   opterr;
 	extern int   optind;
	extern char *optarg;					

	char * conv_ptr;

	long value;

	char c;
	unsigned int optcount = 0; 

	bool help = false;
	bool defaults = false;
	bool error = false;

	while ((c = getopt( argc, argv, "ab:c:dghi:l:m:no:pr:s:t:x:y:z:0:1:2:3:" )) != -1 )      
	{
		optcount++;
		switch ( c )						
		{
			case 'a':
				poptions->display_age_flag = 0;
				break;
			case 'b':
				if (check_arg(optarg, 'b',  true, false))
				{
					poptions->number_of_base_life = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case 'c':
			 	if (check_arg(optarg, 'c',  true, true))
				{
					poptions->iterations = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case 'd':
				defaults = true;
				break;
			case 'g':
				poptions->log= true;
				break;
			case 'h':                                       
				help = true;
				break;

			case 'i':                                       
				if (check_arg(optarg, 'i',  true, false))
				{
					poptions->initial_turns_without_food = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;

			case 'l':
				if (check_arg(optarg, 'l',  true, false))
				{
					poptions->number_of_higher_life = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case 'm':
				if (check_arg(optarg, 'm',  true, true))
				{
					poptions->maturity_cycle = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;

			case 'n':                                       
				poptions->mutates_flag = 0;
				break;
			case 'o':
				if (check_arg(optarg, 'o',  true, true))
				{
					poptions->max_offspring = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case 'p':
				poptions->display_population_flag = 0;
				break;
			case 'r':
				if (check_arg(optarg, 'r',  true, true))
				{
					poptions->reproduction_thres = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case 's':
				if (check_arg(optarg, 's',  true, true))
				{
					poptions->seed = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;		
			case 't':
				if (check_arg(optarg, 's',  false, true))
				{
					poptions->delay = strtof(&(optarg[1]), &conv_ptr);
				}
				else
				{
					error = true;
				}
				break;
			case 'x':
				if (check_arg(optarg, 'x',  true, false))
				{
					poptions->x = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case 'y':
				if (check_arg(optarg, 'y',  true, false))
				{
					poptions->y = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case 'z':
				if (check_arg(optarg, 'z',  true, false))
				{
					poptions->eats_below = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
 			case '0':
 				if (check_arg(optarg, '0',  true, false))
 				{
 					poptions->distance = strtol(&(optarg[1]), &conv_ptr, 10);
 				}
 				else
 				{
 					error = true;
 				}
 				break;
			case '1':
				if (check_arg(optarg, '1',  true, false))
				{
					poptions->mutation1 = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case '2':
				if (check_arg(optarg, '2',  true, false))
				{
					poptions->mutation2 = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			case '3':
				if (check_arg(optarg, '3',  true, false))
				{
					poptions->mutation3 = strtol(&(optarg[1]), &conv_ptr, 10);
				}
				else
				{
					error = true;
				}
				break;
			default:
				error = true;
		}							
	}
	if (error)
	{
		return 1;
	}
	if (help || defaults)
	{
		if (optcount > 1)
		{	
			option_conjunction_error();
		        return 1;	
		}
		if (help)
		{
			print_help();
			return 1;
		}
		if (defaults)
		{
			print_defaults();
			return 1;
		}
	}
	return 0;
}



