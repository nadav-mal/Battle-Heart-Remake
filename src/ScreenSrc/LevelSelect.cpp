#include "ScreenManager/LevelSelect.h"

//-----------------------------------------------

LevelSelect::LevelSelect(Controller* controller)
	: m_map(this->getMap()), Screen(controller)
{
	this->initRet();
	this->initHover();
	this->initStart();
	this->initlvlDet();
	this->setBG(_levelSelect);
}

//-----------------------------------------------

void LevelSelect::update(const float deltaTime)
{}

//-----------------------------------------------

void LevelSelect::init()
{
	this->initButtons();
}

//-----------------------------------------------

void LevelSelect::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	window.draw(this->m_returnButton);
	window.draw(this->m_startButton);

	for (auto& lvl : this->m_availableLevels)
		window.draw(lvl);

	if (this->m_levelSelected)
	{
		window.draw(this->m_levelDetails);
		window.draw(this->m_levelSelection);
	}

	if (this->m_levelHovered)
		window.draw(this->m_levelHover);
}

//-----------------------------------------------

void LevelSelect::manageRowAndCol(int& row, int& col)
{
	col += std::pow(-1, row); // increase or decrease 1 based or row
	if (col >= LEVELS_CHART_COLS || col < 0)
	{
		row++;

		if (col == LEVELS_CHART_COLS)
			col--;
		else if (col == 0)
			col++;
	}
}

//-----------------------------------------------

std::string LevelSelect::dataToString(const int level)
{
	auto lvlInfo = this->m_controller->getLevelInfo(level);
	std::string str = "Players in current level: \n";
	for (int i = 0; i < NUM_OF_PLAYERS; i++)
		if (lvlInfo.m_lvlPlayers[i])
			str += (this->m_map.getVal(i) + ", ");

	str.resize(str.size() - 2);
	str += "\nEnemies in current level: \n";

	for (auto& wave : lvlInfo.m_enemyWaves)
		for (auto& enemy : wave)
			str += (this->m_map.getVal(enemy.x) + ", ");

	str.resize(str.size() - 2);
	return str;
}

//=============================================================================

void LevelSelect::initButtons()
{
	this->initLevelButtons();
}

//=============================================================================

void LevelSelect::handleHover(const sf::Vector2f& hoverPos)
{
	if (this->m_startButton.getGlobalBounds().contains(hoverPos))
	{
		this->m_startButton.setTexture(*Resources::instance().getLSTexture(_startButtonHL));
		//if (!(m_lastButtonHovered == _start && m_startHovered))
		//	this->m_controller->makeSound(int(Sound::Sounds::HOVER));
		m_startHovered = true;
		m_lastButtonHovered = _start;
	}
	else
	{
		this->m_startButton.setTexture(*Resources::instance().getLSTexture(_startButton));
		m_startHovered = false;
	}

	if (this->m_returnButton.getGlobalBounds().contains(hoverPos) )
	{
		this->m_returnButton.setOutlineColor(sf::Color::Black);
		this->m_returnButton.setOutlineThickness(4);
		//if(!(m_lastButtonHovered == _return && m_returnHovered))
		//	this->m_controller->makeSound(int(Sound::Sounds::HOVER));
		m_lastButtonHovered = _return;
		m_returnHovered = true;
	}
	else
	{
		this->m_returnButton.setOutlineThickness(0);
		m_returnHovered = false;
	}

	for (int index = 0; index < this->m_availableLevels.size(); index++)
		if (this->m_availableLevels[index].getGlobalBounds().contains(hoverPos))
		{
			this->m_levelHover.setPosition(this->m_availableLevels[index].getPosition() + lvlSelOffset);
			//if (!(m_lastButtonHovered == index && m_levelHovered))
			//	this->m_controller->makeSound(int(Sound::Sounds::HOVER));
			this->m_levelHovered = true;
			m_lastButtonHovered = index;
			return;
		}
	
	m_levelHovered = false;
			
}

//=============================================================================

void LevelSelect::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (this->m_startButton.getGlobalBounds().contains(clickPos) && this->m_levelSelected)
	{
		this->m_controller->setCurrentScreen(ScreenState::PLAY);
		this->destroyButtons();
	}

	if (this->m_returnButton.getGlobalBounds().contains(clickPos))
	{
		this->m_controller->setCurrentScreen(ScreenState::MENU);
		this->destroyButtons();
	}

	for (int index = 0; index < this->m_availableLevels.size(); index++)
		if (this->m_availableLevels[index].getGlobalBounds().contains(clickPos))
		{
			this->m_levelDetails.setString(this->dataToString(index));
			this->m_levelSelection.setPosition(this->m_availableLevels[index].getPosition() + lvlSelOffset);
			this->m_controller->setCurrLvl(index);
			this->m_levelSelected = true;
		}
}

//=============================================================================

void LevelSelect::initRet()
{
	this->m_returnButton.setString("Return");
	this->m_returnButton.setFont(*Resources::instance().getFont());
	this->m_returnButton.setStyle(sf::Text::Style::Bold);
	this->m_returnButton.setCharacterSize(60);
	this->m_returnButton.setPosition(returnButtonPos);
}

//=============================================================================

void LevelSelect::initStart()
{
	this->m_startButton.setTexture(*Resources::instance().getLSTexture(_startButton));
	this->m_startButton.setPosition(startButtonPos);
}

//=============================================================================

void LevelSelect::initHover()
{
	this->m_levelHover.setTexture(*Resources::instance().getLSTexture(_levelSelection));
	this->m_levelSelection.setTexture(*Resources::instance().getLSTexture(_levelSelection));
}

//-----------------------------------------------

void LevelSelect::initLevelButtons()
{
	sf::Sprite tempSprite;
	sf::Vector2f pos;
	int row = 0, col = 0;
	tempSprite.setTexture(*Resources::instance().getLSTexture(_lvlCompleted));
	for (int i = 0; i < this->m_controller->getMaxLvlAchieved() + 1; i++)
	{
		if (i == this->m_controller->getMaxLvlAchieved())
			tempSprite.setTexture(*Resources::instance().getLSTexture(_currLvlIcon));

		pos = { lsLevelsStartPos.x + col * lsLevelsOffset.x,
				lsLevelsStartPos.y + row * lsLevelsOffset.y };
		tempSprite.setPosition(pos);
		this->m_availableLevels.push_back(tempSprite);
		this->manageRowAndCol(row, col);
	}
}

//=============================================================================

void LevelSelect::initlvlDet()
{
	this->m_levelDetails.setFont(*Resources::instance().getFont());
	this->m_levelDetails.setStyle(sf::Text::Style::Bold);
	this->m_levelDetails.setCharacterSize(36);
	this->m_levelDetails.setPosition(levelDetailsStart);
	this->m_levelDetails.setColor(sf::Color::Black);
	this->m_levelDetails.setOutlineColor(sf::Color::White);
	this->m_levelDetails.setOutlineThickness(1);
}

//=============================================================================

void LevelSelect::destroyButtons()
{
	this->m_availableLevels.clear();
}

//=============================================================================

HashTable<int, std::string> LevelSelect::getMap()
{
	std::unordered_map<int, std::string> map = {
		std::make_pair(_cleric, "Cleric"),
		std::make_pair(_knight, "Knight"),
		std::make_pair(_archer, "Archer"),
		std::make_pair(_wizard, "Wizard"),
		std::make_pair(_wolf, "Wolf"),
		std::make_pair(_darkCleric, "DarkCleric"),
		std::make_pair(_demon, "Demon"),
		std::make_pair(_dragon, "Dragon")
	};
	return map;
}

//=============================================================================
