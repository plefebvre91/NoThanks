#include "NoThanks.hpp"

#include <vector>
#include <string>

NoThanks::NoThanks(): currentPlayer(0),
		      chipsOnTable(0),
		      scores(),
		      cardOnTop(),
		      deck(),
		      players(),
		      parser(){
  
  std::cout << "-- No Thanks! - Game server --"<< std::endl;
  
  nbPlayers = 2;
  
  for(int i=0; i<nbPlayers; i++){
    scores.push_back(0);
    players.push_back(new PlayerHuman());
    players[0]->setName("Player" + std::to_string(i));
  }
}

NoThanks::~NoThanks() {
  for(auto player : players){
    delete player;
  }
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
  std::vector<std::string> jsonPlayers;
  
  for(auto player : players) {
    player->info();
  }
}

bool NoThanks::gameIsFinished() const {
  return deck.isEmpty();
}


std::string NoThanks::dispatch(int id, std::string& json) {
  std::string response;

  Request request = parser.parse(json);

  const std::string& strAction = parser.getAction();
  const std::string& strParam = parser.getParam();
  const std::string& strValue = parser.getValue();

  Player& player = *players[id];
  
  switch(request){
  case (Request::INVALID_PARAM): response = "invalid param"; break;
  case (Request::INVALID_VALUE): response = "invalid value"; break;
  case (Request::INVALID_ACTION): response = "invalid action"; break;

  case (Request::PLAYER_INFO):
    response = players[id]->toJson();
    break;

  case (Request::SET_NAME):
    players[id]->setName(strValue);
    response = "name changed";
    break;

  case (Request::GET_NAME):
    response = players[id]->getName();
    break;
    
  case (Request::GET_SCORE):
    response = "{\"score\":\" " + std::to_string((int)(players[id]->getScore())) +" \"}";
    break;
    
  case (Request::PLAY_GIVE_A_CHIP):
    execute(ACT_GIVE_A_CHIP, player);
    updateScores();
    break;
  

  case (Request::PLAY_TAKE_CHIPS):
    execute(ACT_TAKE_CHIPS, player);
    updateScores();
    break;
    
  case (Request::GET_GAME):
    response = players[id]->toJson();
    break;
    
  case (Request::CARD_ON_TOP):
    std::cout << "get card on top\n";
    
    response = "{\"card\":\"resources/img/cards/" + std::to_string(deck.first().getValue()) + ".png\"}"; 

    std::cout << response + "\n";
    break;

    
  default: response = "unknown error"; break;
  }
  
  return response;
}
#if 0
void NoThanks::run(){
  
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
}
#endif

void NoThanks::selectNextPlayer() {
  Logger::get().info("Joueur suivant...");
  currentPlayer++;
  currentPlayer%=nbPlayers;
}


void NoThanks::updateScores() {
  for(auto player : players){
    
    const std::set<int>& cards = player->getCards();
    auto it = cards.rbegin();  
    Score score = 0;
    while(it != cards.rend()) {
      while(cards.find((*it)-1) != cards.end())
	++it;
      
      score += *it;
      ++it;
    }
    score -= player->getNbChips();
    player->setScore(score);
  }
}

void NoThanks::showScores() const {  
  for(auto player : players) {
    std::string score = std::to_string(player->getScore());
    std::string name  = player->getName();
    Logger::get().info(name + ": " + score);
  }
}
