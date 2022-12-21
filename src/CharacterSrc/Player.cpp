
#include "Characters/Player.h"

// Constructor.
Player::Player(const sf::Vector2f loc , int index)
	: Character(loc, index, PlayerParams), m_selected(false)
{
	setScale(SPRITE_SCALE);
}

//===========================================================
// Draw function.
void Player::draw(sf::RenderWindow& window)
{
	if (m_selected)
		showHpBar();

	drawSkills(window, m_selected);
	getHpBar().draw(window);
	window.draw(this->getSprite());
}

//==========================================================
// Sets enemy as target.
bool Player::setTarget(std::shared_ptr<Enemy> obj)
{
	setAsTarget(obj);
	return true;
}

//==========================================================
// Players set enemies as targets, unless meant to affect other players.
bool Player::setTarget(std::shared_ptr<Player>)
{
	return false;
}

//==========================================================
// Checks if intersecting with the destination.
bool Player::checkIntersection() const
{
	auto norm = sqrt(pow((this->getPosition().x - this->getDest().x), 2) + pow((this->getPosition().y - this->getDest().y), 2));
	if (this->getTarget())
		return (norm <= this->getStat(_range));

	const auto epsilon = 10.f;
	return norm <= epsilon;
}

//==========================================================