#include "PlayerHuman.hpp"

PlayerHuman::PlayerHuman(){
}

PlayerHuman::~PlayerHuman() {
}


Action PlayerHuman::play(const Card& card) {
  int a;
  Action action;
  (void)card;
  std::cout << "1 : prendre la carte et les jetons" << std::endl;
  std::cout << "2 : donner un jeton" << std::endl;

  while(a!= 1 && a!=2)
    std::cin >> a;

  switch(a){
  case 1: action = ACT_TAKE_CHIPS; break;
  case 2: action = ACT_GIVE_A_CHIP; break;
  }
  return action;
}
