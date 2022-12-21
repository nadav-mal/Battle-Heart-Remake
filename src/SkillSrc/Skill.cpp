#include "Skills/Skill.h"

#include "Characters/Character.h"

//==========================================================================================
// Constructs a skill.
Skill::Skill
(
	const sf::Texture* texture,
	const sf::Vector2f pos,
	float cooldown,
	const int effectIndex,
	AttackType type,
	bool onPlayer,
	bool isActive,
	float factor,
	int projType,
	Sound::Sounds soundIndex
)
	: m_timer(Timer(cooldown)), m_type(type), m_effectsTable(this->getTable()),
	m_onPlayer(onPlayer), m_isActive(isActive) , m_factor(factor) , m_soundIndex(int(soundIndex))
{
	this->m_projType = projType;
	this->initInfo(effectIndex, onPlayer, isActive, cooldown, type);
	this->initRect(texture, pos);
	this->initCooldown(pos);
	this->initEffect(effectIndex);
}

//============================================================================
// Updates skill and cooldown.
void Skill::updateSkill(float deltaTime, vector<std::shared_ptr<Character>> targets, Character* caster)
{
	this->setTargets(targets);
	this->m_timer.updateTimer(deltaTime);

	for (int i = 0; i < m_projs.size(); i++)
	{
		this->m_projs[i].updateMovement(deltaTime);
		if (m_projs[i].checkIntersection())
		{
			this->m_effect->affect(caster, m_projs[i].getTarget(), m_factor);
			m_projs.erase(m_projs.begin() + i);
		}
	}
}

//============================================================================
// Uses a skill when it's off cooldown.
bool Skill::useSkill(sf::Vector2f myLoc)
{
	if (this->m_timer.isTimeUp() )
	{
		this->m_timer.setTimer();
		Sound::instance().playSound(m_soundIndex);
		for (auto& target : m_targets)
		{
			auto direction = target->getPosition() - myLoc;
			direction = norm(direction);
			AnimationParams projParams = { sf::Vector2f(ProjRowlengths[m_projType][0], 1), 0.3f };
			auto projectile = Projectile(myLoc, target->getPosition(), this->m_projType, target , projParams);
			m_projs.push_back(projectile);
		}

		return true;
	}
	return false;
	
}

//============================================================================
// get the norm of vector
sf::Vector2f Skill::norm(sf::Vector2f vec)
{
	float l = std::sqrt(std::pow(vec.x,2) + std::pow(vec.y, 2));
	if (l > 0.0f)
		return sf::Vector2f(vec.x / l, vec.y / l);
	else
		return { 0,0 };
}

//============================================================================
// get table of effects
HashTable<int, string> Skill::getTable()
{
	std::unordered_map<int, std::string> map = {
		std::make_pair(_heal, "Heal"),
		std::make_pair(_damage, "Damage"),
		std::make_pair(_defend, "Defend"),
		std::make_pair(_drainLife, "Life steal"),
		std::make_pair(_teleport , "Teleport"),
		std::make_pair(_dmgByDistance, "Distance Dmg")
	};
	return map;
}

//=============================================================================
void Skill::initEffect(const int effectIndex)
{
	switch (effectIndex)
	{
	case _heal:
		this->m_effect = new Heal();
		break;

	case _damage:
		this->m_effect = new Damage();
		break;

	case _defend:
		this->m_effect = new Defend();
		break;
	case _drainLife:
		this->m_effect = new LifeDrain();
		break;
	case _dmgByDistance:
		this->m_effect = new DmgByDistance();
		break;

	case _teleport:
		this->m_effect = new Teleport();
		break;

	default:
		break;
	}
}

//============================================================================

void Skill::initRect(const sf::Texture* texture, const sf::Vector2f pos)
{
	m_rect.setTexture(texture);
	m_rect.setPosition(pos);
	m_rect.setSize({ SKILL_RECT_SIZE, SKILL_RECT_SIZE });
}

//============================================================================

void Skill::initCooldown(const sf::Vector2f pos)
{
	m_cooldownScale.setFillColor(sf::Color(0, 0, 0, 200));
	if (m_cooldownScale.getTexture())
		m_cooldownScale.setSize({ SKILL_RECT_SIZE , 0 });
	m_cooldownScale.setPosition(pos);
}

//=============================================================================

void Skill::draw(sf::RenderWindow& window, bool selected)
{
	if (selected) // if the character is selected we need to print the skill visuals of the character
	{
		updateVisual();
		window.draw(m_rect);
		window.draw(m_cooldownScale);
	}

	for (auto& proj : m_projs) // draw all current projectiles
		proj.draw(window);
}

//==========================================================

void Skill::initInfo(const int effectIndex, const bool onPlayer, 
					 const bool isActive, const float cooldown, 
					 AttackType type)
{
	this->m_info += ("Effect: " + this->effectName(effectIndex) + "\n");
	this->m_info += ("Target type: " + this->targetType(onPlayer) + "\n");
	this->m_info += ("Use type: " + this->useType(isActive) + "\n");
	this->m_info += ("Cooldown: " + this->cooldownStr(cooldown) + "\n");
	this->m_info += ("Attack type :" + this->attackType(type));
}

//==========================================================

std::string Skill::effectName(const int index)
{
	return this->m_effectsTable.getVal(index);
}

//==========================================================

std::string Skill::targetType(const bool player)
{
	if (player)
		return "Player";
	else
		return "Enemy";
}

//==========================================================

std::string Skill::useType(const bool active)
{
	if (active)
		return "Active";
	else
		return "Passive";
}

//==========================================================

std::string Skill::cooldownStr(const float cooldown)
{
	auto string = std::to_string(cooldown);
	if (string[1] != '.')
		string.resize(5);
	else
		string.resize(4);

	return string;
}

//==========================================================

std::string Skill::attackType(AttackType type)
{
	switch (type)
	{
	case AttackType::Multi:
		return "Multi";
	case AttackType::Self:
		return "Self";
	case AttackType::Single:
		return "Single";

	default:
		return "";
	}
}

//==========================================================

void Skill::updateVisual()
{
	m_timer.updateTimer();
	auto timeLeft = m_timer.getTimeLeft();
	timeLeft = std::max(timeLeft, 0.f);
	auto cd = m_timer.getCooldown();
	auto percent = (timeLeft / cd);

	m_cooldownScale.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE * percent });
}

//==========================================================
// check for click - if no targets or cooldown isn't over - skill can't be clicked
bool Skill::handleClick(const sf::Vector2f& pos) 
{
	return !m_targets.empty() && m_isActive && (m_timer.getTimeLeft() <= 0.f) && (m_rect.getGlobalBounds().contains(pos));
}

//==========================================================
// check for hover
bool Skill::checkHover(sf::Vector2f hoverPos)
{
	return this->m_rect.getGlobalBounds().contains(hoverPos);
}
