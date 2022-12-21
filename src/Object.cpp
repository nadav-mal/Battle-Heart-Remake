#include "Object.h"

Object::Object(const sf::Vector2f pos, const int index, AnimationParams animParams, 
			   std::vector<int> rowLens ,const sf::Texture* texture)
	: m_animation(texture, animParams , rowLens),
	  m_isMoving(false), m_dest(pos), m_target(nullptr)
{
	this->initSprite(pos, index , texture); 
}

//=======================================================================================
// move and handle animations of the object
bool Object::handleAnimation(sf::Vector2f movement, float deltaTime)
{
	// If facing right.
	if (this->getPosition().x < this->getDest().x)
		this->m_animation.setFaceRight(true);

	else if (this->getPosition().x > this->getDest().x)
		this->m_animation.setFaceRight(false);

	auto res = this->m_animation.update(deltaTime);
	this->m_sprite.setTextureRect(this->m_animation.getUVRect());

	return res;
}

//=======================================================================================
// insure that the location is inside the borders of the game
sf::Vector2f Object::adjustLocation(sf::Vector2f location)
{
	auto newLoc = sf::Vector2f();
	newLoc.x = std::min(location.x, float(WINDOW_WIDTH - CUT_CORNERS));
	newLoc.y = std::min(location.y, float(WINDOW_HEIGHT - 1.5f * CUT_CORNERS));

	newLoc.x = std::max(newLoc.x, float(CUT_CORNERS));
	newLoc.y = std::max(newLoc.y, float(HEIGHT_LIMIT));

	return newLoc;
}

//=======================================================================================
// initiate sprite texture and visuals
void Object::initSprite(const sf::Vector2f pos, const int index ,const sf::Texture* texture)
{
	this->m_sprite.setPosition(pos);
	this->m_sprite.setTexture(*texture);
	auto size = m_sprite.getTextureRect();
	this->m_sprite.setScale(SCALE);
	this->m_sprite.setOrigin( SPRITE_SIZE/ 2.f , SPRITE_SIZE * 1.1f);
}

//=======================================================================================

// check if the sprite is clicked
bool Object::checkCollision(const sf::Vector2f& location) {
	return this->m_sprite.getGlobalBounds().contains(location);
}

//=======================================================================================