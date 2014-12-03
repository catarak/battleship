//Cassie Tarakajian, ctarakajian@gmail.com

#include "game_manager.h"
#include <iostream>

std::map<char,Ship> SHIP_SET_I = {
  {'A', Ship(5, "Aircraft Carrier")},
  {'B', Ship(4, "Battleship")},
  {'C', Ship(3, "Cruiser")},
  {'d', Ship(2, "Destroyer 1")},
  {'D', Ship(2, "Destroyer 2")},
  {'s', Ship(1, "Submarine 1")},
  {'S', Ship(1, "Submarine 2")}
};

std::map<char,Ship> SHIP_SET_II = {
  {'A', Ship(5, "Aircraft Carrier")},
  {'B', Ship(4, "Battleship")},
  {'c', Ship(3, "Cruiser 1")},
  {'C', Ship(3, "Cruiser 2")},
  {'d', Ship(2, "Destroyer 1")},
  {'D', Ship(2, "Destroyer 2")},
  {'E', Ship(2, "Destroyer 3")}
};



int main(int argc, char *argv[])
{
  srand(time(0));
  bool comp_first, comp_strategy;
  comp_strategy = false;
  std::map<char,Ship> &ship_set = SHIP_SET_I;
  //decide which player is going first randomly
  comp_first = rand() % 2;

  //Probably should use an option parser library for this
  //see which player is going first
  std::string f = "-f", first = "--first";
  //no subs mode
  std::string n = "-n", nsubs = "--nosubs";
  //computer uses a strategy
  std::string s = "-s", strategy = "--strategy";
  //check for all of these flags
  if (argc != 1) {
    for (int i = 1; i < argc; i++) {
      if (f.compare(argv[i]) == 0 || first.compare(argv[i]) == 0) // computer has the first move
      {
        comp_first = true;
      }
      else if (n.compare(argv[i]) == 0 || nsubs.compare(argv[i]) == 0) {
        ship_set = SHIP_SET_II;
      }
      else if (s.compare(argv[i]) == 0 || strategy.compare(argv[i]) == 0) {
        comp_strategy = true;
      }
      else {
        std::cout << "Unknown flag entered, recognized flags are as follows:" << std::endl;
        std::cout << "-f or --first for the computer to have the first move." << std::endl;
        std::cout << "-n or --nosubs for no subs mode" << std::endl;
        std::cout << "-s or --strategy for the computer to guess strategically instead of randomly." << std::endl;
      }
    }
  }
  GameManager Battleship = GameManager(ship_set,comp_strategy,comp_first);
  Battleship.start_game();


}
