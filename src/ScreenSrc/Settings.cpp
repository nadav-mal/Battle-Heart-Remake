#include "ScreenManager/Settings.h"

Settings::Settings(Controller* controller)
	: Screen(controller)
{
	this->initButtons();
	this->setBG(_settingsBG);
}

void Settings::update(const float deltaTime)
{}

void Settings::init()
{}

void Settings::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	window.draw(this->m_returnButton);

	for (auto& button : this->m_volButtons)
		window.draw(button);
}

void Settings::initButtons()
{
	this->initRet();
	this->initVolButtons();
}

void Settings::handleHover(const sf::Vector2f& hoverPos)
{
	if (this->m_returnButton.getGlobalBounds().contains(hoverPos))
	{
		this->m_returnButton.setOutlineColor(sf::Color::Black);
		this->m_returnButton.setOutlineThickness(4);
		//if (!m_returnHovered)
		//this->m_controller->makeSound(int(Sound::Sounds::HOVER));
		m_returnHovered = true;
	}
	else
	{
		this->m_returnButton.setOutlineThickness(0);
		m_returnHovered = false;
	}

	for (int i = 0; i < this->m_volButtons.size(); i++)
		this->checkButton(hoverPos, i);
}

void Settings::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (this->m_returnButton.getGlobalBounds().contains(clickPos))
		this->m_controller->setCurrentScreen(ScreenState::MENU);
	else
		for (int i = 0; i < this->m_volButtons.size(); i++)
			if (this->m_volButtons[i].getGlobalBounds().contains(clickPos))
				this->m_controller->manageSound(Sound::VolumeControl(i));
}

void Settings::initVolButtons()
{
	for (int i = 0; i < (NUM_OF_VOL_BUTTONS / 2); i++)
	{
		sf::Sprite temp;
		temp.setPosition(volButtonStart.x + buttonOffset * i, volButtonStart.y);
		temp.setTexture(*Resources::instance().getVolText(i));
		this->m_volButtons.push_back(temp);
	}
}

void Settings::checkButton(sf::Vector2f hoverPos, int index)
{
	if (this->m_volButtons[index].getGlobalBounds().contains(hoverPos))
		this->m_volButtons[index].setTexture(*Resources::instance().getVolText(index + (NUM_OF_VOL_BUTTONS / 2)));
	else
		this->m_volButtons[index].setTexture(*Resources::instance().getVolText(index));
}

void Settings::initRet()
{
	this->m_returnButton.setString("Return");
	this->m_returnButton.setFont(*Resources::instance().getFont());
	this->m_returnButton.setStyle(sf::Text::Style::Bold);
	this->m_returnButton.setCharacterSize(60);
	auto pos = sf::Vector2f(returnButtonPos.x + buttonOffset / 7, returnButtonPos.y);
	this->m_returnButton.setPosition(pos);
}
