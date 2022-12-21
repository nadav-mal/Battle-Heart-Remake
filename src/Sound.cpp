#include "Sound.h"
#include "Resources.h"

Sound& Sound::instance()
{
	static Sound inst;
	return inst;
}

// Constructor.
Sound::Sound()
{
	/* List of sounds. */
	setSound(Sound::Sounds::BATTLE);
	setSound(Sound::Sounds::BUTTON_CLICK);
	setSound(Sound::Sounds::CLICK_PLAYER);
	setSound(Sound::Sounds::MOVE_PLAYER);
	setSound(Sound::Sounds::HOVER);
	setSound(Sound::Sounds::ARROW);
	setSound(Sound::Sounds::ARROW_RAIN);
	setSound(Sound::Sounds::HEAL);
	setSound(Sound::Sounds::DEF_BUFF);
	setSound(Sound::Sounds::SWORD1);
	setSound(Sound::Sounds::SWORD2);
	setSound(Sound::Sounds::NO_SOUND);

	/* Volume initiation. */
	this->m_volume = DEFAULT_VOLUME;
	this->setVolume();
}

/* Plays the sound once. */
void Sound::playSound(const int place)
{
	if(m_sounds[place].getStatus() != sf::Sound::Playing)
		this->m_sounds[place].play();
}

/* Plays the music in a loop. */
void Sound::playMusic(const std::string fileName)
{
	this->m_music.openFromFile(fileName);
	this->m_music.setLoop(true);
	this->m_music.setVolume(this->m_volume);
	this->m_music.play();
}

/* Stops the music. */
void Sound::stopMusic()
{
	this->m_music.stop();
}

/* Sets a new sound. Must have buffer. */
void Sound::setSound(const Sound::Sounds soundEnum)
{
	sf::Sound tempSound;
	tempSound.setBuffer(*Resources::instance().getBuffer(int(soundEnum)));
	tempSound.setLoop(false);
	this->m_sounds.push_back(tempSound);
}

/* This function is used to set the volume of the sounds and current music. */
void Sound::setVolume()
{
	for (int i = 0; i < this->m_sounds.size(); i++)
		this->m_sounds[i].setVolume(this->m_volume / 2);

	this->m_music.setVolume(this->m_volume);
}

/* Function to increase volume. */
void Sound::incVolume()
{
	if (this->m_volume == 100) return;

	this->m_volume += 10;
	this->setVolume();
}

/* Function to decrease volume. */
void Sound::decVolume()
{
	if (this->m_volume == 0) return;

	this->m_volume -= 10;
	this->setVolume();
}

/* Function to mute and unmute volume. */
void Sound::muteVolume()
{
	/* Already muted. */
	if (this->m_volume == 0)
	{
		this->m_volume = m_prevVolume;
	}
	/* If already muted, unmute. */
	else
	{
		this->m_prevVolume = this->m_volume;
		this->m_volume = 0;
	}

	this->setVolume();
}