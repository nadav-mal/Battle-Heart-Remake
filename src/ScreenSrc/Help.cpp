#include "ScreenManager/Help.h"

Help::Help(Controller* controller)
	: Screen(controller)
{
	this->initButtons();
	this->setBG(_helpBG);
}

//===================================================
void Help::update(const float deltaTime)
{}


//===================================================

void Help::init()
{}

//===================================================

void Help::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	window.draw(this->m_returnButton);
}

//===================================================

void Help::initButtons()
{
	this->initRet();
}

//===================================================

void Help::handleHover(const sf::Vector2f& hoverPos)
{
	if (this->m_returnButton.getGlobalBounds().contains(hoverPos))
	{
		this->m_returnButton.setOutlineColor(sf::Color::Black);
		this->m_returnButton.setOutlineThickness(4);
		//if(!m_returnHovered)
		//	this->m_controller->makeSound(int(Sound::Sounds::HOVER));
		m_returnHovered = true;
	}
	else
	{
		this->m_returnButton.setOutlineThickness(0);
		m_returnHovered = false;
	}
}

//===================================================

void Help::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (this->m_returnButton.getGlobalBounds().contains(clickPos))
		this->m_controller->setCurrentScreen(ScreenState::MENU);
}

//===================================================

void Help::initRet()
{
	this->m_returnButton.setString("Return");
	this->m_returnButton.setFont(*Resources::instance().getFont());
	this->m_returnButton.setStyle(sf::Text::Style::Bold);
	this->m_returnButton.setCharacterSize(60);
	auto pos = sf::Vector2f(returnButtonPos.x + buttonOffset / 6, returnButtonPos.y);
	this->m_returnButton.setPosition(pos);
}