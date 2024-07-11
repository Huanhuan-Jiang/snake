#include "gamedisplay.h"

int main() {
  gamedisplay::Game game;

  if (!game.isInitialized()) {
    throw std::runtime_error(SDL_GetError());
    return 1;
  }

  game.run();

  return 0;
}
