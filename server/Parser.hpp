#ifndef NOTHX_PARSER_HPP
#define NOTHX_PARSER_HPP

#include <iostream>
#include <cstdio>
#include <vector>
#include "rapidjson/document.h"
#include "Definitions.hpp"
#include "Logger.hpp"

using namespace rapidjson;

struct Info {
  int nbPlayers;
  std::vector<std::string> names;
  std::vector<std::string> types;
  std::string message;
  int action;
  int is_fresh;
  
  void reset() {
    nbPlayers = 0;
    names.clear();
    types.clear();
    action = 0;
    is_fresh = false;
  }
};



class Parser {
public:
  Parser();
  Info& get(const std::string& str);
  
private:
  Info info;
};
#endif
