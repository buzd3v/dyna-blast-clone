#include "../include/Game.h"
#include "../include/MenuScene.h"
#include "../include/Object.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

Game::Game(const std::string &title, const int width, const int height)
    : windowWidth(width), windowHeight(height) {
  // init SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "Init SDL failed: " << SDL_GetError() << std::endl;
  }
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cout << "Init IMG failed: " << IMG_GetError() << std::endl;
  }
  if ((TTF_Init() != 0)) {
    std::cout << "TTF engine loaded fail" << TTF_GetError() << std::endl;
  }

  g_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
  if (!g_window) {
    std::cout << "Init Window failed: " << SDL_GetError() << std::endl;
  }
  g_renderer = SDL_CreateRenderer(
      g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (g_renderer == nullptr) {

    std::cout << "renderer init failed: " << SDL_GetError() << std::endl;
  }
  int w, h;
  SDL_GetRendererOutputSize(g_renderer, &w, &h);
  windowWidth = w;
  windowHeight = h;
  assetManager = std::make_shared<AssetManager>();
  sceneManager = std::make_shared<SceneManager>();
}

Game::~Game() {

  SDL_DestroyWindow(g_window);
  SDL_DestroyRenderer(g_renderer);

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Game::run() {
  if (isRunning) {
    return;
  }

  isRunning = true;

  assetManager->load(g_renderer);

  sceneManager->addScene("menu", std::make_shared<MenuScene>(this)); // menu
  sceneManager->activeScene("menu");

  SDL_Event event;

  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      sceneManager->onEvent(event);

      if (event.type == SDL_QUIT) {
        stop();
      }
    }
    // update something
    Uint32 tick = SDL_GetTicks();
    Uint32 delta = tick - lastTime;
    lastTime = tick;

    sceneManager->update(delta);
    // clear screen
    SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(g_renderer);

    // draw something
    sceneManager->draw();

    //
    SDL_RenderPresent(g_renderer);
  }
}
void Game::stop() { isRunning = false; }

SDL_Renderer *Game::getGlobalRenderer() { return this->g_renderer; }

int Game::getWindowHeight() const { return windowHeight; }

int Game::getWindowWidth() const { return windowWidth; }
