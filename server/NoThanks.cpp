#include "NoThanks.hpp"

void f(){
  network_run();
}


NoThanks::NoThanks(): currentPlayer(0),
		      chipsOnTable(0),
		      cardOnTop(),
		      deck(){
  nbPlayers = 5;
  players= new Player*[nbPlayers];
  
  for(int i=0; i<nbPlayers; i++){
    players[i] = new PlayerHuman();
  }
  
  players[0]->setName("Bobiwan");
  players[1]->setName("Liara");
  players[2]->setName("Karl");
  players[3]->setName("Robby");
  players[4]->setName("Yush");

  for(int i=0; i<nbPlayers; i++){
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
    if(!player.hasChips()) {
      Logger::get().info("Plus aucun jeton"); 
    }
    
    Logger::get().info("Action: prendre la carte et les jetons"); 
    
    // prendre jetons et carte
    player.take(chipsOnTable,deck.first().getValue());
    // Enlever les jetons sur la table
    chipsOnTable = 0;
    
    // tirer une nouvelle carte si possible
    cardOnTop = deck.next();
  }
  
  else if(action == ACT_GIVE_A_CHIP) {
    Logger::get().info("Action: donner un jeton"); 
    // poser un jeton
    player.drop();

    // ajouter le jeton sur la table
    ++chipsOnTable;
  }
  
}


void NoThanks::display() {
  Logger::get().info("Jetons sur table:"+std::to_string(chipsOnTable));

  for(int i=0;i<nbPlayers; i++){
    players[i]->info();
  }
}

bool NoThanks::gameIsFinished() const {
  return deck.isEmpty();
}


void NoThanks::run(){
  
  std::thread t(f);
  
  Logger::get().info(NOTHX_TITLE);
  
  while(!gameIsFinished()) {
    Player& player = *players[currentPlayer]; 
    Logger::get().info("Carte distribuee:"+
			 std::to_string(deck.first().getValue()));
    
    Logger::get().info("Au tour de " + player.getName());

    Action action = player.hasChips()? 
      player.play(deck.first()) : ACT_TAKE_CHIPS;

    execute(action, player);
    updateScores();
    display();

    selectNextPlayer();
  }
  updateScores();
  showScores();
  
  t.join();
}


void NoThanks::selectNextPlayer() {
  Logger::get().info("Joueur suivant...");
  currentPlayer++;
  currentPlayer%=nbPlayers;
}


void NoThanks::updateScores() {
  
  for(int i=0; i<nbPlayers; i++) {
    scores[i] = 0;
    const std::set<int>& cards = players[i]->getCards();
    auto it = cards.rbegin();  
    
    while(it != cards.rend()) {
      while(cards.find((*it)-1) != cards.end())
	++it;
      
      scores[i]+=*it;
      ++it;
    }
    scores[i] -= players[i]->getNbChips();
    players[i]->setScore(scores[i]);
  }
}

void NoThanks::showScores() const {  
  for(int i=0; i<nbPlayers; i++) {
    Logger::get().info(players[i]->getName()
		       +": "
		       +std::to_string(scores[i]));
  }
}


