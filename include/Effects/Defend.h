#pragma once
#include "Effect.h"

// This class is in charge of the defend effect.
class Defend : public Effect
{
public:
	Defend();

	virtual void affect(Character* self,
		Character* target, float factor) override;
};