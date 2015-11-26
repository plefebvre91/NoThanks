#include "PlayerHuman.hpp"
#include <unistd.h>
PlayerHuman::PlayerHuman():Player(){
}

PlayerHuman::PlayerHuman(Network* network):Player(network) {
  net = network;
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


  Action action;
  int a = -1;
  while(a != 0 && a!=1) {
    a = net->getLastData().action;
    sleep(1);
  }
  switch(a){
  case 0: action = ACT_TAKE_CHIPS; break;
  case 1: action = ACT_GIVE_A_CHIP; break;
  default: action = ACT_GIVE_A_CHIP; break;
  }
  

  return action;
}
