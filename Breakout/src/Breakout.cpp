#include "../inc/Breakout.h"

#include "../inc/Util.h"
#include "../Constants.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include <iostream>


// scale the display for an old school look
constexpr int DISPLAY_SCALE = 2;
constexpr int DISPLAY_WIDTH = BUFFER_WIDTH * DISPLAY_SCALE;
constexpr int DISPLAY_HEIGHT = BUFFER_HEIGHT * DISPLAY_SCALE;

constexpr int FPS = 60;

#define KEY_PRESSED 1
#define KEY_RELEASED 0

Breakout::Breakout() :
	m_lives{TOTAL_LIVES},
	m_lostLife{false},
	m_paused{true},
	m_redraw(true)
{
	init();
	startGame();
}

void Breakout::init()
{	
	Util::assertWithMessage(al_init(), "Failed to initialize allegro");
	Util::assertWithMessage(al_install_keyboard(), "Failed to install keyboard");
	Util::assertWithMessage(al_init_primitives_addon(), "Failed to initialize primitives");
	Util::assertWithMessage(al_init_image_addon(), "Failed to initialize images");
	Util::assertWithMessage(al_install_audio(), "Failed to install audio");
	Util::assertWithMessage(al_init_acodec_addon(), "audio codecs");
	Util::assertWithMessage(al_reserve_samples(4), "reserve samples");

	m_display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	Util::assertWithMessage(m_display, "Failed to create display");
	m_timer = al_create_timer(1.0 / FPS);
	Util::assertWithMessage(m_timer, "Failed to create timer");
	m_eventQueue = al_create_event_queue();
	Util::assertWithMessage(m_eventQueue, "Failed to create event queue");
	m_buffer = al_create_bitmap(BUFFER_WIDTH, BUFFER_HEIGHT);
	Util::assertWithMessage(m_buffer, "Failed to create buffer");

	al_register_event_source(m_eventQueue, al_get_keyboard_event_source());
	al_register_event_source(m_eventQueue, al_get_display_event_source(m_display));
	al_register_event_source(m_eventQueue, al_get_timer_event_source(m_timer));


	m_HUD.init();
	m_paddle.init();
	m_balls.emplace_back(Ball{});
	m_balls[0].init(m_HUD.getHudBoundary());
	m_level.init(m_HUD.getHudBoundary());
	m_sound.init();
}

void Breakout::startGame()
{
	al_start_timer(m_timer);
	while (!m_done)
	{
		al_wait_for_event(m_eventQueue, &m_event);
		processInputs();
		update();
		draw();
	}
}

void Breakout::processInputs()
{
	switch (m_event.type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:
		if (m_event.keyboard.keycode == ALLEGRO_KEY_SPACE)
		{
			m_paused = !m_paused;
			m_HUD.setPauseScreen();
		}
		else
			m_keys[m_event.keyboard.keycode] = KEY_PRESSED;
		break;
	case ALLEGRO_EVENT_KEY_UP:
			m_keys[m_event.keyboard.keycode] = KEY_RELEASED;
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		m_done = true;
		break;
	}
}

void Breakout::update()
{
	if (m_lives == 0 || m_paused)
		return;
	switch (m_event.type)
	{
	// new frame, update world
	case ALLEGRO_EVENT_TIMER:

		m_paddle.update(m_keys[ALLEGRO_KEY_LEFT], m_keys[ALLEGRO_KEY_RIGHT]);
		for (int i = 0; i < m_balls.size(); i++)
		{
			m_balls[i].update(m_level.getBricks(), m_paddle, m_lostLife, m_score, m_sound);
		}
		if(m_level.getCurrentLevel() == 3)
			m_cannon.update(m_sound, m_balls);
		m_level.update();
 		if (m_score >= m_level.getScoreToWin())
		{
			m_sound.playWinSound();
			if (m_level.getCurrentLevel() == NUMBER_OF_LEVELS)
			{
				m_HUD.setVictoryScreen();
				m_paused = true;
			}
			else
			{
				goToNextLevel();
			}
		}
		else if (m_lostLife)
			loseLife();
		m_redraw = true;
		break;
	}
}

void Breakout::draw()
{
	if (m_redraw && al_is_event_queue_empty(m_eventQueue))
	{
		preDraw();
		m_level.draw();
		m_paddle.draw();
		for (int i = 0; i < m_balls.size(); i++)
		{
			m_balls[i].draw();
		}
		if (m_level.getCurrentLevel() == 3)
			m_cannon.draw();
		m_HUD.draw(m_lives, m_score, m_level.getCurrentLevel());
		postDraw();
	}
}

void Breakout::preDraw()
{
	al_set_target_bitmap(m_buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Breakout::postDraw()
{
	al_set_target_backbuffer(m_display);
	al_draw_scaled_bitmap(m_buffer, 0, 0, BUFFER_WIDTH, BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
	al_flip_display();
}

void Breakout::loseLife()
{
	m_lives--;
	if (m_lives == 0) {
		m_HUD.setLossScreen();
		m_sound.playDeathSound();
	}
	m_lostLife = false;
}

void Breakout::goToNextLevel()
{
	m_lives = 3;
	m_paddle.reset();
	m_level.loadNextLevel();
	m_HUD.setPauseScreen();
	m_paused = true;
	if (m_level.getCurrentLevel() == 2)
	{
		m_balls[0].reset();
		// spawn second slower ball moving in opposite direction
		m_balls.emplace_back(Ball{m_balls[0].getXDir() * -1, 1});
	}
	else if (m_level.getCurrentLevel() == 3)
	{
		m_balls[0].reset();
		m_balls.pop_back(); // dodat cleanup
		m_cannon.init();
	}

}

