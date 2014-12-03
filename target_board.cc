//Cassie Tarakajian, ctarakajian@gmail.com

#include "target_board.h"
#include <iostream>

void TargetBoard::print()
{
  //formatting
  std::string horizontal_line = "-----------------------------------------"; 
  std::cout << std::endl << "      1  2  3  4  5  6  7  8  9  0" << std::endl 
    << "      ----------------------------" << std::endl;
  for (int row = 0; row < 10; row++) { // iterate through all the rows
    //this prints out A-J
    std::cout << static_cast<char> (row + 65) << "  | ";
    for (int column = 0; column < 10; column++) { // iterate through all columns
      if (column != 0) { //want this additional space each time except the first
        std::cout << " ";
      }   
      std::cout << " " << _positions[row][column]; // compute the index of the 
                                             //array to be printed and print it
    }
   std::cout << std::endl;
  }
  std::cout << std::endl; 
}

//Sets character at position on the board (in character array)
void TargetBoard::set_hit(std::pair<int,int> &position)
{
  _positions[position.first][position.second] = HIT;
}

//Sets character at position on the board (in character array)
void TargetBoard::set_miss(std::pair<int,int> &position)
{
  _positions[position.first][position.second] = MISS;
}