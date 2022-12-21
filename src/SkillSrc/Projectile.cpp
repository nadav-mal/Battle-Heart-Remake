
#include "Skills/Projectile.h"
#include "Characters/Character.h"

Projectile::Projectile(const sf::Vector2f pos, const sf::Vector2f dest, 
					   const int index, std::shared_ptr<Character> target,
					   AnimationParams params)
	:	Object(pos, index, params, ProjRowlengths[index], 
			   Resources::instance().getProjTexture(index)), m_mvspd(DEF_MVSPD)
{
	setAsTarget(target);
	setAnimation(0);
	setDestination(dest);
	this->setOffset(projectileOffset);
	this->updateOrientation();
	this->setRotation(this->m_orientation);
}

//==============================================================================

bool Projectile::checkIntersection() const
{
	auto pos = this->getPosition();
	auto dest = this->getDest();
	auto norm = sqrt(pow((pos.x - dest.x), 2) + pow((pos.y - dest.y), 2));
	auto epsilon = 10.f;
	return norm <= epsilon || this->getTarget()->checkCollision(this->getPosition());
}

//==============================================================================

void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
}

//==============================================================================

void Projectile::updateMovement(float deltaTime)
{
	this->setDestination(this->getTarget()->getPosition());

	auto dir = this->getDest() - this->getPosition();
	auto movement = m_mvspd * dir * deltaTime;
	this->setPosition(this->getPosition()+ m_mvspd * dir * deltaTime);
	this->handleAnimation(movement, deltaTime);

}

//==============================================================================
// this func calculates the orientation needed to rotate the projectile to the
// right angle (facing the target)

void Projectile::updateOrientation()
{
	auto adj = this->getPosition().x - this->getTarget()->getPosition().x;
	auto opp = this->getTarget()->getPosition().y - this->getPosition().y;

	if (opp == 0) opp++;
	if (adj == 0) adj++;
	this->m_orientation = (float)(atan(adj / opp) * RAD2DEG);

	if (opp > 0)
		this->m_orientation += 90;
	else
		this->m_orientation -= 90;

	if (adj > 0)
	{
		this->m_orientation += 180;
		this->setFaceRight(false);
	}
}

//==============================================================================

