#include "NoThanks.hpp"

NoThanks::NoThanks() {

}


NoThanks::~NoThanks() {

}

void NoThanks::execute(const Action& action, Player& player) {
  
  if(!player.hasChips() || action == ACT_TAKE_CHIPS) {
    if(!player.hasChips())  Logger::get().info("Plus aucun jeton"); 

    player.take(chipsOnTable,cardOnTop);
    Logger::get().info("Action Prendre carte et jetons"); 

    chipsOnTable = 0;
  }
  
  else if(action == ACT_NOTHING)  {
    Logger::get().info("Action rien"); 
  }

  else if(action == ACT_GIVE_A_CHIP) {
    Logger::get().info("Action Donner"); 
    player.drop();
    ++chipsOnTable;
  }

}


void NoThanks::display() {
  std::cout << "Il y a " << chipsOnTable << " jetons sur la table\n";
  std::cout << "La carte posee est " << cardOnTop << std::endl;
 
}

bool NoThanks::gameIsFinished() const {
  return false;
}


void NoThanks::run(){
  Logger::get().info(NOTHX_TITLE);
  
  int currentPlayer = 0;

  PlayerHuman *p = new PlayerHuman();
  Player& player = *p;  
  player.setName("Bob");
  while(!gameIsFinished()) {
    
    //Player player = player[i]; 
    Action action = player.hasChips()? player.play() : ACT_TAKE_CHIPS;
    
    execute(action, player);
    player.info();

    display();
    
    selectNextPlayer();
  }
}


void NoThanks::selectNextPlayer(){
  Logger::get().info("Joueur suivant...");
  currentPlayer++;
  currentPlayer%=NOTHX_NB_PLAYERS_MAX;
}
