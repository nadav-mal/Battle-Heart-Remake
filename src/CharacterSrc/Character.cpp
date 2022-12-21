#include "Characters/Character.h"
#include "Characters/Player.h"
#include "Characters/Enemy.h"

//================================================================
// Constructor.
Character::Character(const sf::Vector2f pos, const int index, AnimationParams animParams )
	: m_isAttacking(false), Object(pos, index, animParams , CharacterRowLengths[index] , Resources::instance().getTexture(index)), 
	  m_isDying(false), m_steering(new SteeringInterface), m_velocity(DEFAULT_VEC)
{
	this->initStats(index); // Stats
	this->initPhysics(index); // Physics
	this->initBuffs(); // Buffs
	m_hpBar = HealthBar(pos, m_stats[_hp]->getValue()); // Health bar
}

//=======================================================================================
// General update function to characters.
void Character::update(sf::Vector2f steerForce, float deltaTime,
					   vector<std::shared_ptr<Player>> m_players, 
					   vector<std::shared_ptr<Enemy>> m_enemies)
{
	// HP bar follows the character.
	this->m_hpBar.setPosition(this->getPosition());

	// If it's dead.
	if (!isAlive())
		return;

	// Calculates movement.
	sf::Vector2f acceleration = steerForce / this->m_moveStats[_mass];
	this->setVelocity(this->getVelocity() + acceleration * deltaTime);
	this->setVelocity(this->behaviour()->Truncate(this->getVelocity(), this->m_moveStats[_maxVelocity]));

	auto target = this->getTarget();
	// If the character has a target.
	if (target)
	{
		// If the target is alive.
		if (target->isAlive())
			// Go to it.
			this->setDestination(this->getTarget()->getPosition());
		else // If it's dead.
		{
			// Leave it.
			this->setAsTarget(nullptr);
			this->setDestination(this->getPosition());
		}
	}

	updateMovement(deltaTime); // Movement update.
	updateBuffs(); // Buffs update.
	this->updateSkills(deltaTime, m_players, m_enemies); // Skills update.
	this->m_hpBar.updateHealthBar(m_stats[_hp]->getValue() , this->getPosition()); // HP update.
	handleAnimation(this->getVelocity() * deltaTime, deltaTime); // Animation update.
}

//======================================================================================
// Updates the movement of the character.
void Character::updateMovement(float deltaTime)
{
	// If character not at their destination.
	if (!this->checkIntersection())
	{
		// Walk to destination.
		this->setMoving(true);
		this->setPosition(this->getPosition() + this->getVelocity() * deltaTime);
		this->setAnimation(_walk);
	}
	else
	{
		this->setMoving(false); // Not moving.

		// If character has a target and it's in range, attack it.
		if (targetInRange())
		{
			this->setAnimation(_attack);
			useSkill(_basic, this->getPosition());
		}
		else
			this->setAnimation(_idle); // Idle.
	}
}


//=======================================================================================
// Updates skills.
void Character::updateSkills(const float deltaTime, vector<std::shared_ptr<Player>> players, vector<std::shared_ptr<Enemy>> enemies)
{
	vector<shared_ptr<Character>> m_targets;
	for (auto& skill : this->m_skills)
	{
		m_targets.clear();
		auto type = skill->getSkillType();
		switch (type)
		{
		case AttackType::Single:
			if(this->getTarget())
				m_targets.push_back(locateInVector(players, enemies, this->getTarget()));
			break;

		case AttackType::Multi:
			if (skill->getOnPlayer())
				m_targets = this->createTargetVec(players);
			else
				m_targets = this->createTargetVec(enemies);
			break;

		case AttackType::Self:
			m_targets.push_back(locateInVector(players, enemies , this));
			break;

		default:
			break;
		}
		skill->updateSkill(deltaTime, m_targets, this);
	}
}

//=======================================================================================
// Inits stats.
void Character::initStats(const int index)
{
	for (int stat = 0; stat < NUM_OF_STATS; stat++)
		this->m_stats.push_back(std::make_shared<Stat>(charactersStats[index][stat]));
	this->m_stats[_hp]->setMax(m_stats[_hp]->getValue());
}

//=======================================================================================

void Character::initPhysics(const int index)
{
	m_moveStats.push_back(objectsPhysics[index][_mass]);
	m_moveStats.push_back(objectsPhysics[index][_maxForce]);
	m_moveStats.push_back(objectsPhysics[index][_maxVelocity]);
}

