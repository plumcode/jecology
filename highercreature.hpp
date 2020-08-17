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
#ifndef HIGHERCREATURE_HPP
#define HIGHERCREATURE_HPP
#include "basecreature.hpp"

class higher_creature:public base_creature_class
{
	private:
		bool alive;	
		unsigned int max_turns_without_food;
		unsigned int turns_without_food;
		unsigned int food_count;
		unsigned int repro_thres;
	public:
		higher_creature(unsigned int maxturns, unsigned int repro);
		
		
		void Update(base_creature_class ***, base_creature_class ***, eco_option *);
		void Reproduce(base_creature_class ***, eco_option *);
		bool getAlive();
		void setDead();
};

#endif
