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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/
#ifndef BASECREATURE_HPP
#define BASECREATURE_HPP
#include "jecoopt.h"

class base_creature_class
{
	private:
		unsigned int level;
		unsigned int x;
		unsigned int y;

	protected:
		unsigned int age;

	public:
		virtual void Update(base_creature_class ***, base_creature_class ***, eco_option *)=0;
		unsigned int getAge();
		unsigned int getLevel();
		void setLevel(unsigned int levelIn);
		void setX(unsigned int xIn);
		void setY(unsigned int yIn);
		unsigned int getX();
		unsigned int getY();

};
 
#endif
