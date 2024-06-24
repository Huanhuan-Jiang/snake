#include "gamestatus.h"
#include "gamewindow.h"

int main() {
  gamewindow::Game game;

    if (!game.isInitialized()) {
    std::cerr << "Failed to initialize SDL. Exiting..." << std::endl;
    return 1;
  }

  while(true) {
    game.handleEvents();
    game.render();
    SDL_Delay(1000);
    }
  return 0;
}