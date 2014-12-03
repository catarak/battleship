//Cassie Tarakajian, ctarakajian@gmail.com

#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include "ship.h"
#include "board.h"
#include "ocean_board.h"
#include "target_board.h"
#include "computer_player.h"
#include <map>

/*
 * This class manages actually playing the game, with a human player versus
 * a computer one. This class just needs to be initalized with the set of ships, 
 * which player is going first, and whether or not the computer is intelligent. The
 * rest is handled under the covers.
 */
class GameManager {
  private:
  	OceanBoard _user_board;
  	OceanBoard _comp_board;
  	TargetBoard _user_target_board;
  	TargetBoard _comp_target_board;
  	std::map<char, Ship> _ship_map;
  	bool _computer_first;
  	ComputerPlayer _computer;

  	bool user_turn();
  	bool computer_turn();
    bool continue_game();
  	std::pair<int,int> get_user_input();
    void user_attack(std::pair<int,int> &move);
    void computer_attack(std::pair<int,int> &move);
  	bool input_valid(std::string &input1, std::string &input2);

  	std::pair<int,int> get_board_position(std::string &input1, std::string &input2);
    int column_to_int(char c);
    int row_to_int(char r);
    char int_to_column(int c);
    char int_to_row(int r);
    std::pair<char,char> get_printable_move(std::pair<int,int> &move);
  
  public:
  	GameManager(std::map<char, Ship> ships, bool strategy_mode, bool computer_first);
  	void start_game();
};

#endif /*_GAME_MANAGER_H*/