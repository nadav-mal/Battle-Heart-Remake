#pragma once
#include "Effect.h"

// This class is in charge of the life drain effect.
class Teleport : public Effect
{
public:
	Teleport();
	virtual void affect(Character* self,
		Character* target, float factor) override;
};