#include "Characters/DarkCleric.h"

//================================================================
// Constructor.
DarkCleric::DarkCleric()
	:Enemy(_darkCleric)
{
	this->initSkills(_darkCleric);
	setScale(SPRITE_SCALE);
}

//================================================================
// Inits skills.
void DarkCleric::initSkills(const int index)
{
	this->createSkill(index, _basic, _heal, AttackType::Multi, !onPlayer, !isActive, _energy, Sound::Sounds::HEAL); // basic heal on all enemies
	this->createSkill(index, _skill1, _teleport, AttackType::Self, !onPlayer, !isActive, _none, Sound::Sounds::NO_SOUND); // teleport
}

//====================================================================================
// Unique update function.
void DarkCleric::update(sf::Vector2f steerForce, const float deltaTime,
	vector<std::shared_ptr<Player>> m_players, vector<std::shared_ptr<Enemy>> m_enemies)
{
	this->setAsTarget(findClosestEnemy(m_enemies));
	Enemy::update(steerForce, deltaTime, m_players, m_enemies);

	useSkill(_skill1, this->getPosition());
}

//====================================================================================
float distance(sf::Vector2f pos1, sf::Vector2f pos2)
{
	return std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
}
//====================================================================================
// Dark cleric will target the enemy with the lowest hp at the moment.
std::shared_ptr<Enemy> DarkCleric::findClosestEnemy(vector<std::shared_ptr<Enemy>> enemies)
{
	auto copy = enemies;

	auto myPos = this->getPosition();
	// sort the enemies by x values and find one that isn't dead
	std::sort(copy.begin(), copy.end(),
		[&](auto e1, auto e2) {return distance(e1->getPosition(), myPos) < distance(e2->getPosition(), myPos); });


	std::shared_ptr<Enemy> self;
	for (auto enemy : copy)
	{
		if (enemy.get() == this)
		{
			self = enemy;
			continue;
		}
		else if(enemy->isAlive())
			return enemy;
	}
	return self;
}