#pragma once
#include "Effect.h"

// This class is in charge of the life drain effect.
class LifeDrain : public Effect
{
public:
	LifeDrain();
	virtual void affect(Character* self,
		Character* target, float factor) override;
};