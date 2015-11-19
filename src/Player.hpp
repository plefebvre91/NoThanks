#ifndef NOTHANKS_PLAYER_HPP
#define NOTHANKS_PLAYER_HPP

#include <set>

#include "Definitions.hpp"
#include "Logger.hpp"
#include "Action.hpp"
#include "Card.hpp"

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
  int getCards() const;
  
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
   * Setter for player name
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

private:
  int chips;
  std::set<int> cards;
  std::string name;
};

#endif
