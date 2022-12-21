#pragma once

#include "Animation.h"
#include "Resources.h"
#include "SteeringInterface.h"
class SteeringInterface;
class Character;

// This class is in charge of the objects in the game.
class Object
{
public:
	// C-tor and d-tor.
	Object(const sf::Vector2f pos, const int index, AnimationParams animParams, std::vector<int> rowLens,const sf::Texture* texture);
	virtual ~Object() = default;

	// Management.
	bool handleAnimation(sf::Vector2f movement, float deltaTime);

	// Virtuals.
	virtual bool checkIntersection() const = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void updateMovement(float deltaTime) = 0;

	// Getters.
	bool			getIsMoving()			const { return this->m_isMoving; }
	Character*		getTarget()				const { return this->m_target.get(); }
	sf::Vector2f	getDest()				const { return this->m_dest; }
	sf::Sprite		getSprite()				const { return this->m_sprite; }
	sf::Vector2f	getPosition()			const { return this->m_sprite.getPosition(); }
	
	// Setters.
	void setFaceRight(bool faceRight) { this->m_animation.setFaceRight(faceRight); }
	void setDestination(sf::Vector2f dest) { this->m_dest = adjustLocation(dest); }
	void setMoving(bool movement) { this->m_isMoving = movement; }
	void setPosition(sf::Vector2f pos) { this->m_sprite.setPosition(pos); }
	void setAsTarget(std::shared_ptr<Character> obj) { this->m_target = obj; }
	void setAnimation(int index) { this->m_animation.setRow(index); }
	void setRotation(float angle) { this->m_sprite.setRotation(angle); }

	// Checks/validators.
	bool checkCollision(const sf::Vector2f& location);
	sf::Vector2f adjustLocation(sf::Vector2f location);

protected:
	// Protected setters.
	void setColor(sf::Color color)				{ m_sprite.setColor(color); }
	void setScale(sf::Vector2f scale)			{ m_sprite.setScale(scale); }
	void setOffset(sf::Vector2f originOffest)	{ m_sprite.setOrigin(m_sprite.getOrigin() + originOffest); }

private:
	// Inits sprite settings.
	void initSprite(const sf::Vector2f pos, const int index , const sf::Texture* texture);
	sf::Sprite m_sprite;
	std::shared_ptr<Character> m_target; // Stores the target of the object.

	// For animation and movement.
	Animation m_animation;
	bool m_isMoving;
	sf::Vector2f m_dest;
};