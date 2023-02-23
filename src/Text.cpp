#include "../include/Text.h"
#include <SDL2/SDL_surface.h>

Text::Text(std::shared_ptr<TTF_Font> font, SDL_Renderer *renderer,
           const std::string &text)
    : Object(renderer) {
  this->m_font = font;
  this->m_text = text;

  loadText();
}

void Text::loadText() {
  if (!m_font) {
    std::cout << "Cannot load text" << std::endl;
    return;
  }
  SDL_Surface *surface =
      TTF_RenderUTF8_Solid(m_font.get(), m_text.c_str(), m_color);
  if (!surface) {
    std::cout << "Cannot render Text surface" << std::endl;
    return;
  }
  m_texture = std::shared_ptr<SDL_Texture>(
      SDL_CreateTextureFromSurface(this->m_renderer, surface),
      SDL_DestroyTexture);
  if (!m_texture) {
    std::cout << "cannot create texture from surface: " << SDL_GetError()
              << std::endl;
  } else {
    int width, height;
    SDL_QueryTexture(m_texture.get(), nullptr, nullptr, &width, &height);
    m_srcRect.x = 0;
    m_srcRect.y = 0;
    m_srcRect.w = width;
    m_srcRect.h = height;
  }
  SDL_FreeSurface(surface);
}

void Text::setColor(const SDL_Color &color) {
  this->m_color = color;
  loadText();
}
void Text::setText(const std::string &text) {
  m_text = text;
  loadText();
}