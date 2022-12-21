#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f pos , int maxValue)
	:m_max(maxValue),m_curr(maxValue), m_hitTimer(1.2f) , m_showTimer(3.f)
{
	this->initBars(pos);
	this->initText(pos);
}

//====================================================================
// Updating health's bar position and hp amount 
void HealthBar::updateHealthBar(float statVal, const sf::Vector2f& pos)
{
	this->setPosition(pos);
	auto size = m_bar.getSize();

	statVal = std::min(statVal, m_max); // health can not be more than m_max
	auto healthLost = m_curr - statVal ;
	
	
	if (healthLost > 0.f && m_hitTimer.isTimeUp() )
	{
		m_hitDamage.setFillColor(sf::Color::Red);
		m_hitDamage.setString(std::to_string(int(std::ceil(healthLost))));
		m_hitHealth.setSize({m_curr * BAR_WIDTH / m_max , size.y });
		m_hitTimer.setTimer();
	}
	else if (healthLost < 0.f)
	{
		m_hitDamage.setFillColor(sf::Color::Green);
		m_hitDamage.setString(std::to_string(int(std::floor(-healthLost))));
		m_hitHealth.setSize({statVal * BAR_WIDTH / m_max , size.y });
		m_hitTimer.setTimer();
	}

	m_curr = statVal; // update current hp to be the new Stat

	m_showTimer.updateTimer();
	m_hitTimer.updateTimer();
	auto newX = std::max(statVal * BAR_WIDTH / m_max , 0.f);
	m_currHealth.setSize(sf::Vector2f(newX, size.y));
}

//====================================================================

// init size and colours of the bars 
void HealthBar::initBars(const sf::Vector2f pos)
{
	auto size = sf::Vector2f(BAR_WIDTH, BAR_HEIGHT);
	auto origin = m_bar.getOrigin();
	m_bar.setOrigin(origin + healthOffset);
	m_bar.setSize(size);
	m_bar.setPosition(pos);
	m_bar.setFillColor(sf::Color::Black);
	m_bar.setOutlineColor(sf::Color::Black);
	m_bar.setOutlineThickness(3);

	m_currHealth = m_hitHealth = m_bar;
	m_currHealth.setFillColor(sf::Color::Green);
	m_hitHealth.setFillColor(sf::Color::Red);
}

//====================================================================

void HealthBar::draw(sf::RenderWindow& window)
{
	if (!m_showTimer.isTimeUp()) // show hp bar only if show() has been actived
	{
		window.draw(m_bar);
		if (!m_hitTimer.isTimeUp()) // show hit bar if got hit / healed
		{
			window.draw(m_hitDamage);
			window.draw(m_hitHealth);
			
		}
		window.draw(m_currHealth);
	}
}

//=====================================================================
// move the health bar to follow the target ( move to position)
void HealthBar::setPosition(const sf::Vector2f pos)
{
	m_bar.setPosition(pos);
	m_currHealth.setPosition(pos);
	m_hitHealth.setPosition(pos);
	m_hitDamage.setPosition(pos);
}

//======================================================================
// init text stats , font , size and etc.
void HealthBar::initText(const sf::Vector2f pos)
{
	m_hitDamage.setCharacterSize(20);
	m_hitDamage.setOutlineThickness(2);
	m_hitDamage.setStyle(sf::Text::Bold);
	m_hitDamage.setColor(sf::Color::Black);
	m_hitDamage.setFont(*Resources::instance().getFont());
	m_hitDamage.setOrigin(m_hitDamage.getOrigin() + healthTextOffset);
	m_hitDamage.setPosition(pos);
}