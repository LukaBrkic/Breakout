#pragma once

#include <chrono>
#include <vector>

class Ball;
class Sound;
struct ALLEGRO_BITMAP;

class Cannon
{

public:
	Cannon();
	void init();
	void draw();
	void update(const Sound& sound, std::vector<Ball>& balls);
private:
	void advanceFrameWithDelay();
	ALLEGRO_BITMAP* m_spriteSheet;
	ALLEGRO_BITMAP* m_currentSprite;
	int m_currentFrame;
	bool m_shooting;
	bool m_advancingFrames;
	bool m_spawnedBall;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::time_point delayBegin;
	std::chrono::steady_clock::time_point delayEnd;
};

