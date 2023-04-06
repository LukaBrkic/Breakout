#include "../inc/CollidableEntity.h"

#include <iostream>

int m_x, m_y, m_width, m_height;

bool CollidableEntity::collidesWith(const CollidableEntity* entity) const {
	if ((m_x <= (entity->m_x + entity->m_width)) && // r1 left edge is to the right of the right edge of r2
		((m_x + m_width) >= entity->m_x) && // r1 right edge is to the left of r2 left edge
		(m_y <= (entity->m_y + entity->m_height)) &&
		(m_y + m_height >= entity->m_y))
	{
		return true;
	}
	return false;
}

void CollidableEntity::setMembers(int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

int CollidableEntity::getX() const
{
	return m_x;
}
int CollidableEntity::getY() const
{
	return m_y;
}

int CollidableEntity::getCenter() const
{
	return m_x + (m_width / 2);
}


