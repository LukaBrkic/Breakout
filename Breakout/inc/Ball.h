#pragma once

#include "../inc/Brick.h"
#include "CollidableEntity.h"
#include "Paddle.h"

#include <vector>

class Sound;
struct ALLEGRO_BITMAP;


class Ball : public CollidableEntity
{
public:
	Ball();
	Ball(int xDir, int ballSpeed);
	Ball(int xDir, int x, int y, int ballSpeed);
	void init(int topBoundary);
	void draw();
	void update(std::vector<std::vector<Brick>>& bricks, const Paddle& paddle, bool& lostLife, int& score, const Sound& sound);
	void reset();
	int getXDir() const;
private:

	int m_yDir;
	int m_xDir;
	int m_ballSpeed;

	static const int BALL_WIDTH = 8;
	static const int BALL_HEIGHT = 8;

	inline static ALLEGRO_BITMAP* m_sprite;
	inline static int m_topBoundary;
};

