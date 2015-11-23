#ifndef NOTHX_CARD_HPP
#define NOTHX_CARD_HPP

#include "Definitions.hpp"

/**
 * Card class
 */

class Card {
public:
  /**
   * Getter for card value
   */
  int getValue() const;

  /**
   * Setter for card value
   */
  void setValue(int v);

private:
  int value;
};

#endif
