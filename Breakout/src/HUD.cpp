#include "../inc/HUD.h"
#include "../inc/Util.h"
#include "../Constants.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

HUD::HUD():
	m_paused{ true }
{

}

void HUD::init()
{
	m_emptyLifeSprite = al_load_bitmap("assets/spritesheets/emptyHeart.png");
	m_fullLifeSprite = al_load_bitmap("assets/spritesheets/fullHeart.png");
	m_font = al_create_builtin_font();
	Util::assertWithMessage(m_font, "FAILED TO LOAD FONT");
	m_livesLeftText = "LIVES LEFT: ";
	m_scoreText = "SCORE: ";
	m_levelText = "LEVEL: ";

	m_livesLeftTextWidth = al_get_text_width(m_font, m_livesLeftText.c_str()) - LEFT_SPACING_OFFSET;
	m_scoreTextWidth = al_get_text_width(m_font, m_scoreText.c_str()) - LEFT_SPACING_OFFSET;
	m_levelTextWidth = al_get_text_width(m_font, m_levelText.c_str()) - LEFT_SPACING_OFFSET;
	
	m_scoreTextOffset = m_livesLeftTextWidth + (HEART_SPACING * TOTAL_LIVES) + LEFT_SPACING_OFFSET;
	m_levelTextOffset = m_scoreTextOffset + m_scoreTextWidth + al_get_text_width(m_font, "999") + LEFT_SPACING_OFFSET;

	m_whiteColor = al_map_rgb(255, 255, 255);
	m_hudTopBoundary = al_get_font_line_height(m_font) + TOP_SPACING_OFFSET + 3;
}

void HUD::update() 
{

}

void HUD::draw(int livesLeft, int score, int currentLevel) const
{

	// "Lives: "
	al_draw_text(m_font, m_whiteColor, 0, TOP_SPACING_OFFSET, 0, m_livesLeftText.c_str());
	// [0,3]
	drawLives(livesLeft);
	// "Score: "
	al_draw_text(m_font, m_whiteColor, m_scoreTextOffset, TOP_SPACING_OFFSET, 0, m_scoreText.c_str());
	// [0, 999]
	al_draw_text(m_font, m_whiteColor, m_scoreTextOffset + m_scoreTextWidth, TOP_SPACING_OFFSET, 0, std::to_string(score).c_str());
	// "Level: "
	al_draw_text(m_font, m_whiteColor, m_levelTextOffset, TOP_SPACING_OFFSET, 0, m_levelText.c_str());
	// [0,3]
	al_draw_text(m_font, m_whiteColor, m_levelTextOffset + m_levelTextWidth, TOP_SPACING_OFFSET, 0, std::to_string(currentLevel).c_str());
	// hud boundary
	al_draw_line(0, m_hudTopBoundary, BUFFER_WIDTH, al_get_font_line_height(m_font) + TOP_SPACING_OFFSET + 3, m_whiteColor, 1);
	if (m_victory)
	{
		al_draw_text(m_font, m_whiteColor, BUFFER_WIDTH / 2 - al_get_text_width(m_font, "CONGRATULATIONS, YOU WIN!") / 2, BUFFER_HEIGHT / 2, 0, "CONGRATULATIONS, YOU WIN!");
	}
	else if (m_loss)
	{
		al_draw_text(m_font, m_whiteColor, BUFFER_WIDTH / 2 - al_get_text_width(m_font, "GAME OVER") / 2, BUFFER_HEIGHT / 2, 0, "GAME OVER");
	}
	else if (m_paused)
	{
		al_draw_text(m_font, m_whiteColor, BUFFER_WIDTH / 2 - al_get_text_width(m_font, "GAME PAUSED") / 2, BUFFER_HEIGHT / 2, 0, "GAME PAUSED");
		al_draw_text(m_font, m_whiteColor, BUFFER_WIDTH / 2 - al_get_text_width(m_font, "PRESS SPACE TO UNPAUSE") / 2, BUFFER_HEIGHT / 2 + 20, 0, "PRESS SPACE TO UNPAUSE");
	}
	
}

void HUD::setPauseScreen() 
{
	m_paused = !m_paused;
}

void HUD::setLossScreen()
{
	m_loss = true;
}

void HUD::setVictoryScreen()
{
	m_victory = true;
}

int HUD::getHudBoundary() const
{
	return m_hudTopBoundary;
}


void HUD::drawLives(int livesLeft) const
{
	int i = 1;
	// draw remaining lives
	for (; i <= livesLeft; i++)
	{
		al_draw_bitmap(m_fullLifeSprite, m_livesLeftTextWidth + HEART_SPACING * (i - 1), TOP_SPACING_OFFSET_HEARTS, 0);
	}
	// draw empty lives
	for (; i <= TOTAL_LIVES; i++)
	{
		al_draw_bitmap(m_emptyLifeSprite, m_livesLeftTextWidth + HEART_SPACING * (i - 1), TOP_SPACING_OFFSET_HEARTS, 0);
	}
}



