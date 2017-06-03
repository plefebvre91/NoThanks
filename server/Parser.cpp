#include "Parser.hpp"
#include <iostream>


Parser::Parser(){}

Parser::~Parser(){}

#define NOTHX_JSON_KEY_PARAM  "param"
#define NOTHX_JSON_KEY_VALUE  "value"
#define NOTHX_JSON_KEY_ACTION "action"

#define NOTHX_STR_PLAYER_INFO "player-info"
#define NOTHX_STR_UNDEFINED   "undefined"
#define NOTHX_STR_SET         "set"
#define NOTHX_STR_GET         "get"
#define NOTHX_STR_PLAY        "play"
#define NOTHX_STR_SCORE       "score"
#define NOTHX_STR_NAME        "name"
#define NOTHX_STR_GAME        "game"
#define NOTHX_STR_TAKE        "take"
#define NOTHX_STR_DROP        "drop"
#define NOTHX_STR_CARD_ON_TOP "card-on-top"

Request Parser::parse(const std::string& json)
{
  Request rc = Request::UNDEFINED;
  document.Parse(json.c_str());
  
  if(!document.IsObject()){
    std::cout << "Invalid Object";
    return Request::INVALID_ACTION;
  }
  
  rapidjson::Value::ConstMemberIterator itr =
    document.FindMember(NOTHX_JSON_KEY_ACTION);
  
  action = (itr != document.MemberEnd())?
    itr->value.GetString():NOTHX_STR_UNDEFINED;
  
  itr = document.FindMember(NOTHX_JSON_KEY_PARAM);
  param = (itr != document.MemberEnd())?
    itr->value.GetString():NOTHX_STR_UNDEFINED;
  
  itr = document.FindMember(NOTHX_JSON_KEY_VALUE);
  value = (itr != document.MemberEnd())?
    itr->value.GetString():NOTHX_STR_UNDEFINED;

  // Command 'player-info'
  if(action == NOTHX_STR_PLAYER_INFO) {
    rc = Request::PLAYER_INFO;
  }
  
  // Command 'set'
  else if(action == NOTHX_STR_SET) {
    if(param == NOTHX_STR_NAME) {
      rc = Request::SET_NAME;
    }
    else {
      rc = Request::INVALID_PARAM;
    }
  }
  
  
  // Command 'get'
  else if(action == NOTHX_STR_GET){
    if(param == NOTHX_STR_NAME){
      rc = Request::GET_NAME;
    }
    
    else if(param == NOTHX_STR_SCORE){
      rc = Request::GET_SCORE;
    }

    else if(param == NOTHX_STR_GAME){
      rc = Request::GET_GAME;
    }
    
    else if(param == NOTHX_STR_CARD_ON_TOP){
      rc = Request::CARD_ON_TOP;
    }
    
    else {
      rc = Request::INVALID_PARAM;
    }
  }

  // Command 'play'
  else if(action == NOTHX_STR_PLAY){
    if(param == NOTHX_STR_DROP){
      rc = Request::PLAY_GIVE_A_CHIP;
    }

    else if(param == NOTHX_STR_TAKE){
      rc = Request::PLAY_TAKE_CHIPS;
    }
    
    else {
      rc = Request::INVALID_PARAM;
    }
  }
  
  // Invalid command
  else{
    rc = Request::INVALID_ACTION;
  }

  return rc;
}
