#pragma once
#include "Resources.h"
#include "HashTable.h"

// This class is in charge of loading the levels.
// The read is made from a text file.
class LevelLoader
{
public:
	// C-tor and d-tor.
	LevelLoader(const string fileName);
	~LevelLoader() = default;

	// Management.
	std::ifstream openFile(const string fileName);
	LevelInfo getLevel(const int levelNum) const { return this->m_levels[levelNum]; }
	bool getGameEnded(const int currLv) const { return currLv >= this->m_levels.size(); }
	unsigned int getMaxLevel() const { return this->m_numOfLevels; }

private:
	// Stores data regarding the levels.
	std::vector<LevelInfo> m_levels = {};
	unsigned int m_numOfLevels;
	HashTable<string, int> m_table;

	// Reading functions.
	void readFromFile(const string fileName);
	std::vector<sf::Vector2i> readWave(std::ifstream& file);
	int readFullNum(std::ifstream& file, char c);
};