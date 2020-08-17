#ifndef LOWESTCREATURE_HPP
#define LOWESTCREATURE_HPP
#include "basecreature.hpp"

class lowest_creature:public base_creature_class
{
	private:
		bool mature;
		unsigned int maturity_thres;
		unsigned int turns_to_mature;
	public:
		bool getMature();
		void Update(base_creature_class ***, base_creature_class ***, eco_option *);
		void setMaturityThres(unsigned int thres);
		void setImmature();
		lowest_creature();
};

#endif
