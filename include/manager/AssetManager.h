#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "../Texture.h"
#include <cstddef>
#include <memory.h>
#include <memory>
#include <string>
#include <unordered_map>

class AssetManager {

public:
  void load(SDL_Renderer *renderer);
  std::shared_ptr<TTF_Font> getFont() const;
  std::shared_ptr<SDL_Texture> getTexture(Texture texture);

private:
  void loadFont();
  void loadTexture(SDL_Renderer *renderer, Texture texture,
                   const std::string &path);
  std::shared_ptr<TTF_Font> font = nullptr; // font
  std::unordered_map<Texture, std::shared_ptr<SDL_Texture>, EnumHash>
      textures; // map of textures
};