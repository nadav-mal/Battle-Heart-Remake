#pragma once
#include "ScreenManager/Screen.h"
#include "Controller.h"

// This class is in charge of the menu screen.
class Menu : public Screen
{
public:
	// C-tor & d-tor.
	Menu(Controller* controller);
	~Menu() = default;

	// Virtual functions.
	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	// Protected virtuals.
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	// Menu buttons
	virtual void initButtons() override;
	int m_lastButtonHovered = -1;
	std::vector<sf::Text> m_buttons;
};
