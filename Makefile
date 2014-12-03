# Cassie Tarakajian, ctarakajian@gmail.com

CXXFLAGS=-pedantic -Wall -Wextra -std=c++11 -Wabi -Weffc++ -Wctor-dtor-privacy -Wold-style-cast -Woverloaded-virtual -Wsign-promo

all: battle 

battle: battle.cc ship.o board.o ocean_board.o target_board.o computer_player.o game_manager.o

test: ship.o board.o ocean_board.o target_board.o computer_player.o game_manager.o

ship.o: ship.h ship.cc
board.o: board.h ship.h board.cc
ocean_board.o: ship.h board.h ocean_board.h ocean_board.cc 
target_board.o: ship.h board.h target_board.h target_board.cc
computer_player.o: ship.h board.h target_board.h computer_player.cc
game_manager.o: ship.h board.h target_board.h ocean_board.h computer_player.h game_manager.cc

clean:
	rm -rf battle test *.o
zip:
	tar zcvf battleship.tar.gz Makefile README ship.h board.h ship.cc board.cc battle.cc
