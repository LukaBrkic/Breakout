#pragma once

#include "../inc/CollidableEntity.h"

struct ALLEGRO_BITMAP;

class Paddle : public CollidableEntity
{
public:
	Paddle();
	void init();
	void draw();
	void update(bool moveLeft, bool moveRight);
	void reset();

private:
	static const int PADDLE_WIDTH = 40;
	static const int PADDLE_HEIGHT = 11;
	static const int PADDLE_SPEED = 4;

	ALLEGRO_BITMAP* m_sprite;
};

