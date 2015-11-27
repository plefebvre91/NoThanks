#include <iostream>
#include "NoThanks.hpp"


int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  atexit(network::stop);
  
  // Randomize
  srand(time(0));
  // Network
  std::thread networkThread(network::run);
  
  //Initializes board game, tiles and window
  NoThanks* app = new NoThanks();

  //Starts game
  app->run();

  
  networkThread.join();
  
  //Frees memory
  delete app;

  return 0;
}
