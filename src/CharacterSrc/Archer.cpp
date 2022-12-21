#include "Characters/Archer.h"

//==========================================================================================
// Constructor.
Archer::Archer(const sf::Vector2f pos)
	:Player(pos, _archer)
{
	this->initSkills(_archer);
}

//==========================================================================================

void Archer::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single, !onPlayer, !isActive, _arrow, Sound::Sounds::ARROW); // basic
	this->createSkill(index, _skill1, _dmgByDistance, AttackType::Single, !onPlayer, isActive, _arrow, Sound::Sounds::ARROW); // aimed shot
	this->createSkill(index, _skill2, _damage , AttackType::Multi, !onPlayer, isActive, _arrow, Sound::Sounds::ARROW_RAIN); // barrage
}

