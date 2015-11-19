#include "NoThanks.hpp"

NoThanks::NoThanks(): cardOnTop(), deck(){
  srand(time(0));
}


NoThanks::~NoThanks() {

}

void NoThanks::execute(const Action& action, Player& player) {
  
  // prendre les jetons sur la table
  if(action == ACT_TAKE_CHIPS) {
    // Preciser si on a pas le choix
    if(!player.hasChips())  Logger::get().info("Plus aucun jeton"); 

    Logger::get().info("Action Prendre carte et jetons"); 
    // prendre jetons et carte
    player.take(chipsOnTable,cardOnTop.getValue());
    // Enlever les jetons sur la table
    chipsOnTable = 0;
    
    // tirer une nouvelle carte si possible
    cardOnTop = deck.getNext();
  }
  
  else if(action == ACT_GIVE_A_CHIP) {
    Logger::get().info("Action Donner"); 
    // poser un jeton
    player.drop();

    // ajouter le jeton sur la table
    ++chipsOnTable;
  }

}


void NoThanks::display() {
  std::cout << "Il y a " << chipsOnTable << " jetons sur la table\n";
  std::cout << "La carte posee est " << cardOnTop.getValue() << std::endl;
 
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
