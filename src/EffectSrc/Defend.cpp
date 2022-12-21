#include "Effects/Defend.h"

#include "Characters/Character.h"

Defend::Defend()
{}

void Defend::affect(Character* self, Character* target, float factor)
{
	auto currDef = target->getStat(_defence);
	target->setActiveBuff(_defence, BUFF_DURATION);
	target->setStat(_defence, currDef * factor);
}
