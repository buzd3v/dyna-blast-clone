#pragma once

#include "Object.h"
#include <SDL2/SDL_ttf.h>

class Text : public Object {
public:
  Text(std::shared_ptr<TTF_Font> font, SDL_Renderer *renderer,
       const std::string &text);

  void setText(const std::string &text);

  void setColor(const SDL_Color &color);

private:
  void loadText();

  std::string m_text;                         // text
  std::shared_ptr<TTF_Font> m_font = nullptr; // font
  SDL_Color m_color = {255, 255, 255, 255};   // black color for text
};
