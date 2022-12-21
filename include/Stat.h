#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

// This class is in charge of stats in the game.
// Stats represent different variables in the game-
// Such as health, speed, defense, etc. 
class Stat
{
public:
	// C-tor and d-tor.
	Stat(float initVal,float max = std::pow(10,6));
	~Stat() = default;

	// Management.
	float getValue() const { return this->m_val; }
	void setStat(float val) { this->m_val = val; }
	void setMax(float val) { this->m_max = val; }

private:
	bool handleStat(float amount);
	float m_val; // value of the stat
	float m_max;
};