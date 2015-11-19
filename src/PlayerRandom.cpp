#include "PlayerRandom.hpp"

PlayerRandom::PlayerRandom(){
}

PlayerRandom::~PlayerRandom() {
}


Action PlayerRandom::play(const Card& card) {
  return (rand()%2)? ACT_TAKE_CHIPS:ACT_GIVE_A_CHIP;
}
