//Cassie Tarakajian, ctarakajian@gmail.com

#include "ship.h"

//Constructor: sets length and name according to parameters, sets damage to zero
Ship::Ship(int length, const std::string name): _length(length), _name(name), _damage(0)
{}

bool Ship::operator<(Ship other) const
{
  return length() > other.length();
}

//Increments the damage by 1
void Ship::inc_damage()
{
  _damage += 1;
}

//Tests if a ship is sunk, aka every spot on the ship has been hit
bool Ship::is_sunk() const
{
  //If the length and damage of the ship are equal
  if (_length - _damage == 0) {
    return true;
  }
  else {
    return false;
  }
}

//Returns the name of the ship
const std::string Ship::name() const
{
  return _name;
}

//Returns the length of the ship
int Ship::length() const
{
  return _length;
}
