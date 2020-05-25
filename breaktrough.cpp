#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <cctype>
#include <random>

#include "Node.h"
#define rowOfPieces 2
#define rows 8
#define columns 8
#define NINFINITY -9999.0





// the user inputs a4a5, but State class takes 4151
class Game {
  public:
    Game() {
      setPlayersTurn();
    }

  void playGame() {
    bool playersTurn = this->playerPlaysWhite;
    while (!root.isTerminal()){
      root.showState();
      if (playersTurn){
        int move = askUserForMove();
        root = root.letHumanPlay(move);
      }
      else {
        root = root.letComputerPlay(3);
      }
      playersTurn = !playersTurn;
    }
    std::cout << "here" << std::endl;
    root.showState();



    std::cout << "Game over. ";
    if (root.getState().getTurn()) {
      std::cout << "Black won." << std::endl;
    }
    else {
      std::cout << "White won." << std::endl;
    }
  }
  private:
    State initial_state;
    Node  root = Node(initial_state);
    char  playerTurnChoice;
    bool  playerPlaysWhite;
    void setPlayersTurn(){
      std::cout << "Do you want to play black or white? b/w" << std::endl;
      std::cin  >> playerTurnChoice;

      if (tolower(playerTurnChoice) == 'w'){
        this->playerPlaysWhite = true;
      }
      else if (tolower(playerTurnChoice) == 'b'){
        this->playerPlaysWhite = false;
      }
      else {
        setPlayersTurn();
      }
    }
    bool isValidMove(int move){
      return this->root.getState().isValidMove(move);
    }

    int askUserForMove() {
      std::string inMove;
      std::cout << "Make a move." << std::endl;
      std::cin >> inMove;
      int stateMove = convertToStateMove(inMove);
      return stateMove;
    }

    int convertToStateMove(std::string& move){
      for (int i=0; i<move.size(); i++) {
        if (!isdigit(move[i])){
          int asciiValue     = ((int)move[i] - 96);
          std::string letter = std::to_string(asciiValue);
          move.replace(i,1, letter);
        }
      }
      std::swap(move[0], move[1]);
      std::swap(move[2], move[3]);
      int stateMove    = std::stoi(move);
      int moveSquare   = stateMove / 100;
      int targetSquare = stateMove % 100;
      if (!isValidMove(stateMove)){
        std::cout << "Invalid move" << std::endl;
        return askUserForMove();
      }
      return stateMove;
    }
};


int main() {
    Game myGame = Game();
    myGame.playGame();

}
