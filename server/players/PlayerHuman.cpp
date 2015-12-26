#include "PlayerHuman.hpp"
#include <unistd.h>

PlayerHuman::PlayerHuman():Player() {
}

PlayerHuman::~PlayerHuman() {
}


Action PlayerHuman::play(const Card& card) {
  // int a = 0;
  // Action action;
  // (void)card;
  // std::cout << "Prendre (1) / Donner (2) ?: ";

  // while(a!= 1 && a!=2)
  //   std::cin >> a;
  (void)card;

  Action action;
  std::cout << "Action :\n(0) take\n(1) give\n";
  int a;
  std::cin >> a;
  switch(a){
  case 0: action = ACT_TAKE_CHIPS; break;
  case 1: action = ACT_GIVE_A_CHIP; break;
  default: action = ACT_GIVE_A_CHIP; break;
  }
  

  return action;
}
