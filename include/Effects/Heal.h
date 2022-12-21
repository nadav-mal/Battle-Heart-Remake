#pragma once
#include "Effects/Effect.h"

// This class is in charge of the heal effect.
class Heal : public Effect
{
public:
	Heal();

	virtual void affect(Character* self, 
		Character* target, float factor) override;
};