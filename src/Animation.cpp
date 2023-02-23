#include "../include/Animation.h"

void Animation::addFrame(Frame entity)
{
    animation.push_back(std::move(entity));
}

void Animation::setSprite(Sprite *sprite)
{
    this->sprite = sprite;
}

void Animation::play()
{
    if (isPlaying)
        return;
    isPlaying = true;
    time = timeAnimation;
}
void Animation::pause()
{
    isPlaying = false;
}
void Animation::setAnimationLong(const uint32_t delayMs)
{
    timeAnimation = delayMs;
}

void Animation::reset()
{
    pause();
    currentEntity = 0;
    time = 0;
}

void Animation::update(const uint32_t delta)
{
    if (animation.size() == 0 || !sprite || !isPlaying)
    {
        return;
    }
    time += delta;
    if (time >= timeAnimation)
    {
        time = 0;
        Frame frame = animation[currentEntity];
        sprite->setSrcRect(static_cast<int>(frame.width), static_cast<int>(frame.height),
                           static_cast<int>(frame.posX), static_cast<int>(frame.posY));
    }
}
