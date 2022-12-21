#include "Resources.h"

Resources::Resources()
{

	this->loadResources();
}

//=======================================================================================

Resources::~Resources(){}

//=======================================================================================

Resources& Resources::instance()
{
	static Resources inst;
	return inst;
}

//======================================================================================

void Resources::loadResources()
{
	try {

		for (int i = 0; i < NUM_OF_OBJECTS; i++)
			if (!m_textures[i].loadFromFile(textures[i]))
				throw std::runtime_error("Cannot load object's texture from file\n");
			
		for (int i = 0; i < NUM_OF_BG; i++)
			if (!m_bgTextures[i].loadFromFile(bgTextures[i]))
				throw std::runtime_error("Cannot load background's texture from file\n");
			
		for (int i = 0; i < NUM_OF_PLAYERS; i++)
			for (int j = 0; j < NUM_OF_SKILLS; j++)
				if (!m_skillTextures[i][j].loadFromFile(skillTextures[i][j]))
					throw std::runtime_error("Cannot load Skill's texture from file\n");

		for (int i = 0; i < NUM_OF_LS_TEXTS; i++)
			if (!m_lsTextures[i].loadFromFile(lvSelTexts[i]))
				throw std::runtime_error("Cannot load object's texture from file\n");

		for (int i = 0; i < NUM_OF_GAME_STATES; i++)
			if (!m_gameStates[i].loadFromFile(gameStateTexts[i]))
				throw std::runtime_error("Cannot load game state texture from file\n");

		for (int i = 0; i < NUM_OF_GBUTTONS; i++)
			if (!m_gameButtonsTextures[i].loadFromFile(gameButtonsTexts[i]))
				throw std::runtime_error("Cannot load game button's texture from file\n");

		for (int i = 0; i < NUM_OF_PROJ - 1; i++)
			if (!m_projTextures[i].loadFromFile(ProjTextrues[i]))
				throw std::runtime_error("Cannot load projectile's texture from file\n");
			
		for (int i = 0; i < NUM_OF_VOL_BUTTONS; i++)
			if (!m_volTextures[i].loadFromFile(volTextures[i]))
				throw std::runtime_error("Cannot load projectile's texture from file\n");

		for (int i = 0; i < soundList.size(); i++)
		{
			sf::SoundBuffer temp;
			if (!temp.loadFromFile(soundList[i]))
			{
				//throw std::runtime_error("Cannot load sound buffer from file\n");
				this->m_buffers.push_back(temp);
			}
			else
				this->m_buffers.push_back(temp);
		}

		if (!this->m_font.loadFromFile(MAIN_FONT))
			throw std::runtime_error("Cannot set text font\n");
	}
	catch (std::runtime_error& e) // catch exeption if a file is failed to load
	{
		std::cerr << e.what();
		exit(EXIT_FAILURE);
	}

}
