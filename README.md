#CLI Battleship

Compiled using GCC 4.2.1, C++11

This program simulates a game of Battleship. It was actually a project that I did in college, but then decided to refactor and rewrite to prove to myself that I had, in fact, become a better programmer. 

To play, download the project directory, then cd into that directory.

```bash
$ cd <path_to_project_directory>
$ make
$ ./battle (-f)(-n)(-s)
```

* The -f flag means that the computer goes first, otherwise the order is chosen randomly. 
* The -n means no submarines, which changes the set of ships on the board so that there are no ships of length 1. 
* The -s flags means the computer plays with a strategy instead of guessing randomly.

When a game begins, a player's ships and the computers ships 
are placed randomly. 

If strategy mode is on for the computer, it guesses in the most likely spot that it will hit a ship. It does this by calculating a grid of likelihoods. If the computer makes a hit, then it changes strategy and just guesses (intelligently) near where the ship was first hit. 

