#ifndef NOTHANKS_PLAYER_HPP
#define NOTHANKS_PLAYER_HPP

#include <set>

#include "Definitions.hpp"
#include "Logger.hpp"
#include "Action.hpp"
#include "Card.hpp"
#include "Network.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

/**
 * Player abstract class
 */

class Player {
public:
  /**
   * Constructor
   */
  Player();

  /**
   * Destructor
   */
  virtual ~Player();  
  
  /**
   * Choose a move from the given card. Has to be implemented for each player
   */
  virtual Action play(const Card& card) = 0;
  
  /**
   * Getter for cards set
   */
  const std::set<int>& getCards() const;
  
  // accesseurs
  /**
   * \return this chips player amount 
   */
  int getNbChips() const;

  /**
   * \return true if player has at least 1 chip
   */
  bool hasChips() const;
  
  /**
   * Put a chip on the table
   */
  void drop();

  /**
   * Take the card and the chips on the table 
   */
  void take(int chips, int card);

  /**
   * \brief Setter for player name
   */
  void setName(std::string str);

  /**
   * Getter for player name
   */
  const std::string& getName() const;
  
  /**
   * Information about player
   */
  void info() const;

  /**
   * Setter for score
   */
  void setScore(int s);


  /**
   * Getter for score
   */
  int getScore() const;

  /**
   * Convert player information into a JSON String
   */
  std::string toJson() const;
  
protected:
  std::set<int> cards;
  bool adjacentCardIsFound(const Card& card) const;
  int score;
  int chips;
  std::string name;
};

#endif
