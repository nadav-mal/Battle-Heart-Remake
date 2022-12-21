#pragma once

// Includes -------------------------------------

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "macros.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <memory>
#include <queue>
#include <algorithm>
#include <stdlib.h> 
#include <time.h> 
#include "Sound.h"
using std::vector;
using std::list;
using std::string;

//-----------------------------------------------
// This class is in charge of all the resources of the game.
// That includes pictures, sounds, musics and font.
class Resources
{
public:
	~Resources(); // D-tor.
	static Resources& instance(); // Singleton.

	// Getters.
	const sf::Texture* getBackground(int i)			const { return &m_bgTextures[i]; }
	const sf::Texture* getTexture(int i)			const { return &m_textures[i]; }
	const sf::Texture* getProjTexture(int i)		const { return &m_projTextures[i]; }
	const sf::Texture* getLSTexture(int i)			const { return &m_lsTextures[i]; }
	const sf::Texture* getSkillText(int i, int j)	const { return &m_skillTextures[i][j]; }
	const sf::Texture* getGameStateText(int i)		const { return &m_gameStates[i]; }
	const sf::Texture* getGameButtonText(int i)		const { return &m_gameButtonsTextures[i]; }
	const sf::Texture* getVolText(int i)			const { return &m_volTextures[i]; }
	const sf::SoundBuffer* getBuffer(int i)			const { return &m_buffers[i]; }
	const sf::Font* getFont()						const { return &m_font; };

private:
	Resources(); // C-tor.
	Resources(const Resources&) = default;
	sf::Texture m_textures[NUM_OF_OBJECTS]; // Stores characters.
	sf::Texture m_skillTextures[NUM_OF_PLAYERS][NUM_OF_SKILLS]; // Stores skills.
	sf::Texture m_bgTextures[NUM_OF_BG]; // Stores backgrounds.
	sf::Texture m_lsTextures[NUM_OF_LS_TEXTS]; // Stores level select textures.
	sf::Texture m_gameStates[NUM_OF_GAME_STATES]; // Stores game states.
	sf::Texture m_gameButtonsTextures[NUM_OF_GBUTTONS]; // Stores in-game buttons.
	sf::Texture m_projTextures[NUM_OF_PROJ]; // Stores the projectiles.
	sf::Texture m_volTextures[NUM_OF_VOL_BUTTONS]; // Stores volume buttons.
	std::vector<sf::SoundBuffer> m_buffers; // Stores sound buffers.
	sf::Font m_font; // Stores the font.
	void loadResources(); // Loads the resources.
};
