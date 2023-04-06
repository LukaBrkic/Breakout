#pragma once

#include <string>
#include <allegro5/color.h>

struct ALLEGRO_FONT;
struct ALLEGRO_BITMAP;
struct ALLEGRO_COLOR;

class HUD
{
public:
	HUD();
	void init();
	void update();
	void draw(int livesLeft, int score, int currentLevel) const;
	void setPauseScreen();
	void setLossScreen();
	void setVictoryScreen();
	int getHudBoundary() const;
private:
	void drawLives(int livesLeft) const;

	ALLEGRO_FONT* m_font;
	ALLEGRO_BITMAP* m_fullLifeSprite;
	ALLEGRO_BITMAP* m_emptyLifeSprite;
	ALLEGRO_COLOR m_whiteColor;

	std::string m_livesLeftText;
	std::string m_scoreText;
	std::string m_levelText;

	int m_livesLeftTextWidth;
	int m_scoreTextWidth;
	int m_levelTextWidth;
	int m_scoreTextOffset;
	int m_levelTextOffset;
	int m_hudTopBoundary;

	bool m_paused;
	bool m_loss;
	bool m_victory;

	static const int HEART_WIDTH = 11;
	static const int HEART_HEIGHT = 10;
	static const int HEART_SPACING = HEART_WIDTH + 3;
	static const int LEFT_SPACING_OFFSET = 5;
	static const int TOP_SPACING_OFFSET = 6;
	static const int TOP_SPACING_OFFSET_HEARTS = 3;
};

