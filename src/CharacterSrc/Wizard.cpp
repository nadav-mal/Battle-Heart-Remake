
#include "Characters/Wizard.h"

// Constructor.
Wizard::Wizard(const sf::Vector2f pos)
	:Player(pos, _wizard)
{
	this->initSkills(_wizard);
}

// Inits skills.
void Wizard::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single, !onPlayer, !isActive , _energy, Sound::Sounds::NO_SOUND); // basic
	this->createSkill(index, _skill1, _drainLife, AttackType::Single, !onPlayer, isActive, _tesla, Sound::Sounds::NO_SOUND); // 
	this->createSkill(index, _skill2, _damage, AttackType::Multi, !onPlayer, isActive , _lightning, Sound::Sounds::NO_SOUND); // 
}
