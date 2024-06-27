#include "gamestatus.h"
#include "gamewindow.h"

int main() {
  gamewindow::Game game;

  if (!game.isInitialized()) {
    std::cerr << "Failed to initialize SDL. Exiting..." << std::endl;
    return 1;
  }

  if(game.isInitialized()) {std::cout << "Game is initialized!" << ". \n";}

  game.run();

  return 0;
}