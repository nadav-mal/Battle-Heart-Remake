#pragma once
#include <cmath>
#include "Effects/Effect.h"


class DmgByDistance : public Effect
{
public:
	DmgByDistance();

	virtual void affect(Character* self,
		Character* target, float factor) override;
};