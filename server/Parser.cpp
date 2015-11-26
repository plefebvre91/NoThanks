#include "Parser.hpp"
#include "ctime"
#include <assert.h>
Parser::Parser(){}

NetworkMessage Parser::get(const std::string& str) {
  Document document;

  
  NetworkMessage nm;
  nm.action = -1;
  nm.msg = "Vide";
  nm.name = "Bobiwane";

  std::string s(str.c_str());
  char* buffer = (char*)s.c_str();
  if (document.ParseInsitu(buffer).HasParseError()) {
    Logger::get().info("Erreur de Syntaxe" + str);
    return nm;
  }
  

  int action = document[JSON_KEY_ACTION].GetUint();
  std::string msg = document[JSON_KEY_MESSAGE].GetString();
  std::string name = "Bobiwan";
    

  nm.msg= msg;
  nm.action = action;
  nm.name.assign(name);

  Logger::get().info(msg);
  Logger::get().info("Action: "+std::to_string(action));
  
  return nm;
}
