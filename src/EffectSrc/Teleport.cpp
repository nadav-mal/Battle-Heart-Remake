#include "Effects/Teleport.h"

#include "Characters/Character.h"

Teleport::Teleport()
{}

void Teleport::affect(Character* self, Character* target, float factor)
{
	sf::Vector2f pos;
	pos.y = (rand() % (WINDOW_HEIGHT - HEIGHT_LIMIT)) + HEIGHT_LIMIT;
	pos.x = rand() % (WINDOW_WIDTH - CUT_CORNERS);
	self->setPosition(pos);
}
