#pragma once
#include "Enemy.h"

// This class is in charge of the mini dragon enemy.
class Dragon : public Enemy
{
public:
	Dragon();
	virtual void initSkills(const int index) override;

	virtual shared_ptr<Enemy> getType() {
		return make_shared<Dragon>();
	}

};