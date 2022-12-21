#pragma once
#include "Screen.h"
#include "Controller.h"

// This class is in charge of the help screen.
class Help : public Screen
{
public:
	// C-tor & d-tor.
	Help(Controller* controller);
	~Help() = default;

	// Virtuals.
	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	// Protected virtuals.
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	// Buttons
	void initRet();
	virtual void initButtons() override;
	sf::Text m_returnButton;
	bool m_returnHovered = false;
};
