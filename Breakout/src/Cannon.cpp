#include "../inc/Cannon.h"
#include "../inc/Sound.h"
#include "../inc/Ball.h"

#include <allegro5/allegro5.h>

#include <iostream>



constexpr int CANNON_SPRITE_WIDTH = 58;
constexpr int CANNON_SPRITE_HEIGHT = 29;

constexpr float PI = 3.14;

Cannon::Cannon():
	m_spriteSheet(nullptr)
{

}

void Cannon::init()
{
	m_spriteSheet = al_load_bitmap("assets/spritesheets/cannonShot.png");
	begin = std::chrono::steady_clock::now();
}

void Cannon::update(const Sound& sound, std::vector<Ball>& balls)
{
	// fire shot every 10 seconds
	if (!m_advancingFrames)
	{
		end = std::chrono::steady_clock::now();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
		if (seconds >= 10)
		{
			m_spawnedBall = false;
			begin = std::chrono::steady_clock::now();
			m_advancingFrames = true;
			delayBegin = std::chrono::steady_clock::now();
		}
	}
	// delay sprite drawing
	else {
		advanceFrameWithDelay();
	}
	if (m_currentFrame == 1)
		sound.playCannonSound();
	else if (m_currentFrame == 4 && !m_spawnedBall)
	{
		balls.emplace_back(Ball{ 1, CANNON_SPRITE_WIDTH - 13, 180 - 40, 1 });
		m_spawnedBall = true;
	}
}

void Cannon::draw()
{
	al_draw_tinted_scaled_rotated_bitmap_region(m_spriteSheet, m_currentFrame * CANNON_SPRITE_WIDTH, 0, CANNON_SPRITE_WIDTH, CANNON_SPRITE_HEIGHT, al_map_rgb(255, 255, 255), 0, 0, -5, 180, 1, 1, (7.0 / 4.0) * PI, 0);
	//for(int i = 0; i < 9; i++)
		//al_draw_bitmap_region(m_spriteSheet, i * CANNON_SPRITE_WIDTH, 0, CANNON_SPRITE_WIDTH, CANNON_SPRITE_HEIGHT, i * CANNON_SPRITE_WIDTH, 190, 0);
	//al_draw_bitmap_region();
}


void Cannon::advanceFrameWithDelay()
{
	delayEnd = std::chrono::steady_clock::now();
	auto milliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(delayEnd - delayBegin).count();
	if (milliSeconds >= 40)
	{
		m_currentFrame++;
		delayBegin = std::chrono::steady_clock::now();
	}
	if (m_currentFrame == 9)
	{
		m_advancingFrames = false;
		m_currentFrame = 0;
	}
}

