#include "NoThanks.hpp"

NoThanks::NoThanks(): currentPlayer(0),
		      chipsOnTable(0),
		      cardOnTop(),
		      deck() {
  nbPlayers = 2;
  players= new Player*[nbPlayers];
  players[0] = new PlayerRandom();//PlayerHuman();
  players[1] = new PlayerRandom();
  players[0]->setName("Bobiwan");
  players[1]->setName("Liara");

  for(int i=0; i<NOTHX_NB_PLAYERS_MAX; i++){
    scores[i] = 0;
  }
}


NoThanks::~NoThanks() {
  for(int i=0; i<nbPlayers; i++){
    delete players[i];
  }
  delete [] players;
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
    players[i]->info();
  }
}

bool NoThanks::gameIsFinished() const {
  return deck.isEmpty();
}


void NoThanks::run(){
  Logger::get().info(NOTHX_TITLE);
  
  while(!gameIsFinished()) {
    Player& player = *players[currentPlayer]; 
    
    std::cout << "Carte distribuée : " << deck.first().getValue() << "\n";

    std::cout << "Au tour de " << player.getName() << " " << std::endl;
    Action action = player.hasChips()? player.play(deck.first()) : ACT_TAKE_CHIPS;
    execute(action, player);
    display();
    selectNextPlayer();
  }
  updateScores();
  showScores();
}


void NoThanks::selectNextPlayer() {
  Logger::get().info("Joueur suivant...");
  currentPlayer++;
  currentPlayer%=nbPlayers;
}


void NoThanks::updateScores() {
  for(int i=0; i<nbPlayers; i++) {
    const std::set<int>& cards = players[i]->getCards();
    
    auto it = cards.rbegin();  
    
    while(it != cards.rend()) {
      while(cards.find((*it)-1) != cards.end())
	++it;
      
      scores[i]+=*it;
      ++it;
    }
    scores[i] -= players[i]->getNbChips();
  }
}

void NoThanks::showScores() const {  
  for(int i=0; i<nbPlayers; i++) {
    std::cout << players[i]->getName() << ": " << scores[i] << std::endl;
  }
}