//=======================================================================================
// Checks if the target is in range.
bool Character::targetInRange() const
{
	if (this->getTarget())
	{
		auto tarPos = this->getTarget()->getPosition();
		auto myPos = this->getPosition();
		auto range = this->getStat(_range);
		auto norm = sqrt(pow(myPos.x - tarPos.x, 2) + pow(myPos.y - tarPos.y, 2));
		return (norm <= range);
	}
	return false;
}

//=======================================================================================
// Creates a skill by given parameters.
void Character::createSkill(const int charIndex, const int skillIndex, const int effectIndex, const AttackType single, 
	const bool onPlayer, const bool active , const int projType, Sound::Sounds soundIndex = Sound::Sounds::HEAL)
{
	this->addSkill(Skill
		(
			Resources::instance().getSkillText(charIndex, skillIndex),
			sf::Vector2f(skillIndex * (SKILL_GAP) + 30, 30),
			skillCooldowns[charIndex][skillIndex], effectIndex,
			single,
			onPlayer,
			active,
			skillFactors[charIndex][skillIndex]
			,projType,
			soundIndex
		));

}

//=======================================================================================
// Sets stat.
void Character::setStat(const int index, const int newVal)
{ 
	if (index == _hp)
		this->showHpBar();

	if(this->isAlive())
		this->m_stats[index]->setStat(newVal); 
}

//=======================================================================================

void Character::setDying()
{
	this->setAnimation(_death);
	this->m_isDying = true;
	this->m_hpBar.updateHealthBar(m_stats[_hp]->getValue(), this->getPosition());
}

//=======================================================================================
// Creates a vector of the targets.
template<class Type>
vector<shared_ptr<Character>> Character::createTargetVec(Type vec)
{
	vector<shared_ptr<Character>> temp;
	for (auto obj : vec)
	{
		temp.push_back(obj);
	}
	return temp;
}

//=======================================================================================
// Locates the object in the vector.
shared_ptr<Character> Character::locateInVector(vector<shared_ptr<Player>> players, vector<shared_ptr<Enemy>> enemies, Character* obj)
{
	for (auto player : players)
	{
		if (player.get() == obj)
			return player;
	}

	for (auto enemy : enemies)
	{
		if (enemy.get() == obj)
			return enemy;
	}

	return nullptr; 
}

//========================================================================================

void Character::drawSkills(sf::RenderWindow& window, const bool selected)
{
	for (auto& skill : m_skills)
	{
		skill->draw(window,selected);
	}
}

//========================================================================================
// Checks if the skill was clicked and if off cooldown, and if so then uses it.
bool Character::checkSkillClick(const sf::Vector2f& location)
{
	for (auto& skill : m_skills)
	{
		if (skill->handleClick(location))
		{
			skill->useSkill(this->getPosition());
			return true;
		}
	}
	return false;
}

//========================================================================================
// Checks hover on skills.
bool Character::checkSkillHover(sf::Vector2f hoverPos, int index)
{
	return this->m_skills[index]->checkHover(hoverPos);
}

//==========================================================================================

std::string Character::getSkillData(int index) const
{
	return this->m_skills[index]->getInfo();
}

//==========================================================================================
// Turns locations to vector.
vector<sf::Vector2f> Character::getLocationsVec(bool getDest) const
{
	vector<sf::Vector2f> vec;
	if (getDest)
		vec.push_back(this->getDest());
	else
		vec.push_back(this->getTarget()->getPosition());
	vec.push_back(getPosition());
	vec.push_back(m_velocity);
	return vec;
}

//===========================================================================================
// Buffs are meant to affect for a certain time, not forever.
void Character::updateBuffs()
{
	for (size_t i = 0; i < m_buffTimers.size(); i++)
	{
		auto buff = m_buffTimers[i];
		buff.first.updateTimer();
		if (m_activeBuffs[i] && buff.first.isTimeUp())
		{
			this->setStat(i, buff.second);
			m_activeBuffs[i] = false;
		}
	}	
}

//===========================================================================================

void Character::setActiveBuff(int index ,float duration)
{
	if (!m_buffTimers[index].first.isTimeUp()) // prevent double buffs
	{
		m_buffTimers[index].first.updateTimer(m_buffTimers[index].first.getTimeLeft()); // set to 0
		this->updateBuffs();
	}

	m_buffTimers[index].first.setCooldown(duration);
	m_buffTimers[index].first.setTimer();
	m_buffTimers[index].second = m_stats[index]->getValue();
	m_activeBuffs[index] = true;
}

//============================================================================================

void Character::initBuffs()
{
	for (size_t i = 0; i < NUM_OF_STATS ; i++)
	{
		auto timer = Timer(0.f);
		m_buffTimers.push_back(std::make_pair(timer , m_stats[i]->getValue()));
		m_activeBuffs.push_back(false);
	}
}