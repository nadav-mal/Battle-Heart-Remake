#pragma once
#include "Player.h"

// This class is in charge of the knight player.
// The knight is designed to be tanky but doesn't do a lot of damage.
class Knight : public Player
{
public:
	Knight(const sf::Vector2f pos);

	virtual shared_ptr<Player> getType() {
		return make_shared<Knight>(startPositions[_knight]);
	}

	virtual void initSkills(const int index) override;
};
