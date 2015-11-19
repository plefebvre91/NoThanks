#include "NoThanks.hpp"

NoThanks::NoThanks(): cardOnTop(), deck(){
  nbPlayers = 2;
  players = new PlayerHuman[nbPlayers];
  players[0].setName("Bobiwan");
  players[1].setName("Liara");
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
    player.take(chipsOnTable,deck.first().getValue());
    // Enlever les jetons sur la table
    chipsOnTable = 0;
    
    // tirer une nouvelle carte si possible
    cardOnTop = deck.next();
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
  for(int i=0;i<nbPlayers; i++){
    players[i].info();
  }
}

bool NoThanks::gameIsFinished() const {
  return deck.isEmpty();
}


void NoThanks::run(){
  Logger::get().info(NOTHX_TITLE);
  
  while(!gameIsFinished()) {
    Player& player = players[currentPlayer]; 
    
    std::cout << "Carte distribuée : " << deck.first().getValue() << "\n";

    std::cout << "Au tour de " << player.getName() << " " << std::endl;
    Action action = player.hasChips()? player.play(deck.first()) : ACT_TAKE_CHIPS;
    execute(action, player);
    display();
    selectNextPlayer();
  }
}


void NoThanks::selectNextPlayer(){
  Logger::get().info("Joueur suivant...");
  currentPlayer++;
  currentPlayer%=nbPlayers;
}
