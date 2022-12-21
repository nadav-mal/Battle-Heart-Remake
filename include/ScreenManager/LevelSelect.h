#pragma once
#include "Resources.h"
#include "Screen.h"
#include "Controller.h"

// This class is in charge of the level select screen.
// You may choose which level you'd like to play as long as you've acquired it.
class LevelSelect : public Screen
{
public:
	// C-tor & d-tor.
	LevelSelect(Controller* controller);
	~LevelSelect() = default;

	// Virtuals.
	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

	// Unique funcs.
	void manageRowAndCol(int& row, int& col);
	std::string dataToString(const int level);

protected:
	// Protected virtuals.
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	// Initiation funcs
	void initRet();
	void initStart();
	void initHover();
	void initLevelButtons();
	void initlvlDet();
	virtual void initButtons() override;
	void destroyButtons(); // Remakes buttons.

	// Hash table used to receive info regarding a selected level.
	HashTable<int, std::string> getMap();
	HashTable<int, std::string> m_map;

	// Button clicks and hovers.
	int m_lastButtonHovered = -1;
	bool m_levelHovered = false;
	bool m_returnHovered = false;
	bool m_startHovered = false;
	bool m_levelSelected = false;
	sf::Sprite m_startButton;
	sf::Sprite m_levelSelection;
	sf::Sprite m_levelHover;
	sf::Text m_returnButton;
	sf::Text m_levelDetails;
	std::vector<sf::Sprite> m_availableLevels;
};
