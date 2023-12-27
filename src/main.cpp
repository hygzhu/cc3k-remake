
#include "game.h"
#include <Windows.h>
int main(int argc, char *args[]) {



  AllocConsole();
  freopen("CONOUT$", "w", stdout);


  Game game;
  bool play = true;
  while (play) {
    play = game.start();
  }
  return 0;
}