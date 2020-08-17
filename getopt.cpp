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
#include	<string.h>
#include	<stdio.h>
#include        "getopt.h"

#define 	SWITCH	'-'                     /* -: always recognized */

/* ------------ EXPORT variables -------------------------------------- */

char *	optarg; 			/* option argument if : in opts */
int	optind = 1;			/* next argv index		*/
int	opterr = 1;			/* show error message if not 0	*/
int	optopt; 			/* last option (export dubious) */

/* ------------ private section --------------------------------------- */

static	int sp = 1;			/* offset within option word	*/

static int badopt( char *name, char *text )
{	if ( opterr )			/* show error message if not 0	*/
		fprintf( stderr, "%s: %s -- %c\n", name, text, optopt );

	return (int) '?';               /* ?: result for invalid option */
}
/* ------------ EXPORT function --------------------------------------- */

int getopt(int argc, char **argv, char *opts )
{
	char *cp, ch;

	if ( sp == 1 )
	{	if ( argc <= optind || argv[ optind ][ 1 ] == '\0' )
			return EOF;	/* no more words or single '-'  */


		if (( ch = argv[ optind ][ 0 ] ) != '-' && ch != SWITCH )
			return EOF;	/* options must start with '-'  */

		if ( ! strcmp( argv[ optind ], "--" ))
		{	++optind;			/* to next word */
			return EOF;			/* -- marks end */
	}	}

	optopt = (int)( ch = argv[ optind ][ sp ] );	/* flag option	*/

	if ( ch == ':' || ( cp = strchr( opts, ch )) == NULL )
	{	if ( argv[ optind ][ ++sp ] == '\0')
		{	++optind;	sp = 1; 	/* to next word */
		}

		return badopt( argv[ 0 ], "illegal option" );
	}

	if ( *++cp == ':' )             /* ':' option requires argument */
	{	optarg = &argv[ optind ][ sp + 1 ];	/* if same word */
		++optind;	sp = 1; 		/* to next word */

		if ( *optarg == '\0' )                  /* in next word */
		{	if ( argc <= optind )		/* no more word */
				return badopt( argv[ 0 ],
					"option requires an argument" );

			optarg = argv[ optind++ ];	/* to next word */
	}	}
	else				/* flag option without argument */
	{	optarg = NULL;

		if ( argv[ optind ][ ++sp ] == '\0' )
		{	optind++;	sp = 1; 	/* to next word */
	}	}

	return optopt;
}


