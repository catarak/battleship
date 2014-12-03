//Cassie Tarakajian, ctarakajian@gmail.com

#include "game_manager.h"
#include <iostream>

GameManager::GameManager(std::map<char, Ship> ships, 
                         bool strategy_mode, 
                         bool computer_first): 
                         _user_board(ships),
                         _comp_board(ships),
                         _ship_map(ships),
                         _computer_first(computer_first),
                         _computer(&_comp_target_board, ships, strategy_mode)
{

}

void GameManager::start_game()
{
  if (_computer_first) {
    computer_turn();
  }
  while(user_turn() && computer_turn()) {
  }
}

bool GameManager::computer_turn()
{
  std::pair<int,int> comp_move = _computer.get_move();
  computer_attack(comp_move);
  return continue_game();
}

bool GameManager::user_turn()
{
  _user_target_board.print();
  _user_board.print();

  std::pair<int, int> user_move = get_user_input();
  user_attack(user_move);
  return continue_game();
}

bool GameManager::continue_game()
{
  if (_user_board.all_ships_sunk()) {
    std::cout <<"Game is over, the evil machine has won!"<< std::endl; 
    return false;
  }
  else if (_comp_board.all_ships_sunk()) {
    std::cout << "Game is over, you have won! Yay!" << std::endl;
    return false;
  }
  return true;
}

std::pair<int,int> GameManager::get_user_input()
{
  std::string input1, input2;

  do {
    std::cout << "Please input the space you want to attack (q or quit to terminate program): ";
    std::cin >> input1;
    if (input1 == "q" || input1 == "quit") {
      exit(0);
    }
    std::cin >> input2;
  } while (!input_valid(input1, input2));
  return get_board_position(input1, input2); 
}

void GameManager::user_attack(std::pair<int,int> &move)
{
  char result = _comp_board.attack_position(move);
  std::pair<char,char> printable_move = get_printable_move(move);
  //TODO convert move to printable
  if (result == OPEN) {
    std::cout << "Splash! User shot " << printable_move.first << " " 
      << printable_move.second << " and missed!" << std::endl;
    _user_target_board.set_miss(move);
  }
  else {
    std::cout << "Boom! User shot " << printable_move.first 
      << " " << printable_move.second << " and hit!" << std::endl;
    _user_target_board.set_hit(move);
    //If ship is sunk, result returns ship abbreviation
    if (result != HIT) {
      std::cout << "Evil Machine says, 'Drat! You sank my " << _ship_map.at(result).name() << "!'" << std::endl;
    }
  }

}

void GameManager::computer_attack(std::pair<int,int> &move)
{
  char result = _user_board.attack_position(move);
  std::pair<char,char> printable_move = get_printable_move(move);
  if (result == OPEN) {
    std::cout << "Splash! Evil Machine shot " << printable_move.first << " " 
      << printable_move.second << " and missed!" << std::endl;
      _comp_target_board.set_miss(move);
  }
  else {
    std::cout << "Boom! Evil Machine shot " << printable_move.first << " " << 
      printable_move.second << " and hit!" << std::endl;
    _comp_target_board.set_hit(move);
    if (result != HIT) {
      std::cout << "Your " << _ship_map.at(result).name() 
        << " has been sunk!" << std::endl;
    }
  }
  _computer.update_strategy(result);
}

//Convert row char to integer
int GameManager::row_to_int(char r) {
  return r - 'A';
}

//Convert row in integer form to char form
char GameManager::int_to_row(int r) {
  return r + 'A';
}

//Convert column in char form to int form
int GameManager::column_to_int(char c) {
  int column;
  if (c != '0') {
    column = c - '1';
  }
  else {
    column = c - '0' + 9; //'0' corresponds to column 9;
  }
  return column;
}

//Convert column in int form to char form
char GameManager::int_to_column(int c) {
  if (c == BOARD_SIDE - 1) { // special case for maximum index
    c = 0;
  }
  else {
    c++;
  }
  return '0' + c;
}

std::pair<char,char> GameManager::get_printable_move(std::pair<int,int> &move)
{
  return std::make_pair(int_to_row(move.first), int_to_column(move.second));
}

std::pair<int,int> GameManager::get_board_position(std::string &input1, std::string &input2)
{
  int row = row_to_int(input1.at(0));
  int column = column_to_int(input2.at(0));
  return std::make_pair(row, column);
}

bool GameManager::input_valid(std::string &input1, std::string &input2)
{
    if (input1 == "A" || input1 == "B" || 
        input1 == "C" || input1 == "D" || 
        input1 == "E" || input1 == "F" || 
        input1 == "G" || input1 == "H"  || 
        input1 == "I" || input1 == "J") {
      if (input2 == "1" || input2 == "2" || 
          input2 == "3" || input2 == "4" || 
          input2 == "5" || input2 == "6" || 
          input2 == "7" || input2 == "8" || 
          input2 == "9" || input2 == "0") {
        //I don't like that I'm generating the integer position twice, but it's
        //part of validating the user's input
        std::pair<int,int> move = get_board_position(input1, input2);
        char position = _user_target_board.get_char(move);
        if (position == OPEN) {
          return true;
        }
        else {
          std::cout << "You are trying to attack a position you already hit. Try another position." << std::endl;
          return false;
        }
    }
  }

  std::cout << "Invalid input.  Please enter space to attack in the format \"A 7\"" << std::endl;
  return false;
}