#include "NoThanks.hpp"

NoThanks::NoThanks() {

}


NoThanks::~NoThanks() {

}

void NoThanks::execute(const Action& action) {
  if(action == ACT_NOTHING)  Logger::get().info("Action rien"); 
  if(action == ACT_TAKE_CHIPS)  Logger::get().info("Action Prendre"); 
  if(action == ACT_GIVE_A_CHIP)  Logger::get().info("Action Donner"); 
}


void NoThanks::display() {
  Logger::get().info("display()");
  Logger::get().info("\n");
}

bool NoThanks::gameIsFinished() const {
  return false;
}


void NoThanks::run(){
  Logger::get().info(NOTHX_TITLE);
  
  int currentPlayer = 0;

  PlayerHuman *p = new PlayerHuman();
  Player& player = *p;  

  while(!gameIsFinished()) {
    
    //Player player = player[i]; 
    Action action = player.play();
   
    execute(action);
    Logger::get().info("Affichage...");
    display();
    
    selectNextPlayer();
  }
}


void NoThanks::selectNextPlayer(){
  Logger::get().info("Joueur suivant...");
  currentPlayer++;
  currentPlayer%=NOTHX_NB_PLAYERS_MAX;
}
