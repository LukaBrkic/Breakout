#pragma once

#include "CollidableEntity.h"

#include <string>

struct ALLEGRO_BITMAP;

struct Brick : CollidableEntity {
	Brick(char brickID, int hitPoints, int breakScore) :
		brickID{ brickID },
		hitPoints(hitPoints), breakScore(breakScore), 
		textureIndex(0), wasHit(false)
	{}
	char brickID;
	int hitPoints, breakScore;
	int textureIndex;
	bool wasHit;
};