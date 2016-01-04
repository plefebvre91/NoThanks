#ifndef MOCKGAME_HPP
#define MOCKGAME_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "Definitions.hpp"
#include "Logger.hpp"

/**
 * Main class
 */

class MockGame {
public:
  /**
   * Constructor
   */
  MockGame(int, std::vector<std::string>&);

  /**
   * Destructor
   */
  ~MockGame();

  /**
   * Main loop
   */
  void run();

  /**
   * \return true if next player is not a human
   */
  bool currentPlayerIsAComputer() const {return false;}

  /**
   * Return the game state (JSON sstring)
   */
  std::string getJSON();
  
  void display();
};
#endif
