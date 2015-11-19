#include <iostream>
#include "NoThanks.hpp"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  
  // Randomize
  srand(time(0));

  //Initializes board game, tiles and window
  NoThanks* app = new NoThanks();

  //Starts game
  app->run();

  //Frees memory
  delete app;

  return 0;
}
