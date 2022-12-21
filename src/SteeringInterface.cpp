#include "SteeringInterface.h"
#include "Characters/Enemy.h"
SteeringInterface::SteeringInterface()
{}

SteeringInterface::~SteeringInterface(){}

//====================================================================================================
float SteeringInterface::distance(sf::Vector2f start, sf::Vector2f end)
{
	sf::Vector2f v = start - end;
	return length(v);
}

//====================================================================================================
float SteeringInterface::length(sf::Vector2f vec)
{
	auto Rx = vec.x;
	auto Ry = vec.y;
	return std::sqrt(Rx * Rx + Ry * Ry);
}

//====================================================================================================
sf::Vector2f SteeringInterface::Normalize(sf::Vector2f vec)
{
	float l = length(vec);
	if (l > 0.0f)
		return sf::Vector2f(vec.x / l, vec.y / l);
	else
		return sf::Vector2f(0, 0);
}
//====================================================================================================

sf::Vector2f SteeringInterface::Truncate(const sf::Vector2f& vec, float max)
{
	sf::Vector2f truncated = sf::Vector2f(vec.x, vec.y);
	if (length(vec) > max)
		truncated = Normalize(truncated) * max;

	return truncated;
}

//====================================================================================================

sf::Vector2f SteeringInterface::Arrive(std::vector<sf::Vector2f> vectors, std::vector<float> values, float r)
{
	auto desiredV = vectors[_target] - vectors[_object];
	auto steeringForce = desiredV - vectors[_velocity];
	auto dist = desiredV;

	if (length(dist) >= r) 
	{
		steeringForce /= values[_maxVelocity];
		steeringForce *= values[_maxForce];
	}

	return steeringForce;
}

//====================================================================================================

sf::Vector2f SteeringInterface::CollisionAvoidance(std::vector<sf::Vector2f> vectors,
												   std::vector<sf::Vector2f> obstacles, std::vector<float> values, float MAX_AVOID_FORCE)
{

	float v = length(vectors[_velocity]) / (values[_maxVelocity]);
	sf::Vector2f ahead = vectors[_object] + vectors[_velocity] * v;
	sf::Vector2f halfahead = vectors[_object] + vectors[_velocity] * 0.5f * v;
	std::vector <sf::Vector2f> distances, subdistances, avoidForce;

	for (int i = 0; i < obstacles.size(); i++) {

		sf::Vector2f d = ahead - obstacles[i];
		distances.push_back(d);
		sf::Vector2f subD = halfahead - obstacles[i];
		subdistances.push_back(subD);
		sf::Vector2f af;
		af = ahead - obstacles[i];
		af = Normalize(af) * MAX_AVOID_FORCE;
		avoidForce.push_back(af);
	}

	for (int i = 0; i < obstacles.size(); i++) {

		if (length(distances[i]) <= 50 || length(subdistances[i]) <= 50 || distance(vectors[_object], obstacles[i]) <= 50)
		{//50 = radius of sphere


			sf::Vector2f desiredV = vectors[_target] - vectors[_object];
			desiredV = Normalize(desiredV);
			desiredV *= values[_maxVelocity];
			sf::Vector2f steeringForce = desiredV - vectors[_velocity];
			steeringForce /= values[_maxVelocity];
			steeringForce *= values[_maxForce];
			distances.clear();
			subdistances.clear();
			return steeringForce + avoidForce[i];
		}
		else 
		{

			sf::Vector2f desiredV = vectors[_target] - vectors[_object];
			desiredV = Normalize(desiredV);
			desiredV *= values[_maxVelocity];
			sf::Vector2f steeringForce = desiredV - vectors[_velocity];
			steeringForce /= values[_maxVelocity];
			steeringForce *= values[_maxForce];
			return steeringForce;
		}
	}
	return { 0,0 };
}

