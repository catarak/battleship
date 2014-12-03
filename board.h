//Cassie Tarakajian, ctarakajian@gmail.com

#ifndef _BOARD_H
#define _BOARD_H

#include "ship.h"
#include <vector>
#include <map>

#define BOARD_SIDE 10
#define HIT 'x'
#define MISS '/'
#define OPEN 'o'

enum Orientation {LEFT, UP, RIGHT, DOWN};

//map orientation to unit vector to rotate row and columns
const std::map<Orientation, std::pair<int,int>> ORT_TO_VECTOR = 
  {
    {Orientation::LEFT,  {0, -1}},
    {Orientation::UP,    {-1, 0}},
    {Orientation::RIGHT, {0, 1}},
    {Orientation::DOWN,  {1, 0}}
  };  

/**
 * A Board object is a BOARD_SIDE X BOARD_SIDE array of characters, that is initialized
 * to all OPEN spaces. It is an abstract class.
 */
class Board
{
  private:
    void initialize_board(); //initalizes board to all 'o's
  protected:
    //BOARD_SIDE X BOARD_SIDE array of chars
    char (*_positions)[BOARD_SIDE];
    //sets a character on the board, for placing ships 
    void set_char(char c, int row, int column);
    void set_char(char c, std::pair<int,int> &position);
  public:
    Board(); 
    ~Board();
    //Returns char at a position on the board
    char get_char(int row, int column);
    char get_char(std::pair<int,int> &position); 
    virtual void print() = 0;
};
#endif /*_BOARD_H*/
