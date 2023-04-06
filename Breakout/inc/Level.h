#pragma once

#include "../inc/Brick.h"
#include "../inc/tinyxml2.h"

#include <vector>
#include <unordered_map>

struct ALLEGRO_BITMAP;
struct Brick;

class Level
{
public:
	void init(int hudTopBoundary);
	void update();
	void draw() const;
	std::vector<std::vector<Brick>>& getBricks();
	void loadNextLevel();
	int getCurrentLevel() const;
	int getScoreToWin() const;
private:
	void loadBricks();
	void createLevelLayout(std::string layoutString);
	void allocateLevelLayout(int rowCount, int columnCount);
	void setBrickPositions();

	ALLEGRO_BITMAP* getBrickTexture(const Brick& brick) const;
	ALLEGRO_BITMAP* getSprite(int x, int y, int width, int height, ALLEGRO_BITMAP* spriteSheet);

	ALLEGRO_BITMAP* m_weakBrickSprite;
	ALLEGRO_BITMAP* m_mediumBrickSprites[2]; 
	ALLEGRO_BITMAP* m_hardBrickSprites[3];
	ALLEGRO_BITMAP* m_background;

	std::vector<Brick> m_levelBricks; // holds possible bricks
	std::vector<std::vector<Brick>> m_levelLayout; // holds actual level layout
	std::unordered_map<char, Brick> m_brickIdToBrickType;
	tinyxml2::XMLDocument m_levelInfo;

	int m_currentLevel;
	int m_hudBoundary;
	int m_rowSpacing;
	int m_columnSpacing;
	int m_scoreToWin;

	static const int BRICK_WIDTH = 32;
	static const int BRICK_HEIGHT = 9;
	static const int PADDING_BETWEEN_BRICKS = 7;

};

