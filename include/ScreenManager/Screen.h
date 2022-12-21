#pragma once
#include "Resources.h"
class Controller;

// All the possibilities of screens.
enum class ScreenState {
	MENU,
	PLAY,
	LEVEL_SELECT,
	HELP,
	SETTINGS,
	EXIT
};

// Class Screen is the screen manager base class.
// All different screens in the program inherit from this class.
class Screen
{
public:
	// C-tor & d-tor.
	Screen(Controller* controller) : m_controller(controller) {}
	virtual ~Screen() = default;

	// Virtuals.
	virtual void run(sf::RenderWindow& window); // Run loop.
	virtual void init() = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	// Some more virtuals.
	virtual void initButtons() = 0;
	virtual void handleHover(const sf::Vector2f& hoverPos) = 0;
	virtual void handleMouseClick(const sf::Vector2f& hoverPos, sf::RenderWindow& window) = 0;

	// Background management.
	void setBG(const int index);
	void drawBG(sf::RenderWindow& window) { window.draw(this->m_bg); }
	sf::RectangleShape m_bg;

	Controller* m_controller; // Context.
};

