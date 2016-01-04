#include "MockGame.hpp"
using namespace rapidjson;


static int rand_(int min, int max){
  return (min + rand()%max);
}


MockGame::MockGame(int _nbPlayers, std::vector<std::string>& names){
  Logger::get().info("Mock -- Constructeur");  
}

MockGame::~MockGame() {
  Logger::get().info("Mock -- Destructeur");  
}

void MockGame::display() {
  
}

std::string MockGame::getJSON(){
  StringBuffer s;
  Writer<StringBuffer> writer(s);
  writer.StartObject();
  
  writer.String("top");
  writer.Uint(rand_(3,33));
  
  writer.String("players");
  writer.StartArray();
  for (int i=0; i<2; i++) {
    writer.StartObject();
    writer.String(JSON_KEY_NAME);
    
    //    std::string name;
    //    name = "Joueur_" + std::to_string(rand_(1,10));
    writer.String( std::string("Joueur_" + std::to_string(rand_(1,10))).c_str());
    
    writer.String(JSON_KEY_SCORE);
    writer.Uint(rand_(1,10));
  
    writer.String(JSON_KEY_COINS);
    writer.Uint(rand_(1,11));
  
    writer.String(JSON_KEY_CARDS);

    writer.StartArray();
    for (int i=0; i<rand_(1,19); i++) {
      writer.Uint(rand_(1,33));
    }
    writer.EndArray();
    writer.EndObject();

    
  }
  writer.EndArray();
  writer.EndObject();
  std::string all = s.GetString();
  return all;
}

void MockGame::run(){
  Logger::get().info("Mock -- Tour suivant (run)");
}
