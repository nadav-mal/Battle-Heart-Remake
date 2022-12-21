#include "Effects/DmgByDistance.h"

#include "Characters/Character.h"

DmgByDistance::DmgByDistance()
{}

void DmgByDistance::affect(Character* self, Character* target, float factor)
{
	auto currHP = target->getStat(_hp);
	auto dmgByDefence = (self->getStat(_dmg) * factor / (target->getStat(_defence) * DEFENSE_IGNORE_RATE));
	auto myPos = self->getPosition();
	auto tarPos = target->getPosition();
	auto distance = sqrt(pow(myPos.x - tarPos.x, 2) + pow(myPos.y - tarPos.y, 2)) / 100.f;
	target->setStat(_hp, currHP - (distance * dmgByDefence));
}
