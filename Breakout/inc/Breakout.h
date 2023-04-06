#pragma once

#include "../inc/Paddle.h"
#include "../inc/Ball.h"
#include "../inc/HUD.h"
#include "../inc/Level.h"
#include "../inc/Sound.h"
#include "../inc/Cannon.h"

#include <array>
#include <allegro5/allegro5.h>

class Breakout
{
public:
	Breakout();
private:
	void init();
	void startGame();
	void preDraw();
	void processInputs();
	void update();
	void draw();
	void postDraw();
	void loseLife();
	void goToNextLevel();

	std::vector<Ball> m_balls;
	Paddle m_paddle;
	HUD m_HUD;
	Level m_level;
	Sound m_sound;
	Cannon m_cannon;
	
	std::array<int, ALLEGRO_KEY_MAX> m_keys;

	bool m_done;
	bool m_redraw;
	bool m_lostLife;
	bool m_paused;

	int m_lives;
	int m_score;

	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_BITMAP* m_buffer;
	ALLEGRO_TIMER* m_timer;
	ALLEGRO_EVENT m_event;
	ALLEGRO_EVENT_QUEUE* m_eventQueue;
};

