//Cassie Tarakajian, ctarakajian@gmail.com

#include "computer_player.h"
#include <algorithm>
#include <random>
#include <iostream>

ComputerPlayer::ComputerPlayer(TargetBoard *target_board, 
	                             std::map<char, Ship> ship_map,
	                             bool intelligent): 
  _intelligent(intelligent), 
  _target_board(target_board),
  _ship_map(ship_map)
{
	set_max_ship_length();
  initialize_cardinalities();	
}

void ComputerPlayer::initialize_cardinalities()
{
	for (int i = 0; i < (BOARD_SIDE + 1)/2; i++) { //BOARD_SIDE+1 in case board 
    for (int j = 0; j < (BOARD_SIDE + 1)/2; j++) { //side is odd
      _strategy.cardinalities[i][j] = _strategy.cardinalities[i][BOARD_SIDE-1-j] =
       _strategy.cardinalities[BOARD_SIDE-1-i][j] =
       _strategy.cardinalities[BOARD_SIDE-1-i][BOARD_SIDE-1-j]= i + j + (_strategy.max_ship_length-1)*2;
    }
  }
}

void ComputerPlayer::update_cardinalities()
{
  for (int row = 0; row < BOARD_SIDE; row++) {
    for (int column = 0; column < BOARD_SIDE; column++) {
      if (_strategy.cardinalities[row][column] != -1) { // make sure we are not looking at a -1
        int count = 0; // the cardinality counter
        for (int distance = 1; distance < _strategy.max_ship_length; distance++) { // count the spaces to the right
          if (column + distance >= BOARD_SIDE) { // if we are out of bounds
            break;
          }
          if (_strategy.cardinalities[row][column + distance] == -1) { // we have found a space that has been shot at
            break;
          }
          count++; // we are in bounds, and it is not a known space
        }
        for (int distance = 1; distance < _strategy.max_ship_length; distance++) { // count the spaces to the left
          if (column - distance < 0) { // if we are out of bounds
            break;
          }
          if (_strategy.cardinalities[row][column - distance] == -1) { // we have found a space that has been shot at
            break;
          }
          count++; // we are in bounds, and it is not a known space
        }
        for (int distance = 1; distance < _strategy.max_ship_length; distance++) { // count the spaces up
          if (row - distance < 0) { // if we are out of bounds
            break;
          }
          if (_strategy.cardinalities[row - distance][column] == -1) { // we have found a space that has been shot at
            break;
          }
          count++; // we are in bounds, and it is not a known space
        }
        for (int distance = 1; distance < _strategy.max_ship_length; distance++) { // count the spaces down
          if (row + distance >= BOARD_SIDE) { // if we are out of bounds
            break;
          }
          if (_strategy.cardinalities[row + distance][column] == -1) { // we have found a space that has been shot at
            break;
          }
            count++; // we are in bounds, and it is not a known space
        }
        _strategy.cardinalities[row][column] = count;
      }
    }
  }
}

void ComputerPlayer::print_cardinalities()
{
  std::string horizontal_line = "-----------------------------------------"; 
  std::cout << std::endl << 
    "      1  2  3  4  5  6  7  8  9  0     " << std::endl <<
    "      ----------------------------     " << std::endl;
  for (int row = 0; row < 10; row++) { // iterate through all the rows
  std::cout << static_cast<char> (row + 65) << "  | ";
    for (int column = 0; column < 10; column++) { // iterate through all the columns
      if (column != 0) { // we want this additional space eacg tune except the first
        std::cout << " ";
      }   
      std::cout << " " << _strategy.cardinalities[row][column]; // compute the index of the array 
                                                   //to be printed and print it
    }
   std::cout << std::endl;
  }
    std::cout << std::endl;
}

void ComputerPlayer::set_max_ship_length()
{
	_strategy.max_ship_length = std::max_element(_ship_map.begin(), _ship_map.end(), ValueCompare())->second.length();
}

std::pair<int, int> ComputerPlayer::get_move()
{
	std::pair<int,int> move = {0,0};
	if (!_intelligent) {
    get_random_move(move);
	}
	else if(_strategy.tracking_ship) {
		get_tracking_ship_move(move);
	}
	else {
		get_strategic_move(move);
	}
	//computer remembers its last move
	_last_move = move;
	//update candinalities
	_strategy.cardinalities[move.first][move.second] = -1;
  return move;
}


