//Cassie Tarakajian, ctarakajian@gmail.com

#include "board.h"
#include <iostream>

Board::Board(): _positions(new char[BOARD_SIDE][BOARD_SIDE])
{
  initialize_board();
}

Board::~Board()
{
  delete[] _positions; 
}

//Initializez board to all o's
void Board::initialize_board()
{
  for (int i = 0; i < BOARD_SIDE; i++) {
    for (int j = 0; j < BOARD_SIDE; j++) {
      _positions[i][j] = 'o';
    }
  }
}

//Returns character at position on board (in character array)
char Board::get_char(int row, int column)
{
  return _positions[row][column];
}

//Returns character at position on board (in character array)
char Board::get_char(std::pair<int,int> &position)
{
  return _positions[position.first][position.second];
}

//Sets character at position on the board (in character array)
void Board::set_char(char c, int row, int column)
{
  _positions[row][column] = c;
}

//Sets character at position on the board (in character array)
void Board::set_char(char c, std::pair<int,int> &position)
{
  _positions[position.first][position.second] = c;
}
