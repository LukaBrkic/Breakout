#include "../inc/Sound.h"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>

void Sound::init()
{
	m_cannon = al_load_sample("assets/sounds/cannon.wav");
	m_win = al_load_sample("assets/sounds/win.wav");
	m_death = al_load_sample("assets/sounds/death.wav");
	m_ballHit = al_load_sample("assets/sounds/ballHit.wav");
	m_instances[0] = al_create_sample_instance(m_cannon);
	m_instances[1] = al_create_sample_instance(m_win);
	m_instances[2] = al_create_sample_instance(m_death);
	m_instances[3] = al_create_sample_instance(m_ballHit);
	for (int i = 0; i < 4; i++)
	{
		al_attach_sample_instance_to_mixer(m_instances[i], al_get_default_mixer());
	}
}

void Sound::playCannonSound() const
{
	al_play_sample_instance(m_instances[0]);
	//al_play_sample(m_cannon, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Sound::playWinSound() const
{
	al_play_sample_instance(m_instances[1]);
}

void Sound::playDeathSound() const
{
	al_play_sample_instance(m_instances[2]);
}

void Sound::playBallHit() const
{
	//al_play_sample(m_ballHit, 1.0, 0.0, 0.5, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_play_sample_instance(m_instances[3]);
}