void ComputerPlayer::get_random_move(std::pair<int,int> &move)
{
	int row, column;
	std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> random_position(0, 9);
  do {
  	row = random_position(gen);
    column = random_position(gen);
  } while(_target_board->get_char(row,column) != 'o');
  move = std::make_pair(row, column);
}
    
void ComputerPlayer::set_tracking_position(int &row, int &column)
{
	row = _strategy.first_hit.first 
    + _strategy.distance * ORT_TO_VECTOR.at(static_cast<Orientation>(_strategy.ort)).first;
  column = _strategy.first_hit.second 
    + _strategy.distance * ORT_TO_VECTOR.at(static_cast<Orientation>(_strategy.ort)).second;
}

void ComputerPlayer::change_tracking_orientation(int &row, int &column, char &position)
{
	_strategy.ort += 1;
  std::cout << "Orientation: " <<_strategy.ort << std::endl;
	if (_strategy.ort > Orientation::DOWN) {
    	//change dat first hit!!!!!
    	_strategy.ship_hits.erase(_strategy.ship_hits.begin());
    	_strategy.first_hit = _strategy.ship_hits.front();
    	_strategy.ort = 0;
  }
	_strategy.distance = 0; 
	set_tracking_position(row, column);
  position = _target_board->get_char(row, column);
}

void ComputerPlayer::get_tracking_ship_move(std::pair<int,int> &move)
{
  std::cout << "Trying to get tracking ship move!" << std::endl;
	int trk_row, trk_column;
	set_tracking_position(trk_row, trk_column);
  char current_guess = _target_board->get_char(trk_row, trk_column);

  while (current_guess == HIT || current_guess == MISS){
    //If ship could still possibly be in this orientation
    if (current_guess == HIT && _strategy.distance < _strategy.max_ship_length) {
  	  //then guess the next position
  	  _strategy.distance += 1;
  	  set_tracking_position(trk_row, trk_column);
  	  //if not off of the edge of the board
      if (trk_row < BOARD_SIDE && trk_column < BOARD_SIDE){
        std::cout << "Current Guess: " << current_guess << std::endl;
        std::cout << "Row: " << trk_row << std::endl;
        std::cout << "Column: " << trk_column << std::endl;
      	current_guess = _target_board->get_char(trk_row, trk_column);
      }
      else {
      	change_tracking_orientation(trk_row, trk_column, current_guess);
      }
    }
    else {
    	change_tracking_orientation(trk_row, trk_column, current_guess);
    }
  }
  move = std::make_pair(trk_row, trk_column);
}

void ComputerPlayer::get_strategic_move(std::pair<int,int> &move)
{
  for (int i = 0; i < BOARD_SIDE; i++) {
    for (int j = 0; j < BOARD_SIDE; j++) {
      if (_strategy.cardinalities[move.first][move.second] < _strategy.cardinalities[i][j]) {
        move = std::make_pair(i, j);
      }
    }
  }
}

void ComputerPlayer::update_strategy(char result)
{
  if (result == OPEN) {
    if (_intelligent && !_strategy.tracking_ship) {
    	update_cardinalities();
    } 
  }	
  else {
    if (!_strategy.tracking_ship) {
    	_strategy.num_ship_hits = 0;
    	_strategy.first_hit = _last_move;
    	_strategy.tracking_ship = true;
    }	
    _strategy.num_ship_hits += 1;
    _strategy.ship_hits.push_back(_last_move);

    if(result != HIT) {
    	//if only hit one ship during tracking mode
    	if (_strategy.num_ship_hits == _ship_map.at(result).length()) {
        update_cardinalities();
        reset_tracking();
    	}
  	  //if hit multiple ships
  	  else {
        _strategy.num_ship_hits = _strategy.num_ship_hits - _ship_map.at(result).length();
        //Don't know where we first hit the other ship, but will guess it is the next hit
        _strategy.ship_hits.erase(_strategy.ship_hits.begin());
    	  _strategy.first_hit = _strategy.ship_hits.front();
    	  _strategy.ort = 0;
	      _strategy.distance = 0; 
  	  }
      _ship_map.erase(result);
      set_max_ship_length();	
    }
  }
}

void ComputerPlayer::reset_tracking()
{
  _strategy.tracking_ship = false;
  _strategy.num_ship_hits = 0;
  _strategy.ort = 0;
  _strategy.distance = 0;
  _strategy.ship_hits.erase(_strategy.ship_hits.begin(), _strategy.ship_hits.end());
  _strategy.first_hit = std::make_pair(-1, -1);
}

