#include "gamestatus.h"
#include "gamewindow.h"

int main() {
  gamestatus::Game game(100, 100, 12);
  game.run();
  return 0;
}