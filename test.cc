#include "ship.h"
#include "board.h"
#include "ocean_board.h"
#include "target_board.h"
#include "computer_player.h"
#include "game_manager.h"

#include <iostream>
#include <map>
#include <string>
#include <cassert>

int main(void)
{
  //test Ship
  Ship s = Ship(2, "The Destroyer");
  assert (s.name() == "The Destroyer");
  assert (s.length() == 2);
  s.inc_damage();
  assert (!s.is_sunk());
  s.inc_damage();
  assert (s.is_sunk());

  std::map<char, Ship> ship_map = {{'A', Ship(5, "Aircraft Carrier")},
                                   {'B', Ship(4, "Battleship")},
                                   {'C', Ship(3, "Cruiser")}};
  OceanBoard ob = OceanBoard(ship_map);
  ob.print();

  TargetBoard tb = TargetBoard();
  tb.print();


  /*
  std::string s;
  char r, c;
  std::cin >> s >> r >> c;
  std::cout << s << " " << r << " " << c << std::endl;
  */
  /*std::map<char, int> m; 
  m['a'] = 1;
  m['b'] = 2;

  std::map<char, int> n (m);*/
  /*Board *b = new Board();
  b->initialize_board();
  b->print_board_trk();
  b->add_ships();
  b->place_ships();
  b->print_board();
  char C = 39;
  int i = C;
  std::cout << C << std::endl;*/
}
