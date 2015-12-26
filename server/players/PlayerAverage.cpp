#include "PlayerAverage.hpp"
#include <numeric>

PlayerAverage::PlayerAverage(){
}

PlayerAverage::~PlayerAverage() {
}


Action PlayerAverage::play(const Card& card) {
  if(cards.empty()) {
    return (card.getValue() < NOTHX_NB_CARD / 2)?
      ACT_TAKE_CHIPS :  ACT_GIVE_A_CHIP;
  }
  else {
    int average = 
      std::accumulate(cards.begin(), cards.end(), 0) / cards.size();
    
    return (card.getValue() < average || adjacentCardIsFound(card))?
      ACT_TAKE_CHIPS:ACT_GIVE_A_CHIP;
  }
}
