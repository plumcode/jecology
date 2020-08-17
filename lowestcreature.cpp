#include "lowestcreature.hpp"

lowest_creature::lowest_creature()
{
	age = 0;
	mature = true;
}
		

void lowest_creature::setMaturityThres(unsigned int thres)
{
	maturity_thres = thres;
}

void lowest_creature::setImmature()
{
	mature = false;
	turns_to_mature = maturity_thres;
}

void lowest_creature::Update(base_creature_class *** creatures, base_creature_class *** new_universe, eco_option * poptions)
{
	age++;
	if (turns_to_mature)
	{
		turns_to_mature--;
		if (turns_to_mature == 0)
		{
			mature = true;
		}
	}
		
}

bool lowest_creature::getMature()
{
	return mature;
}

