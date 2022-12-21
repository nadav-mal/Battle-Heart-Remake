#pragma once
#include <SFML/Graphics.hpp>
#include "macros.h"
// Animation class is in charge of the graphic animations in the game.
class Animation
{
public:
	Animation(const sf::Texture* texture, AnimationParams animParams); // C-tor.

	// Special c-tor for sprite sheets with different row lengths.
	Animation(const sf::Texture* texture, AnimationParams animParams , std::vector<int> lengths ); 
	~Animation() = default; // D-tor.

	// Animation management.
	bool update(float deltaTime);
	sf::IntRect& getUVRect() { return this->uvRect; }

	// Setters
	void setRow(int index);
	void setFaceRight(bool faceRight) { this->m_faceRight = faceRight; }

	// Getters
	bool getFaceRight()	const { return this->m_faceRight; }

private:
	sf::IntRect uvRect; // The rectangle of the currently displayed sprite.
	sf::Vector2f m_imageCount; // number of images in each row
	sf::Vector2f m_currentImage; // current image in sprite sheet
	std::vector<int> m_rowLens; // vector of lengths , used when length of rows isn't consistant
	float m_totalTime;
	float m_switchTime;
	unsigned int m_row; // current row
	bool m_faceRight; // is facing right ( or left)
};