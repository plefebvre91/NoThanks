#include "Player.hpp"

Player::Player():cards() {
  cards.reset();
  chips = NOTHX_NB_CHIPS;
}

Player::~Player() {

}

int Player::getCards() {
  return (int)cards.to_ulong();
}


int Player::getChips() {
  return chips;
}


int Player::getScore() {
  int index = NOTHX_NB_CHIPS-1;
  int score = 0;

  while(index > 1) {
    if(cards.test(index)) {
      index--;
      while(index >= 1 && cards.test(index)) {
	index--;
      }
      score -= (index+1);
    }
    else {
      index--;
    }
  }
  
  return (score + chips);
}




