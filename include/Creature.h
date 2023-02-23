#pragma once
#include "Sprite.h"

class Creature : public Sprite
{
private:
    /* data */
public:
    Creature(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer) : Sprite(texture, renderer){};
    void revertLastMove();
    void setMove(bool isMove);
    bool isMoving();

protected:
    int preDeltaX;
    int preDeltaY;

private:
    bool moving = false;
};
