#include "ScreenManager/Menu.h"

Menu::Menu(Controller* controller)
	: Screen(controller)
{
	this->m_controller->makeMusic("menuMusic.ogg");
	this->initButtons();
	this->setBG(_menu);
}

void Menu::update(const float deltaTime)
{}

void Menu::init()
{}

void Menu::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	for (auto& button : this->m_buttons)
		window.draw(button);
}

//=============================================================================

void Menu::initButtons()
{
	sf::Text tempText;
	tempText.setFont(*Resources::instance().getFont());
	tempText.setStyle(sf::Text::Style::Bold);
	tempText.setCharacterSize(70);

	for (int i = 0; i < NUM_OF_MBUTTONS; i++)
	{
		tempText.setString(MENU_BUTTONS_STRINGS[i]);

		if (i == _battle)
			tempText.setPosition(battleButtonPos);
		else
			tempText.setPosition(sf::Vector2f(screenButtonsStart.x, screenButtonsStart.y + buttonOffset * i));

		this->m_buttons.push_back(tempText);
	}
}

//=============================================================================

void Menu::handleHover(const sf::Vector2f& hoverPos)
{
	for (int index = 0; index < this->m_buttons.size(); index++)
	{
		if (this->m_buttons[index].getGlobalBounds().contains(hoverPos))
		{
			this->m_buttons[index].setOutlineColor(sf::Color::Black);
			this->m_buttons[index].setOutlineThickness(4);
			///if(m_lastButtonHovered != index)
			//	this->m_controller->makeSound(int(Sound::Sounds::HOVER));
			m_lastButtonHovered = index;
			return;
		}
		else
			this->m_buttons[index].setOutlineThickness(0);
	}
	m_lastButtonHovered = -1;
}

//=============================================================================

void Menu::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	for (int index = 0; index < this->m_buttons.size(); index++)
		if (this->m_buttons[index].getGlobalBounds().contains(clickPos))
		{
			switch (index)
			{
			// Clicking on battle results in continuing from last point.
			case MenuButtons::_battle:
				this->m_controller->makeSound(Sound::Sounds::BATTLE);
				this->m_controller->setCurrentScreen(ScreenState::PLAY);
				return;
			// Clicking on levels results in picking a level.
			case MenuButtons::_levels:
				this->m_controller->setCurrentScreen(ScreenState::LEVEL_SELECT);
				return;
			// Clicking on help displays info on how to play.
			case MenuButtons::_help:
				this->m_controller->setCurrentScreen(ScreenState::HELP);
				return;
			case MenuButtons::_settings:
				this->m_controller->setCurrentScreen(ScreenState::SETTINGS);
				return;
			// Exits game.
			case MenuButtons::_escape:
				this->m_controller->setCurrentScreen(ScreenState::EXIT);
				return;
			}
		}
}
