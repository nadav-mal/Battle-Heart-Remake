#pragma once
#include "macros.h"
class Enemy;

// This class is in charge of the steering in the game.
// Steering exists in "Object" objects, which means every object steers.
class SteeringInterface
{
public:
	// C-tor and d-tor.
	SteeringInterface();
	~SteeringInterface();

	// Arrives at a destination.
	sf::Vector2f Arrive(std::vector<sf::Vector2f> locations, 
						std::vector<float> values , float r);

	// Arrives while avoiding collision.
	sf::Vector2f CollisionAvoidance(std::vector<sf::Vector2f> locations,
									std::vector<sf::Vector2f> obstacles, 
									std::vector<float> values, float MAX_AVOID_FORCE);

	// Management and vector calculations.
	float distance(sf::Vector2f start, sf::Vector2f end);
	float length(sf::Vector2f vec);
	sf::Vector2f Normalize(sf::Vector2f vec);
	sf::Vector2f Truncate(const sf::Vector2f& vec, float max);
};