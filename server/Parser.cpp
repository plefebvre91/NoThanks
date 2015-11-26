#include "Parser.hpp"
#include <assert.h>
Parser::Parser(){}

NetworkMessage Parser::get(const std::string& str) {
  Document document;
  
  char *buffer = (char*)str.c_str();
  std::cout << "lol: " << buffer << std::endl;
  NetworkMessage nm;
  nm.msg="Vide";
  nm.action=-1;
  

  if (document.ParseInsitu(buffer).HasParseError()) {
    Logger::get().info("** Erreur syntaxe json:");
    Logger::get().info(buffer);
    
    return nm;

  }
   
  int action = document[JSON_KEY_ACTION].GetUint();
  std::string msg = document[JSON_KEY_MESSAGE].GetString();
    

  nm.msg= msg;
  nm.action = action;
  
  Logger::get().info(msg);
  Logger::get().info("Action: "+std::to_string(action));
  
  return nm;
}
