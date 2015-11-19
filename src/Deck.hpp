#ifndef DECK_HPP
#define DECK_HPP

#include <utility>
#include <ctime>
#include <cstdlib>
#include "Definitions.hpp"

class Deck {
public:
  //Constructor/Destructor
  Deck();
  ~Deck();
  
  //Returns true if all card have been played
  bool isEmpty();

  //Returns the last removed tile index 
  //  const Card& getNext() const;

private:
  void shuffle();
  int deck[NOTHX_NB_CARD];
  int topIndex;
};

#endif
