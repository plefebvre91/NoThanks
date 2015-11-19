#include "NoThanks.hpp"

NoThanks::NoThanks():deck() {

}


NoThanks::~NoThanks() {

}
void NoThanks::execute() {
  Logger::get().info("execute()");
}


void NoThanks::display() {
  Logger::get().info("display()");
  Logger::get().info("\n");
}

bool NoThanks::gameIsFinished() const {
  return false;
}


void NoThanks::run(){
  Logger::get().info("Démarrage");
  std::cout << "No Thanks!" << std::endl;
  
  int currentPlayer = 0;

  while(!gameIsFinished() && currentPlayer < 5) {
    
    //Player player = player[i]; 
    Logger::get().info("Recuperation de l'action du joueur suivant");
    //Action action = player.play();
    Logger::get().info("Execution de l'action");
    execute();
    Logger::get().info("Affichage...");
    display();
    Logger::get().info("Selection du joueur suivant");

    ++currentPlayer;
    //    currentPlayer %=3;
  }
}

