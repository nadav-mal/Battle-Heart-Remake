#include "Effects/LifeDrain.h"

#include "Characters/Character.h"

LifeDrain::LifeDrain()
{}

void LifeDrain::affect(Character* self, Character* target, float factor)
{
	auto currHP = target->getStat(_hp);
	auto dmgByDefence = (self->getStat(_dmg) * factor / target->getStat(_defence)) ;
	target->setStat(_hp, currHP - dmgByDefence);
	self->setStat(_hp, self->getStat(_hp) + dmgByDefence * 0.5);
}
