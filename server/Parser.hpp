#ifndef NOTHX_PARSER_HPP
#define NOTHX_PARSER_HPP

#include <iostream>
#include <cstdio>

#include "rapidjson/document.h"
#include "Definitions.hpp"
#include "Logger.hpp"

using namespace rapidjson;

struct NetworkMessage {
  int action;
  std::string msg;
};


class Parser {
public:
  Parser();
  NetworkMessage get(const std::string& str);
  
};
#endif
