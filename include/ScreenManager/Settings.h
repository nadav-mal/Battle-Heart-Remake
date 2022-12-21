#pragma once
#include "Screen.h"
#include "Controller.h"

// This class is in charge of the settings screen.
class Settings : public Screen
{
public:
	// C-tor & d-tor.
	Settings(Controller* controller);
	~Settings() = default;

	// Virtual functions.
	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	virtual void initButtons() override;
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

	// Unique functions.
	void initVolButtons();
	void checkButton(sf::Vector2f hoverPos, int index);

private:
	// Unique members.
	void initRet();
	sf::Text m_returnButton;
	std::vector<sf::Sprite> m_volButtons;
	bool m_returnHovered = false;
};
