#pragma once
class CollidableEntity
{
public:
	CollidableEntity(){}
	CollidableEntity(int x, int y, int width, int height):
		m_x(x), m_y(y), 
		m_width(width), m_height(height)
		{}
	virtual bool collidesWith(const CollidableEntity* entity) const;
	void setMembers(int x, int y, int width, int height);
	int getX() const;
	int getY() const;
	int getCenter() const;
protected:
	int m_x, m_y, m_width, m_height;
};

