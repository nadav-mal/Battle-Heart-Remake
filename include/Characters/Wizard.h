#pragma once
#include "Player.h"

// Class Wizard is in charge of the wizard player.
class Wizard : public Player
{
public:
	Wizard(const sf::Vector2f pos);
	virtual shared_ptr<Player> getType() {
		return make_shared<Wizard>(startPositions[_wizard]);
	}

	virtual void initSkills(const int index) override;
};
