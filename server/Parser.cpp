#include "Parser.hpp"
#include "ctime"
#include <assert.h>
#include <mutex>
Parser::Parser(){}

Info& Parser::get(const std::string& str) {
  Document document;
  
  std::string s(str.c_str());
  char* buffer = (char*)s.c_str();
  
  if (document.ParseInsitu(buffer).HasParseError()) {
    Logger::get().info("Erreur de Syntaxe" + str);
    return info;
  }
  
  if(document.HasMember(JSON_KEY_ACTION))
    info.action = document[JSON_KEY_ACTION].GetUint();
  
  if(document.HasMember(JSON_KEY_MESSAGE))
    info.message = document[JSON_KEY_MESSAGE].GetString();
  
  if(document.HasMember("players")) {
    const Value& players = document["players"];
    
    info.nbPlayers = players.Size();

    for (Value::ConstValueIterator itr = players.Begin(); 
	 itr != players.End(); ++itr) {
      if(itr->HasMember("name")){
	const Value& metadata = (*itr)["name"];
	info.names.push_back(metadata.GetString());
      }

      if(itr->HasMember("type")){
	const Value& metadata = (*itr)["type"];
	info.types.push_back(metadata.GetString());
      }
    }
  }
    
  Logger::get().info("From client:");
  Logger::get().info("Nombre joueurs: "+std::to_string(info.nbPlayers));
  Logger::get().info("Action:"+std::to_string(info.action));

  
  // for(auto n : info.names){
  //   Logger::get().info("Boucle noms");
  //   Logger::get().info(n);
  // }

  // for(auto n : info.types){
  //   Logger::get().info("Boucle types");
  //   Logger::get().info(n);
  // }
  
  return info;
}
