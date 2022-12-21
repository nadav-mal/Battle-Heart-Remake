#include "Effects/Heal.h"

#include "Characters/Character.h"

Heal::Heal()
{}

void Heal::affect(Character* self, Character* target, float factor)
{
	auto currHP = target->getStat(_hp);
	target->setStat(_hp,currHP + (factor * self->getStat(_dmg)));
}
