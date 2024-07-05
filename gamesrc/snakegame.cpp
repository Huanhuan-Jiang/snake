#include "gamedisplay.h"

int main() {
  gamedisplay::Game game;

  if (!game.isInitialized()) {
    std::cerr << "Failed to initialize SDL. Exiting..." << std::endl;
    return 1;
  }

  game.run();

  return 0;
}
