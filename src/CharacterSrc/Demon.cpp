#include "Characters/Demon.h"

//================================================================
// Constructor.
Demon::Demon()
	:Enemy(_demon)
{
	this->initSkills(_demon);
	this->setOffset(DemonOffset);
}

//================================================================
// Inits skills.
void Demon::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single, onPlayer, !isActive, _none, Sound::Sounds::SWORD1); // basic
}
