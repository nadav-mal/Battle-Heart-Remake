
#include "Characters/Cleric.h"

//================================================================
// Constructor.
Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{
	this->initSkills(_cleric);
}

//==========================================================
// Sets player as target.
bool Cleric::setTarget(std::shared_ptr<Player> obj)
{
	setAsTarget(obj); 
	return true;
}

//==========================================================
// Can't set enemy as target.
bool Cleric::setTarget(std::shared_ptr<Enemy>)
{
	return false;
}

//==========================================================
// Inits skills.
void Cleric::initSkills(const int index)
{
	this->createSkill(index, _basic, _heal, AttackType::Single, onPlayer, !isActive,_healBall, Sound::Sounds::HEAL); // basic
	this->createSkill(index, _skill1, _heal, AttackType::Multi, onPlayer, isActive, _healBall, Sound::Sounds::HEAL); // multi heal
	this->createSkill(index, _skill2, _defend, AttackType::Single , onPlayer, isActive , _tesla, Sound::Sounds::DEF_BUFF); // shield
}

