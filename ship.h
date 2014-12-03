//Cassie Tarakajian, ctarakajian@gmail.com

#ifndef _SHIP_H
#define _SHIP_H

#include <string>

/**
 * A Ship object contains the name of a ship, the length of the ship, and
 * how much damage has been done to the ship.
 */
class Ship
{
private:
  int _length; //length of ship
  std::string _name; //name of ship
  int _damage; //damage done to ship
public:
  Ship(int length, const std::string name); //constructor
  bool operator<(Ship other) const;
  void inc_damage(); //increments damage by 1
  bool is_sunk() const; //tests if ship is sunk (all spots have been hit)
  const std::string name() const; //returns name of ship
  int length() const; //returns length of ship
};

#endif /*_SHIP_H*/

