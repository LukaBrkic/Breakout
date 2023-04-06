#pragma once

struct ALLEGRO_SAMPLE;
struct ALLEGRO_SAMPLE_INSTANCE;

class Sound
{
public:
	void init();
	void playCannonSound() const;
	void playWinSound() const;
	void playDeathSound() const;
	void playBallHit() const;
private:
	ALLEGRO_SAMPLE* m_cannon;
	ALLEGRO_SAMPLE* m_win;
	ALLEGRO_SAMPLE* m_death;
	ALLEGRO_SAMPLE* m_ballHit;
	ALLEGRO_SAMPLE_INSTANCE* m_instances[4];

};

