//Cassie Tarakajian, ctarakajian@gmail.com

#include "board.h"

#ifndef _TARGET_BOARD_H
#define _TARGET_BOARD_H

/*
 * A Target Board is the upper board on a Battleship game, which
 * stores the various attacks that a user has made. This user can
 * store these moves as a hit or a miss, and can therfore use it to
 * plan their next move.
 */
class TargetBoard: public Board
{
  private:

  public:	
  	virtual void print();
  	void set_hit(std::pair<int,int> &position);
  	void set_miss(std::pair<int,int> &position);
};

#endif /*_TARGET_BOARD_H*/
