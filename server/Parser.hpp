#ifndef PARSER_HPP
#define PARSER_HPP

#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"


enum class Request {
  SET_NAME,
  GET_NAME,
  GET_SCORE,
  PLAY_GIVE_A_CHIP,
  PLAY_TAKE_CHIPS,

  INVALID_PARAM,
  INVALID_VALUE,
  INVALID_ACTION,

  UNDEFINED
};
  

class Parser {
public:

  /*
   * Constructor
   */
  Parser();

  Request parse(const std::string& json);

  inline const std::string& getAction() const
  {
    return action;
  }

  inline const std::string& getValue() const
  {
    return value;
  }

  inline const std::string& getParam() const
  {
    return param;
  }


  /**
   * Destructor
   */
  ~Parser();
    
private:
  rapidjson::Document document;
  std::string action;
  std::string param;
  std::string value;
};

#endif
