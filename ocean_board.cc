//Cassie Tarakajian, ctarakajian@gmail.com

#include "ocean_board.h"
#include <iostream>

OceanBoard::OceanBoard(std::map<char, Ship> ship_map): Board(), _ship_map(ship_map) 
{
  place_ships();
}

void OceanBoard::print()
{
  //this is not the most efficient way to print, but it's clear.
  //put ships in a printable form
  std::vector<std::string> printable_ships;
  for (std::map<char, Ship>::iterator ship_it = _ship_map.begin();
       ship_it != _ship_map.end();
       ++ship_it) {
    std::string abbreviation(1, ship_it->first);
    printable_ships.push_back(abbreviation + ": " + ship_it->second.name());
  }
  
  std::string horizontal_line = "-----------------------------------------"; 
  std::cout << std::endl << 
    "      1  2  3  4  5  6  7  8  9  0     " << std::endl <<
    "      ----------------------------     " << std::endl;
  for (size_t row = 0; row < BOARD_SIDE; row++) { // iterate through all the rows
  //This prints out A,B,C,D,E,F
  std::cout << static_cast<char> (row + 65) << "  | ";
    for (int column = 0; column < BOARD_SIDE; column++) { // iterate through all the columns
      if (column != 0) { // we want this additional space eacg tune except the first
        std::cout << " ";
      }   
      std::cout << " " << _positions[row][column]; // compute the index of the array 
                                                   //to be printed and print it
    }
    if (row < printable_ships.size()) {
      std::cout << "     " + printable_ships.at(row);
    }
   std::cout << std::endl;
  }
    std::cout << std::endl;	
}

void OceanBoard::place_ships()
{
  //Randomly place ships on board
  srand(time(0));
  for (std::map<char, Ship>::iterator ship_it = _ship_map.begin();
       ship_it != _ship_map.end();
       /*want to move to next ship ONLY if we can place it*/) {

    //pick a random position
    Orientation ort = static_cast<Orientation>(rand() % 4); //Orientation of ship, left, down, up, or right
    unsigned int row = rand() % BOARD_SIDE;
    unsigned int column = rand() % BOARD_SIDE;

    //int ort_int = ort;
    //std::cout << "Orientation: " << ort << std::endl;
    //std::cout << "Row: " << row << std::endl;
    //std::cout << "Column: " << column << std::endl;


    //assume we can't place ship
    bool overlap = true;
    unsigned int ship_length = ship_it->second.length();
    char abbreviation = ship_it->first;

    //This could maybe be refactored???
    if (ort == Orientation::LEFT) {
      if ((column + 1) >= ship_length) { //if not off edge
        overlap = false; //to see if placing ship here will overlap
        for (unsigned int i = 0; i < ship_length; i++) {
          if (get_char(row, column - i) != 'o') {
            overlap = true;
          }
        }
      }
      if (!overlap) { //If ship doesn't overlap or fall off edge, put it on
        for (unsigned int i = 0; i < ship_length; i++) {
          set_char(abbreviation, row, column - i);
        }
        ++ship_it;
      }
    }
    else if (ort == Orientation::RIGHT) {
      if ((BOARD_SIDE - (column + 1)) >= ship_length) { //if not off edge
        overlap = false; //to see if placing ship here will overlap
        for (unsigned int i = 0; i < ship_length; i++) {
          if (get_char(row, column + i) != 'o') {
            overlap = true;
          }
        }
      }
      if (!overlap) { //If ship doesn't overlap or fall off edge, put it on
        for (unsigned int i = 0; i < ship_length; i++) {
          set_char(abbreviation, row, column + i);
        }
        ++ship_it;
      }
    }
    else if (ort == Orientation::DOWN) {
      if ((BOARD_SIDE - (row + 1)) >= ship_length) { //if not off edge
        overlap = false; //to see if placing ship here will overlap
        for (unsigned int i = 0; i < ship_length; i++) {
          if (get_char(row + i, column) != 'o') {
            overlap = true;
          }
        }
      }
      if (!overlap) { //If ship doesn't overlap or fall off edge, put it on
        for (unsigned int i = 0; i < ship_length; i++) {
          set_char(abbreviation, row + i, column);
        }
        ++ship_it;
      }
    }
    else if (ort == Orientation::UP) {
      if ((row + 1) >= ship_length) { //if not off edge
        overlap = false; //to see if placing ship here will overlap
        for (unsigned int i = 0; i < ship_length; i++) {
          if (get_char(row - i, column) != 'o') {
            overlap = true;
          }
        }
      }
      if (!overlap) { //If ship doesn't overlap or fall off edge, put it on
        for (unsigned int i = 0; i < ship_length; i++) {
          set_char(abbreviation, row - i, column);
        }
        ++ship_it;
      }
    }
  }
}

//Sets character at position on the board (in character array)
char OceanBoard::attack_position(std::pair<int,int> &move)
{
  int row = move.first;
  int column = move.second;
  char position = _positions[row][column];
  if (position == OPEN) {
    _positions[row][column] = MISS;
  }
  else {
    _ship_map.at(position).inc_damage();
    _positions[row][column] = HIT;
    //don't want to reveal the ship hit UNLESS ship is sunk
    if (!_ship_map.at(position).is_sunk()) {
      position = HIT;
    }
  }
  return position;
}

bool OceanBoard::all_ships_sunk()
{
  bool all_sunk = true;
  for (std::map<char, Ship>::iterator ship_it = _ship_map.begin();
       ship_it != _ship_map.end();
       ++ship_it) {
    if (!ship_it->second.is_sunk()) {
      all_sunk = false;
      return all_sunk;
    }
  }
  return all_sunk;
}
