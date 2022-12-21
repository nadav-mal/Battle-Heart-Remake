#pragma once
#include "Enemy.h"

// Class Player is in charge of the different players in the game.
class Player : public Character
{
public:
	// C-tor.
	Player(const sf::Vector2f pos, int index);

	// Virtuals
	virtual void draw(sf::RenderWindow& window) override;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) override;
	virtual bool setTarget(std::shared_ptr<Player> obj) override;
	virtual bool checkIntersection() const override;
	virtual shared_ptr<Player> getType() = 0;
	void setSelected(bool state) { this->m_selected = state; }

private:
	bool m_selected; // Stores if the player is currently selected.
};