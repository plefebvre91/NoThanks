#ifndef NOTHANKS_PLAYER_AVERAGE_HPP
#define NOTHANKS_PLAYER_AVERAGE_HPP

#include "Player.hpp"
#include "Definitions.hpp"

/**
 * Averagely playing player class. Implements Player class.
 */

class PlayerAverage : public Player {
public:
  /**
   * Constructor
   */
  PlayerAverage();

  /**
   * Destructor
   */
  virtual ~PlayerAverage();  

  /**
   * Choose the move to play
   */
  virtual Action play(const Card& card);
};

#endif
