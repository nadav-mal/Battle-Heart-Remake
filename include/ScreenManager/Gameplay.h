#pragma once
#include "Screen.h"
#include "Board.h"

// This class is in charge of the gameplay screen.
class Gameplay : public Screen
{
public:
	// C-tor & d-tor.
	Gameplay(Controller* controller);
	virtual ~Gameplay() = default;

	// Virtuals
	virtual void init() override;
	virtual void update(const float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;

	bool winLevel(); // Checks if the level is won.
	void winGame(); // Wins the game (just exits).

protected:
	// Protected virtuals.
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	// Lots of buttons.
	virtual void initButtons() override;
	void checkButton(sf::Vector2f hoverPos, GameButtons reg, GameButtons hl, ButtonIndexes index);
	void checkPause(sf::Vector2f hoverPos);
	void cont();
	void restart();
	void exitGame();
	sf::Sprite m_gameState;
	sf::Sprite m_pauseButton;
	vector<sf::Sprite> m_buttons;

	Board m_board; // Stores the main data of the game.

	// Hovering and game states management.
	bool m_paused = false;
	bool m_continued = false;
	bool m_wonLevel = false;
	bool m_wonGame = false;
	bool m_lost = false;
	bool m_charSelected = false;
	bool m_hoveredPause = false;
	int m_lastButtonHovered = -1;
	unsigned int m_currLvl;
};