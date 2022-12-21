#include "Effects/Damage.h"

#include "Characters/Character.h"

Damage::Damage()
{}

void Damage::affect(Character* self, Character* target , float factor)
{
	auto currHP = target->getStat(_hp);
	auto dmgByDefence = ( self->getStat(_dmg) * factor / (target->getStat(_defence) * DEFENSE_IGNORE_RATE) ) ;
	target->setStat(_hp, currHP - dmgByDefence);
}
