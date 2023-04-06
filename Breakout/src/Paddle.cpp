#include "../inc/Paddle.h"

#include "../Constants.h"

#include <allegro5/allegro5.h>
#include <iostream>
#include <array>

Paddle::Paddle() :
    CollidableEntity{
        (BUFFER_WIDTH / 2) - (PADDLE_WIDTH / 2),
        BUFFER_HEIGHT - PADDLE_HEIGHT,
        PADDLE_WIDTH,
        PADDLE_HEIGHT},
    m_sprite(nullptr)
{}

void Paddle::init() 
{
    m_sprite = al_load_bitmap("assets/spritesheets/paddle.png");
}


void Paddle::update(bool moveLeft, bool moveRight)
{
    if (moveLeft)
    {
        m_x -= PADDLE_SPEED;
    }
    else if (moveRight)
    {
        m_x += PADDLE_SPEED;
    }

    if (m_x < 0) m_x = 0;
    else if (m_x + PADDLE_WIDTH > BUFFER_WIDTH) m_x = BUFFER_WIDTH - PADDLE_WIDTH;
}


void Paddle::draw()
{
    al_draw_bitmap(m_sprite, m_x, m_y, 0);
}

void Paddle::reset()
{
    setMembers((BUFFER_WIDTH / 2) - (PADDLE_WIDTH / 2), BUFFER_HEIGHT - PADDLE_HEIGHT, PADDLE_WIDTH, PADDLE_HEIGHT);
}

