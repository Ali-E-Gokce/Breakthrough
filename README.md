# Breakthrough
Breakthrough board game playable on the terminal

This is an implementation of breakthrough that can be played via the terminal. The rules can be found here:

https://www.chessprogramming.org/Breakthrough_(Game)

Input is taken as a FEN string x1y1y2x2 where x1y1 is the square with the moving piece,
and y2x2 is where you want to move it to.

The AI uses a simple minimax algorithm with no optimizaiton.

In the future, I might add a better GUI, and optimize the searching algorithm.

It is compiled like:

g++ -std=c++11  -nostdinc++   breaktrough.cpp State.cpp Node.cpp

The game was invented by Dan Troyka.

