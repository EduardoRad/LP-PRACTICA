#pragma once
#include "PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
private:
	std::string m_cuisine;
	std::string m_reducedMobility;
public:
	PuntDeInteresRestaurantSolucio() : m_cuisine("undefinit"), m_reducedMobility("undefinit") {};
	PuntDeInteresRestaurantSolucio(std::string id, std::string name, Coordinate coord, std::string cuisine, std::string reducedMobility)
		: PuntDeInteresBase(id, name, coord), m_cuisine(cuisine), m_reducedMobility(reducedMobility) {};

	~PuntDeInteresRestaurantSolucio() {};
	std::string getReducedMobility() const { return m_reducedMobility; }
	std::string getCuisine() const { return m_cuisine; }
	unsigned int getColor();
	PuntDeInteresRestaurantSolucio* clone();
};


