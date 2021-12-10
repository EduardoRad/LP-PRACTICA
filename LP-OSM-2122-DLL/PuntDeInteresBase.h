#pragma once

#include <string>
#include "Common.h"

const unsigned int SUPERMARKET = 0xA5BE00;
const unsigned int TOBACCO = 0xFFAD69;
const unsigned int BAKERY = 0xE85D75;
const unsigned int OTHERS = 0xEFD6AC;

const unsigned int PIZZA_RM = 0x03FCBA;
const unsigned int CHINESE = 0xA6D9F7;
const unsigned int OTHERS_RM = 0x251351;
const unsigned int DEFAULT = 0xFFA500;

class PuntDeInteresBase {

private:
	std::string m_id;
	std::string m_name;
	Coordinate m_coord;

public:
	PuntDeInteresBase();
	PuntDeInteresBase(std::string id, std::string name, Coordinate coord);
	virtual ~PuntDeInteresBase() {};

	std::string getID();
	virtual std::string getName();
	Coordinate getCoord();
	virtual unsigned int getColor();
	virtual PuntDeInteresBase* clone();

};