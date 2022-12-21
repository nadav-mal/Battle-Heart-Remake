#pragma once
#pragma once
#include "Player.h"

// This class is in charge of the arhcer player.
class Archer : public Player
{
public:
	Archer(const sf::Vector2f pos);

	virtual shared_ptr<Player> getType() {
		return make_shared<Archer>(startPositions[_archer]);
	}

	virtual void initSkills(const int index) override;
};
