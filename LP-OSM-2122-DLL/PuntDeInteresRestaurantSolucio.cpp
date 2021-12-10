#include "pch.h"
#include "PuntDeInteresRestaurantSolucio.h"

unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	unsigned int color;

	if (m_reducedMobility == "yes" && m_cuisine == "pizza")
		color = PIZZA_RM;
	else if (m_cuisine == "chinese")
		color = CHINESE;
	else if (m_reducedMobility == "yes")
		color = OTHERS_RM;
	else
		color = DEFAULT;

	return color;
}

PuntDeInteresRestaurantSolucio* PuntDeInteresRestaurantSolucio::clone()
{
	return new PuntDeInteresRestaurantSolucio(*this);
}

