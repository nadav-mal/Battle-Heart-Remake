#pragma once
#include "Resources.h"
#include "Player.h"

// Class Cleric is in charge of the cleric player.
// The cleric can heal other players.
class Cleric : public Player
{
public:
	// C-tor and d-tor.
	Cleric(const sf::Vector2f pos);
	~Cleric() = default;

	virtual bool setTarget(std::shared_ptr<Player> obj) override;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) override;
	virtual shared_ptr<Player> getType() {
		return make_shared<Cleric>(startPositions[_cleric]);
	}
	virtual void initSkills(const int index) override;
};