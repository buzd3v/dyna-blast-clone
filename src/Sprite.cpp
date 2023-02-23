#include "../include/Sprite.h"

Sprite::Sprite(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer) : Object(renderer)
{
    this->m_texture = texture;

    int w, h;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);

    m_srcRect.x = 0;
    m_srcRect.y = 0;
    m_srcRect.w = w;
    m_srcRect.h = h;

    m_desRect.x = 0;
    m_desRect.y = 0;
    m_desRect.w = w;
    m_desRect.h = h;
}

void Sprite::update(const uint32_t delta)
{
    for (auto ani : animations)
    {
        ani->update(delta);
    }
}

void Sprite::addAnimation(std::shared_ptr<Animation> animation)
{
    animations.push_back(std::move(animation)); // notice
}
