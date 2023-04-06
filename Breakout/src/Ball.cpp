#include "../inc/Ball.h"

#include "../Constants.h"
#include "../inc/Util.h"
#include "../inc/Paddle.h"
#include "../inc/Sound.h"

#include <allegro5/allegro5.h>
#include <iostream>

Ball::Ball():
    CollidableEntity(
        (BUFFER_WIDTH / 2) - (BALL_WIDTH / 2), 
        BUFFER_HEIGHT - (BUFFER_HEIGHT / 4), 
        BALL_WIDTH, 
        BALL_HEIGHT),
    m_xDir(Util::randomOneOrMinus()),
    m_yDir(-1),
    m_ballSpeed(2)
{}

Ball::Ball(int xDir, int ballSpeed) :
    Ball()
{
    m_xDir = xDir;
    m_ballSpeed = ballSpeed;
}

Ball::Ball(int xDir, int x, int y, int ballSpeed):
   Ball()
{
    m_xDir = xDir;
    m_x = x;
    m_y = y;
    m_ballSpeed = ballSpeed;
}

    

void Ball::init(int topBoundary)
{
    m_sprite = al_load_bitmap("assets/spritesheets/ball.png");
    m_topBoundary = topBoundary;
}


void Ball::update(std::vector<std::vector<Brick>>& bricks, const Paddle& paddle, bool& lostLife, int& score, const Sound& sound)
{
    for (auto& row : bricks)
    {
        for (auto& brick : row)
        {
            if (brick.hitPoints > 0 && brick.brickID != '_' && this->collidesWith(&brick))
            {
                brick.wasHit = true;
                m_yDir *= -1;
                m_xDir = Util::randomOneOrMinus();
                if (brick.hitPoints == 1)
                    score += brick.breakScore;
                sound.playBallHit();
            }
        }
    }
    if (this->collidesWith(&paddle))
    {

        if (this->getCenter() < paddle.getCenter())
        {
            m_xDir = -1;
        }
        else
            m_xDir = 1;
        m_yDir *= -1;
        sound.playBallHit();
    }
    if ((m_x < 0) || (m_x + BALL_WIDTH > BUFFER_WIDTH))
    {
        m_xDir *= -1;
    }

    if (m_y > BUFFER_HEIGHT) 
    {
        lostLife = true;
        reset();
        return;

    }
    else if (m_y < m_topBoundary)
    {
        m_yDir *= -1;
    }
    m_x += m_ballSpeed * m_xDir;
    m_y += m_ballSpeed * m_yDir;
}


void Ball::draw()
{
    al_draw_bitmap(m_sprite, m_x, m_y, 0);
}

void Ball::reset()
{
    m_x = (BUFFER_WIDTH / 2) - (BALL_WIDTH / 2);
    m_y = BUFFER_HEIGHT - (BUFFER_HEIGHT / 4);
    m_xDir = Util::randomOneOrMinus();
    m_yDir = -1;
}

int Ball::getXDir() const
{
    return m_xDir;
}

