#include "Characters/Enemy.h"

//==========================================================
// Constructor.
Enemy::Enemy(const int index)
	: Character(this->randEnemyPos(), index, characterParams)
{

}

//=======================================================================================
// Draw function.
void Enemy::draw(sf::RenderWindow& window)
{
	showHpBar();
	drawSkills(window,false);
	this->getHpBar().draw(window);
	window.draw(this->getSprite());
}

//=======================================================================================
// Enemies cannot target other enemies, unless meant to.
bool Enemy::setTarget(std::shared_ptr<Enemy>) 
{
	return false;
}

//=======================================================================================
// Any enemy can target any player.
bool Enemy::setTarget(std::shared_ptr<Player> obj)
{
	setAsTarget(obj);
	return true;
}

//=======================================================================================
// Returns if the enemy is close enough to start attacking.
bool Enemy::checkIntersection() const
{
	auto norm = sqrt(pow((this->getPosition().x - this->getDest().x), 2) + pow((this->getPosition().y - this->getDest().y), 2));
	return (norm <= this->getStat(_range));
}

//=======================================================================================
// Enemies start at a random pos.
sf::Vector2f Enemy::randEnemyPos()
{
	sf::Vector2f pos;
	int side = rand();
	bool left = (side % 2 == 0) ? true : false; // Left/Right side of the screen.
	if (left)
		pos.x = CUT_CORNERS; 
	else
		pos.x = WINDOW_WIDTH - CUT_CORNERS;
	pos.y = (rand() % (WINDOW_HEIGHT - HEIGHT_LIMIT)) + HEIGHT_LIMIT;
	return pos;
}
//=======================================================================================
