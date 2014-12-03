//Cassie Tarakajian, ctarakajian@gmail.com

#ifndef _COMPUTER_PLAYER_H
#define _COMPUTER_PLAYER_H

#include "ship.h"
#include "board.h"
#include "target_board.h"
#include <map>

struct ValueCompare {
	template <typename Lhs, typename Rhs>
  bool operator() (const Lhs& lhs, const Rhs& rhs) const 
  { 
  	return lhs.second.length() < rhs.second.length();
  }
};

/*
 * This is the AI player class. It can either guess randomly, or can make
 * intelligent choices in sinking ships. It has a pointer to its target board,
 * to keep track of past moves, and the ship map to keep track of which ships
 * the player has sunk. 
 * 
 */
class ComputerPlayer 
{
  public:
  	ComputerPlayer(TargetBoard *target_board, 
                   std::map<char, Ship> ship_map,
  		             bool intelligent=false);
  	std::pair<int, int> get_move();
  	//and want to know which ship hit
  	void update_strategy(char result);
    void print_cardinalities();
  private:
  	bool _intelligent;
    TargetBoard *_target_board;
    std::map<char, Ship> _ship_map;
    std::pair<int,int> _last_move;

    void initialize_cardinalities();
    void set_max_ship_length();
    void update_cardinalities();

    void get_random_move(std::pair<int,int> &move);

    void get_tracking_ship_move(std::pair<int,int> &move);
    void set_tracking_position(int &row, int &column);
    void change_tracking_orientation(int &row, int &column, char &position);
    void reset_tracking();

    void get_strategic_move(std::pair<int,int> &move);

    struct Strategy {
    	int cardinalities[BOARD_SIDE][BOARD_SIDE];
      bool tracking_ship;
      int max_ship_length;
      int num_ship_hits;
      std::vector<std::pair<int,int>> ship_hits;
      int ort;
      int distance;
      std::pair<int,int> first_hit;
    };

    Strategy _strategy;
};

#endif /*_COMPUTER_PLAYER_H*/ 