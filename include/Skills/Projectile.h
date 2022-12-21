#pragma once
#include "Object.h"
#define RAD2DEG (180.0f / (float)PI)

class Character;

class Projectile : public Object
{
public:
	Projectile(const sf::Vector2f pos, const sf::Vector2f dest , 
			   const int index, std::shared_ptr<Character> target, AnimationParams params);


	virtual bool checkIntersection() const override; // check if the projectile reached the target
	void draw(sf::RenderWindow& window);
	void updateMovement(float deltaTime) override;

private:
	void updateOrientation(); // update angle to destination

	float m_orientation; // direction of the image based on the angle to target
	float m_mvspd; // movement speed of the projectile
};

