#include "../include/Object.h"

Object::Object(SDL_Renderer *renderer) { this->m_renderer = renderer; }

Object::~Object() {}

void Object::setSize(const int width, const int height) {
  m_desRect.w = width;
  m_desRect.h = height;
}

void Object::setPosition(const int x, const int y) {
  m_desRect.x = x;
  m_desRect.y = y;
}

void Object::setSrcRect(const int width, const int height, const int x,
                        const int y) {
  this->m_srcRect.x = x;
  this->m_srcRect.y = y;
  this->m_srcRect.w = width;
  this->m_srcRect.h = height;
}

void Object::attachToCamera(bool isAttach) {
  this->isAttachToCamera = isAttach;
}

int Object::getWidth() const { return this->m_desRect.w; }

int Object::getHeight() const { return this->m_desRect.h; }

int Object::getPositionX() const { return this->m_desRect.x; }
int Object::getPositionY() const { return this->m_desRect.y; }
const SDL_Rect &Object::getRect() const { return this->m_desRect; }
void Object::setFlip(SDL_RendererFlip flip) { this->m_flip = flip; }

void Object::update(const uint32_t delta) {}

void Object::draw(const SDL_Rect &camrera) {
  if (m_renderer != nullptr && m_texture != nullptr) {
    SDL_Rect temp = m_desRect;
    if (isAttachToCamera) {
      temp.x -= camrera.x;
      temp.y -= camrera.y;
    }

    SDL_RenderCopyEx(m_renderer, m_texture.get(), &m_srcRect, &m_desRect, 0,
                     nullptr, m_flip);
  } else {
    std::cout << "null texture" << std::endl;
  }
}
