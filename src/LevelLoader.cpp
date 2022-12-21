#include "LevelLoader.h"

LevelLoader::LevelLoader(const string fileName)
    : m_table(HashTable(levelsMap))
{
	this->readFromFile(fileName);
}

std::ifstream LevelLoader::openFile(const string fileName)
{
    std::ifstream file(fileName);
    if (file.fail())
        throw std::invalid_argument("Cannot open file\n");

    return file;
}

void LevelLoader::readFromFile(const string fileName)
{
    std::ifstream file = openFile(fileName);
    char c;
    string word;
    struct LevelInfo currLvlInfo = {};
    unsigned int currLevel = 0;

    while (file.get(c)) // While there's something to read in the file.
    {
        if (isalpha(c)) // Reads a word.
            word += c;
        // If a number appears after the word then it's enemies or a new level.
        else if (isdigit(c))
        {
            sf::Vector2i feedback = { this->m_table.getVal(word),
                                      this->readFullNum(file, c) };

            // If new level.
            if (feedback.x == NEW_LEVEL_DETECTED)
            {
                if (currLevel != 0)
                {
                    this->m_levels.push_back(currLvlInfo);
                    currLvlInfo = { 0 };
                }
                currLevel++;
            }
            word.clear();
        }
        // If player.
        else if (c == '\n' && word != "")
        {
            currLvlInfo.m_lvlPlayers[this->m_table.getVal(word)] = true;
            word.clear();
        }
        // If new wave of enemies.
        else if (c == WAVE)
            currLvlInfo.m_enemyWaves.push_back(this->readWave(file));
    }

    this->m_levels.push_back(currLvlInfo);
    // Might come in use, or not.
    this->m_numOfLevels = currLevel;
}

std::vector<sf::Vector2i> LevelLoader::readWave(std::ifstream& file)
{
    char c = ' ';
    string word = "";
    sf::Vector2i feedback(0, 0);
    std::vector<sf::Vector2i> wave;

    while (c != WAVE)
    {
        if (isalpha(c))
            word += c;
        else if (isdigit(c))
        {
            wave.push_back({ this->m_table.getVal(word), this->readFullNum(file, c) });
            word.clear();
        }

        file.get(c);
    }
    file.get(c);
    return wave;
}


int LevelLoader::readFullNum(std::ifstream& file, char c)
{
    char timeLim[2] = { 0 };
    auto counter = 0;

    while (isdigit(c))
    {
        timeLim[counter] = c;
        counter++;
        file.get(c);
    }

    return atoi(timeLim);
}