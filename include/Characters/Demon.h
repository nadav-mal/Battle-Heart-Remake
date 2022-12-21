#pragma once
#include "Enemy.h"

// This class is in charge of the demon enemy.
class Demon : public Enemy
{
public:
	Demon();

	virtual void initSkills(const int index) override;
	virtual shared_ptr<Enemy> getType() {
		return make_shared<Demon>();
	}
};
