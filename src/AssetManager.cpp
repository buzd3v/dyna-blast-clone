#include "../include/manager/AssetManager.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>

void AssetManager::load(SDL_Renderer *renderer) {
  loadFont();
  loadTexture(renderer, Texture::ScoreTable, "sprites/dashboard.png");
  loadTexture(renderer, Texture::TopLeftCorner, "sprites/topleftcorner.png");
  loadTexture(renderer, Texture::TopRightCorner, "sprites/toprightcorner.png");
  loadTexture(renderer, Texture::BottomLeftCorner,
              "sprites/bottomleftcorner.png");
  loadTexture(renderer, Texture::BottomRightCorner,
              "sprites/bottomrightcorner.png");
  loadTexture(renderer, Texture::TopWall, "sprites/topwall.png");
  loadTexture(renderer, Texture::BottomWall, "sprites/bottomwall.png");
  loadTexture(renderer, Texture::LeftWall, "sprites/leftwall.png");
  loadTexture(renderer, Texture::RightWall, "sprites/rightwall.png");

  loadTexture(renderer, Texture::MenuBack, "sprites/start_panel.png");
  loadTexture(renderer, Texture::Stone, "sprites/map/steel.png");
  loadTexture(renderer, Texture::Grass, "sprites/grass.png");
  loadTexture(renderer, Texture::Brick, "sprites/map/brick.png");
  loadTexture(renderer, Texture::Player, "sprites/player/walking@16.png");
  loadTexture(renderer, Texture::Enemy1, "sprites/enemy/ghost@4.png");
  loadTexture(renderer, Texture::Enemy2, "sprites/enemy/drop@4.png");
  loadTexture(renderer, Texture::Enemy3, "sprites/enemy/fire@4.png");
  loadTexture(renderer, Texture::Bomb, "sprites/bomb@4.png");
  loadTexture(renderer, Texture::Explosion, "sprites/bonus_explosion@7.png");
  loadTexture(renderer, Texture::Door, "sprites/exit@2.png");
}

std::shared_ptr<TTF_Font> AssetManager::getFont() const { return font; }

std::shared_ptr<SDL_Texture> AssetManager::getTexture(Texture textured) {
  return textures[textured];
}

void AssetManager::loadFont() {
  font = std::shared_ptr<TTF_Font>(TTF_OpenFont("sprites/font.ttf", 32),
                                   TTF_CloseFont);
  if (!font) {
    std::cout << "TTF open error: " << TTF_GetError() << std::endl;
  }
}

void AssetManager::loadTexture(SDL_Renderer *renderer, Texture texture,
                               const std::string &path) {
  textures[texture] = std::shared_ptr<SDL_Texture>(
      IMG_LoadTexture(renderer, path.c_str()), SDL_DestroyTexture);
  if (!textures[texture]) {
    std::cout << "IMG load texture Error: " << IMG_GetError() << std::endl;
  }
}
