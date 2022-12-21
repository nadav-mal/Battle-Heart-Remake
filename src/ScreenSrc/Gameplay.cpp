#include "ScreenManager/Gameplay.h"

//-------------------------------------------------

Gameplay::Gameplay(Controller* controller)
	: m_currLvl(0), m_board(Board(controller->getLevelInfo(0), controller)),
	Screen(controller)
{
	this->initButtons();
}

//-------------------------------------------------

void Gameplay::update(const float deltaTime)
{
	if (!this->m_wonLevel && !this->m_paused && !this->m_lost)
	{

		auto state = this->m_board.updateBoard(deltaTime, this->m_charSelected);
		if (state == _winLevel)
		{
			if (!this->winLevel())
				this->winGame();
			else
				this->m_gameState.setTexture(*Resources::instance().getGameStateText(_winLevel));
		}
		else if (state == _loseLevel)
		{
			this->m_lost = true;
			this->m_gameState.setTexture(*Resources::instance().getGameStateText(_loseLevel));
		}
	}
}

//-------------------------------------------------

void Gameplay::init()
{
	this->m_currLvl = this->m_controller->getCurrLvl();
	this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl), m_controller);
	this->m_controller->makeMusic(levelsMusic[(this->m_currLvl % levelsMusic.size())]);
	
	auto bgIndex = this->m_currLvl % NUM_OF_BACKGROUNDS;
	this->setBG(bgIndex + _firstLevel);
}

//-------------------------------------------------

void Gameplay::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	this->m_board.drawBoard(window, this->m_charSelected);
	window.draw(this->m_pauseButton);

	if (this->m_paused || this->m_wonLevel || this->m_lost)
	{
		window.draw(this->m_gameState);
		if (!this->m_lost)
			window.draw(this->m_buttons[_continueIndex]);

		window.draw(this->m_buttons[_restartIndex]);
		window.draw(this->m_buttons[_exitIndex]);
	}
}

//-------------------------------------------------

bool Gameplay::winLevel()
{
	this->m_currLvl++;
	this->m_controller->setMaxLvlAchieved(this->m_currLvl);
	this->m_controller->setCurrLvl(this->m_currLvl);
	if (this->m_controller->getGameWon(this->m_currLvl))
		return false;

	this->m_wonLevel = true;
	return true;
}

//-------------------------------------------------

void Gameplay::winGame()
{
	this->m_wonGame = true;
	exit(EXIT_SUCCESS);
}

//-------------------------------------------------

void Gameplay::initButtons()
{
	// Pause
	this->m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pause));
	this->m_pauseButton.setPosition(pauseButtonPos);

	for (int i = 1; i < ((NUM_OF_GBUTTONS - 1) / 2); i++)
	{
		sf::Sprite temp;
		temp.setTexture(*Resources::instance().getGameButtonText(i));
		auto pos = sf::Vector2f(gameButtonPos.x, gameButtonPos.y + (i * buttonOffset * 0.55f));
		temp.setPosition(pos);
		this->m_buttons.push_back(temp);
	}
}

//-------------------------------------------------

void Gameplay::handleHover(const sf::Vector2f& hoverPos)
{
	// If not paused
	if (!this->m_paused && !this->m_wonLevel && !this->m_lost)
	{
		this->m_board.hoverSkills(hoverPos);
		this->checkPause(hoverPos);
		auto clericSelected = this->m_board.checkCleric();
		if (this->m_charSelected && !clericSelected)
			this->m_board.hoverEnemies(hoverPos);
		else
			this->m_board.hoverPlayers(hoverPos);
	}
	else
	{
		// Continue
		if (!this->m_lost)
			this->checkButton(hoverPos, _continue, _continueHL, _continueIndex);
		// Restart
		this->checkButton(hoverPos, _restart, _restartHL, _restartIndex);
		//Exit
		this->checkButton(hoverPos, _exitButton, _exitButtonHL, _exitIndex);
	}
}

//-------------------------------------------------

void Gameplay::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (this->m_paused || this->m_wonLevel || this->m_lost)
	{
		if (!this->m_lost && this->m_buttons[_continueIndex].getGlobalBounds().contains(clickPos))
			this->cont();
		else if (this->m_buttons[_restartIndex].getGlobalBounds().contains(clickPos))
			this->restart();
		else if (this->m_buttons[_exitIndex].getGlobalBounds().contains(clickPos))
			this->exitGame();
	}
	else
	{
		if (!this->m_charSelected)
			this->m_charSelected = this->m_board.handleFirstClick(clickPos);

		else // if a click made the player move - charSelected is no longer true
			this->m_charSelected = !m_board.handleSecondClick(clickPos);
	}

	if (this->m_pauseButton.getGlobalBounds().contains(clickPos))
	{
		this->m_controller->makeSound(Sound::Sounds::BUTTON_CLICK);
		this->m_gameState.setTexture(*Resources::instance().getGameStateText(_pauseLevel));
		this->m_paused = true;
	}
}

//-------------------------------------------------

void Gameplay::checkButton(sf::Vector2f hoverPos, GameButtons reg, GameButtons hl, ButtonIndexes index)
{
	if (this->m_buttons[index].getGlobalBounds().contains(hoverPos))
	{
		this->m_buttons[index].setTexture(*Resources::instance().getGameButtonText(hl));
		
		if (reg != this->m_lastButtonHovered)
		{
			this->m_lastButtonHovered = int(reg);
			//this->m_controller->makeSound(int(Sound::Sounds::HOVER));
		}
	}
	else
		this->m_buttons[index].setTexture(*Resources::instance().getGameButtonText(reg));
}

//-------------------------------------------------

void Gameplay::checkPause(sf::Vector2f hoverPos)
{
	if (this->m_pauseButton.getGlobalBounds().contains(hoverPos))
	{
		if (!this->m_hoveredPause)
		{
			//this->m_controller->makeSound(int(Sound::Sounds::HOVER));
			this->m_hoveredPause = true;
		}
		this->m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pauseHL));
	}
	else
	{
		this->m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pause));
		this->m_hoveredPause = false;
	}
}

//-------------------------------------------------

void Gameplay::cont()
{
	this->m_controller->makeSound(Sound::Sounds::BUTTON_CLICK);

	if (this->m_wonLevel)
	{
		this->m_charSelected = false;
		this->m_wonLevel = false;
		this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl), m_controller);
		auto bgIndex = this->m_currLvl % NUM_OF_BACKGROUNDS;
		this->setBG(bgIndex + _firstLevel);
	}
	else
		this->m_paused = false;
}

//-------------------------------------------------

void Gameplay::restart()
{
	this->m_controller->makeSound(Sound::Sounds::BUTTON_CLICK);

	if (this->m_wonLevel)
		this->m_board = Board(this->m_controller->getLevelInfo(--this->m_currLvl), m_controller);
	else
		this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl), m_controller);

	this->m_wonLevel = false;
	this->m_lost = false;
	this->m_paused = false;
}

//-------------------------------------------------

void Gameplay::exitGame()
{
	this->m_controller->makeSound(Sound::Sounds::BUTTON_CLICK);
	this->m_lost = false;
	this->m_wonLevel = false;
	this->m_paused = false;
	this->m_controller->makeMusic("menuMusic.ogg");
	this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl), m_controller);
	this->m_controller->setCurrentScreen(ScreenState::MENU);
}

//-------------------------------------------------
