#include "Characters/Wolf.h"

// Constructor.
Wolf::Wolf()
	:Enemy(_wolf)
{
	this->initSkills(_wolf);
	setScale(SPRITE_SCALE);
}

// Inits skills.
void Wolf::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single, onPlayer, !isActive, _none, Sound::Sounds::NO_SOUND); // basic
}
