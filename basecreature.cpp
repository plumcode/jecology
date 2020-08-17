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
#include "basecreature.hpp"

void base_creature_class::setLevel(unsigned int levelIn)
{
	level = levelIn;
}


void base_creature_class::setX(unsigned int xIn)
{
	x = xIn;
}

void base_creature_class::setY(unsigned int yIn)
{
	y = yIn;
}

unsigned int base_creature_class::getX()
{
	return x;
}

unsigned int base_creature_class::getY()
{
	return y;
}

unsigned int base_creature_class::getLevel()
{
	return level;
}

unsigned int base_creature_class::getAge()
{
	return age;
}

