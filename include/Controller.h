#pragma once
#include "LevelLoader.h"
#include "ScreenManager/Screen.h"

// This class is in charge of controlling the whole game process
// and switching between different screens while managing those.
class Controller
{
public:
	// C-tor and d-tor.
	Controller();
	~Controller() = default;

	void run(); // Main function of the game. Game loop.

	// Setters.
	void setCurrentScreen(ScreenState state);
	void setCurrLvl(int level) { this->m_currentLevel = level; }
	void setMaxLvlAchieved(int newMax);

	// Audio.
	void makeSound(Sound::Sounds index)					{ Sound::instance().playSound(int(index)); }
	void makeMusic(const std::string fileName)			{ Sound::instance().playMusic(fileName); }
	void manageSound(Sound::VolumeControl action);

	// Getters.
	int getMaxLvlAchieved()				const { return this->m_maxLevelAchieved; }
	int getCurrLvl()					const { return this->m_currentLevel; }
	bool getGameWon(int level)			const { return this->m_levelLoader.getGameEnded(level); }
	LevelInfo getLevelInfo(int level)	const { return this->m_levelLoader.getLevel(level); }
	unsigned int getNumOfLevels()		const { return this->m_levelLoader.getMaxLevel(); }
	
private:
	// Screens.
	void initScreens();
	void swapScreen();
	std::vector<std::unique_ptr<Screen>> m_screens; // Stores the screens.
	ScreenState m_currentScreen = ScreenState::MENU;
	bool m_changeScreen = false;

	// Levels.
	int m_currentLevel = 0;
	int m_maxLevelAchieved = 0;
	LevelLoader m_levelLoader;

	// SFML.
	sf::RenderWindow m_window;
	sf::Clock m_clock;
};
