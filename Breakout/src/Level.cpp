#include "../inc/Level.h"

#include "../inc/Util.h"
#include "../Constants.h"

#include <allegro5/allegro5.h>

#include <iostream>



void Level::init(int hudBoundary)
{
	m_hudBoundary = hudBoundary;
	loadBricks();
	loadNextLevel();
}

void Level::update()
{
	for (auto& row : m_levelLayout)
	{
		for (auto& brick : row)
		{
			if (!brick.wasHit)
				continue;
			brick.textureIndex++;
			brick.hitPoints--;
			brick.wasHit = false;
		}
	}
}


void Level::draw() const 
{
	al_draw_bitmap(m_background, 0, 0, 0);
	for (const auto& row : m_levelLayout)
	{
		for (const auto& brick : row)
		{
			if (brick.hitPoints == 0)
				continue;
			ALLEGRO_BITMAP* textureToDraw = getBrickTexture(brick);
			al_draw_bitmap(textureToDraw, brick.getX(), brick.getY(), 0);
		}
	}
}

ALLEGRO_BITMAP* Level::getSprite(int x, int y, int width, int height, ALLEGRO_BITMAP* spriteSheet)
{
	ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(spriteSheet, x, y, width, height);
	Util::assertWithMessage(sprite, "Could not create sprite");
	return sprite;
}


void Level::loadBricks()
{
	ALLEGRO_BITMAP* brickSpriteSheet = al_load_bitmap("assets/spritesheets/bricks.png");
	m_weakBrickSprite = getSprite(0, 0, BRICK_WIDTH, BRICK_HEIGHT, brickSpriteSheet);

	m_mediumBrickSprites[0] = getSprite(0, BRICK_HEIGHT + PADDING_BETWEEN_BRICKS, BRICK_WIDTH, BRICK_HEIGHT, brickSpriteSheet);
	m_mediumBrickSprites[1] = getSprite(BRICK_WIDTH, BRICK_HEIGHT + PADDING_BETWEEN_BRICKS, BRICK_WIDTH, BRICK_HEIGHT, brickSpriteSheet);

	m_hardBrickSprites[0] = getSprite(0, BRICK_HEIGHT * 2 + PADDING_BETWEEN_BRICKS * 2, BRICK_WIDTH, BRICK_HEIGHT, brickSpriteSheet);
	m_hardBrickSprites[1] = getSprite(BRICK_WIDTH, BRICK_HEIGHT * 2 + PADDING_BETWEEN_BRICKS * 2, BRICK_WIDTH, BRICK_HEIGHT, brickSpriteSheet);
	m_hardBrickSprites[2] = getSprite(BRICK_WIDTH * 2, BRICK_HEIGHT * 2 + PADDING_BETWEEN_BRICKS * 2, BRICK_WIDTH, BRICK_HEIGHT, brickSpriteSheet);

}

void Level::loadNextLevel()
{
	m_currentLevel++;
	std::string levelPath = "assets/levels/level" + std::to_string(m_currentLevel) + ".xml";
	m_levelInfo.LoadFile(levelPath.c_str());
	tinyxml2::XMLElement* levelElement = m_levelInfo.FirstChildElement("Level");
	int rowCount = levelElement->IntAttribute("RowCount");
	int columnCount = levelElement->IntAttribute("ColumnCount");
	m_rowSpacing = levelElement->IntAttribute("RowSpacing");
	m_columnSpacing = levelElement->IntAttribute("ColumnSpacing");
	std::string backgroundTexturePath = levelElement->Attribute("BackgroundTexture");
	allocateLevelLayout(rowCount, columnCount);
	
	tinyxml2::XMLElement* allBrickTypes = levelElement->FirstChildElement("BrickTypes");
	const auto* brickType = allBrickTypes->FirstChildElement();
	while (brickType != nullptr)
	{
		char brickID = *brickType->Attribute("Id");
		int hitPoints = brickType->IntAttribute("HitPoints");
		int breakScore = brickType->IntAttribute("BreakScore");
		std::string hitSound; // add 
		std::string BreakSound; // add
		m_brickIdToBrickType.emplace(brickID, Brick(brickID, hitPoints, breakScore));
		brickType = brickType->NextSiblingElement();
	}
	tinyxml2::XMLElement* brickLayout = allBrickTypes->NextSiblingElement();
	createLevelLayout(std::move(brickLayout->GetText()));
	setBrickPositions();
	m_background = al_load_bitmap(backgroundTexturePath.c_str());
}

ALLEGRO_BITMAP* Level::getBrickTexture(const Brick& brick) const
{
	switch (brick.brickID)
	{
	case 'S':
		return m_weakBrickSprite;
	case 'M':
		return m_mediumBrickSprites[brick.textureIndex];
	case 'H':
		return m_hardBrickSprites[brick.textureIndex];
	case 'I':
		return nullptr; // add later
	}
	std::cerr << "UNKNOWN BRICK ID" << std::endl;
	exit(1);
}

void Level::createLevelLayout(std::string layoutString)
{
	int row = 0;
	// replace first \n with character that doesn't mess with the rows
	layoutString[0] = ' ';
	for (const char brick : layoutString)
	{
		if (brick == '\n')
			row++;
		else if(m_brickIdToBrickType.find(brick) != m_brickIdToBrickType.end())
		{
			m_levelLayout[row].emplace_back(m_brickIdToBrickType.at(brick));
		}
	}
}

void Level::setBrickPositions()
{
	int paddingY = m_rowSpacing + m_hudBoundary;
	for (auto& row : m_levelLayout)
	{
		int paddingX = m_columnSpacing;
		for (auto& brick : row)
		{
			if (brick.hitPoints == 0)
			{
				paddingX += BRICK_WIDTH + m_columnSpacing;
				continue;
			}
			m_scoreToWin += brick.breakScore;
			brick.setMembers(paddingX, paddingY, BRICK_WIDTH, BRICK_HEIGHT);
			paddingX += BRICK_WIDTH + m_columnSpacing;
		}
		paddingY += BRICK_HEIGHT + m_rowSpacing;
	}
}

void Level::allocateLevelLayout(int rowCount, int columnCount)
{
	m_levelLayout.clear();
	m_levelLayout.reserve(rowCount);
	for (int i = 0; i < rowCount; i++)
	{
		m_levelLayout.emplace_back(std::vector<Brick>{});
		m_levelLayout[i].reserve(columnCount);
	}
}

std::vector<std::vector<Brick>>& Level::getBricks()
{
	return m_levelLayout;
}

int Level::getCurrentLevel() const
{
	return m_currentLevel;
}

int Level::getScoreToWin() const
{
	return m_scoreToWin;
}







