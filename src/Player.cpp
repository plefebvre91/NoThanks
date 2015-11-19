#include "Player.hpp"

Player::Player():cards() {
  chips = NOTHX_NB_CHIPS;
}

Player::~Player() {

}

int Player::getChips() const {
  return chips;
}
