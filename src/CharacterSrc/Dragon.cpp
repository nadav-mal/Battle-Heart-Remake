#include "Characters/Dragon.h"

// Constructor.
Dragon::Dragon()
	:Enemy(_dragon)
{
	this->initSkills(_dragon);
	this->setOffset({ 10,-20 });
}

// Inits skills.
void Dragon::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single , onPlayer, !isActive, _fireBreath, Sound::Sounds::NO_SOUND); // basic
}
