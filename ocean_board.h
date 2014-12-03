//Cassie Tarakajian, ctarakajian@gmail.com

#ifndef _OCEAN_BOARD_H
#define _OCEAN_BOARD_H

#include "board.h"
#include <string>

/*
 * An Ocean Board is the lower board on a battleship board, which contains
 * the ships for a player. The ships are placed on the grid, and they
 * are storied in a map, which maps the one character code on the 
 * grid to a Ship object, which is used to figure out whether or not
 * a Ship has been sunk.
 * 
 */
class OceanBoard : public Board
{
  private:
  	std::map<char, Ship> _ship_map;
  	void place_ships();
  public: 
  	OceanBoard(std::map<char, Ship> ship_map);
    bool all_ships_sunk();
    virtual void print();
    //Returns HIT if hit, OPEN if miss, ship code if sunk a ship
    char attack_position(std::pair<int,int> &move);
};

#endif /*_OCEAN_BOARD_H*/
