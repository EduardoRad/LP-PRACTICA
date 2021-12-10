#include "pch.h"
#include "PuntDeInteresBase.h"


PuntDeInteresBase::PuntDeInteresBase() {
	this->m_id = "undefinit";
	this->m_name = "undefinit";
	this->m_coord = Coordinate{ 0.0, 0.0 };
}

PuntDeInteresBase::PuntDeInteresBase(std::string id, std::string name, Coordinate coord) {
	this->m_id = id;
	this->m_name = name;
	this->m_coord = coord;
}

std::string PuntDeInteresBase::getID() {
	return this->m_id;
}

std::string PuntDeInteresBase::getName() {
	return this->m_name;
}

Coordinate PuntDeInteresBase::getCoord() {
	return this->m_coord;
}


unsigned int PuntDeInteresBase::getColor() {
	return 0xFFA500;
}

PuntDeInteresBase* PuntDeInteresBase::clone()
{
	return new PuntDeInteresBase(*this);
}




