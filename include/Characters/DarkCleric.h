#pragma once
#include "Enemy.h"

// This class is in charge of the dark cleric enemy.
// As the cleric, it can heal its' allies.
class DarkCleric : public Enemy
{
public:
	DarkCleric();
	virtual void initSkills(const int index) override;

	virtual shared_ptr<Enemy> getType() {
		return make_shared<DarkCleric>();
	}

	virtual void update(sf::Vector2f steerForce, const float deltaTime,
		vector<std::shared_ptr<Player>> m_players, vector<std::shared_ptr<Enemy>> m_enemies) override;

private:
	std::shared_ptr<Enemy> findClosestEnemy(vector<std::shared_ptr<Enemy>> m_enemies);
};