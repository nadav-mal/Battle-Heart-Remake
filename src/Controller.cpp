
#include "Controller.h"
#include "ScreenManager/Gameplay.h"
#include "ScreenManager/Menu.h"
#include "ScreenManager/LevelSelect.h"
#include "ScreenManager/Help.h"
#include "ScreenManager/Settings.h"

Controller::Controller()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battle Heart"),
	  m_levelLoader(LevelLoader(LevelsFileName))
{
	this->m_window.setFramerateLimit(60);
	this->initScreens();
	this->makeMusic("menuMusic.ogg");
}

//=======================================================================================

void Controller::run()
{
	float deltaTime = 0.f;
	try
	{
		while (this->m_currentScreen != ScreenState::EXIT)
		{
			deltaTime = this->m_clock.restart().asSeconds();
			this->m_window.clear();
			this->m_screens[int(this->m_currentScreen)]->draw(this->m_window);
			this->m_screens[int(this->m_currentScreen)]->run(this->m_window);
			this->m_window.display();
			this->swapScreen();
			this->m_screens[int(this->m_currentScreen)]->update(deltaTime);
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what();
		exit(EXIT_FAILURE);
	}
}

//=======================================================================================

void Controller::setCurrentScreen(ScreenState state)
{
	this->m_currentScreen = state;
	this->m_changeScreen = true;
}

//=======================================================================================

void Controller::setMaxLvlAchieved(int newMax)
{
	if (this->m_maxLevelAchieved < newMax)
		this->m_maxLevelAchieved = newMax;
}

//=======================================================================================

void Controller::manageSound(Sound::VolumeControl action)
{
	switch (action)
	{
	case Sound::VolumeControl::INC:
		Sound::instance().incVolume();
		break;

	case Sound::VolumeControl::DEC:
		Sound::instance().decVolume();
		break;

	case Sound::VolumeControl::MUTE:
		Sound::instance().muteVolume();
		break;

	default:
		break;
	}
}

//=======================================================================================

void Controller::initScreens()
{
	this->m_screens.push_back(std::make_unique<Menu>(this));
	this->m_screens.push_back(std::make_unique<Gameplay>(this));
	this->m_screens.push_back(std::make_unique<LevelSelect>(this));
	this->m_screens.push_back(std::make_unique<Help>(this));
	this->m_screens.push_back(std::make_unique<Settings>(this));
}

//=======================================================================================

void Controller::swapScreen()
{
    if (this->m_changeScreen)
    {
		if (this->m_currentScreen == ScreenState::EXIT)
			exit(EXIT_SUCCESS);
        m_screens[int(this->m_currentScreen)]->init();
        this->m_changeScreen = false;
    }
}
