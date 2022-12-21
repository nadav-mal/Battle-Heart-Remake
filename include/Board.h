#pragma once

#include "Resources.h"
#include "Characters/Cleric.h"
#include "Characters/Knight.h"
#include "Characters/Wizard.h"
#include "Characters/Archer.h"
#include "Characters/Demon.h"
#include "Characters/Wolf.h"
#include "Characters/Dragon.h"
#include "Characters/DarkCleric.h"
#include "HashTable.h"
#include "Controller.h"

using namespace std;

class Board 
{
public:
	Board(const LevelInfo& currLevelInfo, Controller* controller);
	bool handleFirstClick(sf::Vector2f location);
	bool handleSecondClick(sf::Vector2f location);
	int	updateBoard(float deltaTime, bool charSelected);
	void drawBoard(sf::RenderWindow& window, bool charSelected);
	void hoverEnemies(const sf::Vector2f& hoverPos);
	void hoverPlayers(const sf::Vector2f& hoverPos);
	void hoverSkills(const sf::Vector2f& hoverPos);

	bool checkCleric() { 
		Player* player = this->m_currPlayer.get();
		return dynamic_cast<Cleric*>(player);
	}

private:
	// Members
	vector<shared_ptr<Player>> m_players;
	vector<shared_ptr<Enemy>> m_enemies;
	int m_currWave;
	int m_currPlayerHovered = -1;
	int m_currEnemyHovered = -1;
	int m_currSkillHovered = -1;
	std::shared_ptr<Player> m_currPlayer;
	std::vector<std::vector<sf::Vector2i>> m_enemyWaves;
	sf::Sprite m_selected;
	sf::Sprite m_hovered;
	sf::Sprite m_skillHover;
	sf::Sprite m_skillInfoBG;
	sf::Text m_hoveredSkillInfo;
	bool m_isHovered = false;
	bool m_skillHovered = false;
	Controller* m_controller;

	// Funcs
	HashTable<int, shared_ptr<Player>> getPlayersTable();
	HashTable<int, shared_ptr<Enemy>> getEnemiesTable();

	// init functions - init members and interfaces used on characters
	void initPlayers(const bool lvlPlayers[NUM_OF_PLAYERS]);
	void initEnemies(const std::vector<sf::Vector2i> enemyWave);
	void initSelected();
	void initHovered();

	// update functions - update objects by time passed
	void updatePlayers(const float deltaTime);
	void updateEnemies(const float deltaTime, const sf::Vector2f dist);
	void updateEnemyDest();

	// check for characters death
	void updatePlayersDeath(std::shared_ptr<Player> character, float deltaTime, int& index);
	void updateEnemysDeath(std::shared_ptr<Enemy> character, float deltaTime, int& index);

	// draw functions - draw objects
	void drawObjects(sf::RenderWindow& window);
	
	// movement and behavior functions
	void seperation(Enemy* enemy, sf::Vector2f steerForce, float deltaTime);
	void playerBehavior(std::shared_ptr<Player> character, float deltaTime);
	void enemyBehavior(std::shared_ptr<Enemy> enemy, float deltaTime, sf::Vector2f pos);


	vector<sf::Vector2f> createObstaclesVec();
	sf::Vector2f adjustLocation(sf::Vector2f location);

	template <class Type>
	bool checkHover(Type character, const sf::Vector2f pos);

	template <class Type>
	Type sortObjects(Type vector);

	bool checkMoving() const; 
};


// check if a character is hovered
template<class Type>
inline bool Board::checkHover(Type character, const sf::Vector2f pos)
{
	if (character->getSprite().getGlobalBounds().contains(pos))
	{
		this->m_hovered.setPosition(adjustLocation(character->getPosition()));
		this->m_isHovered = true;
		return true;
	}
	return false;
}


// sort vector of Enemy or Player
template <class Type>
inline Type Board::sortObjects(Type vector)
{
	auto copy = vector;
	std::sort(copy.begin(), copy.end(),
		[](auto obj1, auto obj2)
		{ return obj1->getPosition().y < obj2->getPosition().y; });
	return copy;
}

