#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

class Object
{
    /**
     *@brief class for all object likes enemy, player, text, ...
     */
public:
    Object(SDL_Renderer *renderer);

    virtual ~Object();

    // set the size of object
    void setSize(const int width, const int height);

    // set the position of object
    void setPosition(const int x, const int y);

    // set the srcRect a.k.a the clip part off texture
    void setSrcRect(const int width, const int height, const int x, const int y);

    // attach object to the camera
    void attachToCamera(bool isAttach = true);

    int getWidth() const;

    int getHeight() const;

    int getPositionX() const;

    int getPositionY() const;

    const SDL_Rect &getRect() const;

    void setFlip(SDL_RendererFlip flip);

    virtual void update(const uint32_t delta);

    void draw(const SDL_Rect &camrera);

protected:
    SDL_Renderer *m_renderer;
    SDL_Rect m_desRect; // rect on screen
    SDL_Rect m_srcRect; // which part of texture to display

    SDL_RendererFlip m_flip = SDL_FLIP_NONE; // if the texture flip horizontal or vertical

    std::shared_ptr<SDL_Texture> m_texture = nullptr;

private:
    bool isAttachToCamera = true;
};