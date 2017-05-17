#include "NoThanks.hpp"

NoThanks::NoThanks(): currentPlayer(0),
		      chipsOnTable(0),
		      scores(),
		      cardOnTop(),
		      deck(),
		      players() {
  
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
  /*
  StringBuffer s;
  Writer<StringBuffer> writer(s);
  writer.StartObject();
  
  writer.String("players");
  writer.StartArray();
  for (auto player : players) {
    writer.StartObject();
    writer.String(JSON_KEY_NAME);
    writer.String(player->getName().c_str());
    
    writer.String(JSON_KEY_SCORE);
    writer.Uint(player->getScore());
  
    writer.String(JSON_KEY_COINS);
    writer.Uint(player->getNbChips());
  
    writer.String(JSON_KEY_CARDS);
    const std::set<int>& cards = player->getCards();

    writer.StartArray();
    for (auto card : cards) {
      writer.Uint(card);
    }
    writer.EndArray();
    writer.EndObject();

    
  }
  writer.EndArray();
  writer.EndObject();
  std::string all = s.GetString();
  */
  //send all data;
}

bool NoThanks::gameIsFinished() const {
  return deck.isEmpty();
}


std::string NoThanks::dispatch(int id, std::string& json) {
  Document document;
  document.Parse(json.c_str());
  std::string response;
  
  assert(document.IsObject());

  Value::ConstMemberIterator itr = document.FindMember("action");
  
  const std::string& action = (itr != document.MemberEnd())?
    itr->value.GetString():"undefined";

  itr = document.FindMember("param");
  const std::string& param = (itr != document.MemberEnd())?
    itr->value.GetString():"undefined";

  itr = document.FindMember("value");
  const std::string& value = (itr != document.MemberEnd())?
    itr->value.GetString():"undefined";
  
  // Command 'set'
  if(action == "set"){
    if(param == "name"){
      const std::string  old_name = players[id]->getName();
      players[id]->setName(value);
      
      response = old_name + " is now called " + value;
    }

    else {
      response = "invalid param :" + param;
    }
  }
  
  // Command 'get'
  else if(action == "get"){
    if(param == "name"){
      response = players[id]->getName();
    }
    
    else if(param == "score"){
      response = std::to_string(id);
    }

    else {
      response = "invalid param in : " + param;
    }
  }

  // Command 'play'
  else if(action == "play"){
    Action action = (param == "drop") ? ACT_GIVE_A_CHIP : ACT_TAKE_CHIPS;
    Player& player = *players[id];
    
    execute(action, player);
    updateScores();
    display();
  }

  // Invalid command
  else{
    response = "invalid command in : " + action;
  }

  return response;

}

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
