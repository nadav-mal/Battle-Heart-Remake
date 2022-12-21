#pragma once
#include "Animation.h"
#include "Resources.h"
#include "Stat.h"
#include "Timer.h"

class Character;
using namespace std;

// This class is the base class of the different effects.
class Effect 
{
public:
	virtual ~Effect() = default;
	virtual void affect(Character* self,
		Character* target, float factor) = 0;
};
 