#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <cctype>
#include <random>


#define rowOfPieces 2
#define rows 8
#define columns 8
#define NINFINITY -9999.0
#include "State.h"


State::State() {
  // whites and blacks is a vector of the position of each piece for each color
  // white terminals are the columns that the white player needs to get to win
  whites.reserve(rowOfPieces*columns);
  blacks.reserve(rowOfPieces*columns);
  white_terminals.reserve(columns);
  black_terminals.reserve(columns);
  // the following lines will create all the pieces, the algebra is such that
  // black will start from position 11/a1 , and white will end at yx where
  // y=number of columns and x=number of rows.
  // There will be rowOfPieces numbers of rows for each color
  // there can be at most 9 rows and columns currently
  for (int i=1; i<rowOfPieces+1; i++) {
    for (int j=1; j<columns+1; j++) {
      blacks.push_back(i*10 + j);
    }
  }
    // the outer loop makes sure a piece is generated for each row that is
    // filled, starting from the back of the board (i.e. index rows) for whites
    // and the start of the board (i.e. index 0) for blacks
  for (int i=(rows-rowOfPieces)+1; i<rows+1; i++) {
    for (int j=1; j<columns+1; j++) {
      whites.push_back(i * 10 + j);
    }
  }
  for (int i=1; i<columns+1; i++) {
      black_terminals.push_back(rows*10 + i);
      white_terminals.push_back(10 + i);
    }
}


// All attribuets stays the same when an objects is copied, the positions will be updated later
State::State(const State& obj) {
  this->whites           = std::vector <int>(obj.whites);
  this->blacks           = std::vector <int> (obj.blacks);
  this->white_terminals  = std::vector <int>(obj.white_terminals);
  this->black_terminals  = std::vector <int>(obj.black_terminals);
  this->whitesTurn       = obj.whitesTurn;
}

// prints the state of the board onto the terminal
void State::showState(){
  // the following twom lines clear the screan after each move, this requires ANSI Color/VT100 control set
  std::cout << "\033[2J";
  std::cout << "\033[%0;%0H";

  int pos;
  int asciiValueOfA = 97;
  std::cout << "  ";
  // the x positions are stored as an integer, but printed as characters a-z
  for (int i = asciiValueOfA; i < columns + asciiValueOfA; i++){
    std::cout << char(i);
  }
  std::cout << std::endl;
  // prints a '.' for emtpy spaces, O for white pieces, X for black pieces
  for (int i = 1; i < rows + 1; i++){
    // prints the y positions
    std::cout << i << " ";
    for (int j = 1; j < columns + 1; j++){
      // iterates over all posiitons on the board,
      // if a piece exists on that position, an 'X' for blacks or 'O' for
      // whites is printed, if the square is empty, a '.' is printed
      pos = i * 10 + j;
      if (std::find(whites.begin(), whites.end(), pos) != whites.end())
        std::cout << "O";
      else if (std::find(blacks.begin(), blacks.end(), pos) != blacks.end())
        std::cout << "X" ;
      else
        std::cout << ".";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
// checks if a given state is a terminal state, i.e. the game is over
bool State::isTerminal() {
  bool found;
  //if no white pieces are left, black wins
    if (this->whites.size() == 0){
      return true;
    }
    //checks if any of the white pieces are in the final row, hence black wins the game
    for (auto x = std::end(white_terminals); x != std::begin(white_terminals);) {
      found = std::find(this->whites.begin(), this->whites.end(), *--x) != this->whites.end();
      if (found)
        return true;
      }
    // if no blacks pieces are left, black wins
    if (this->blacks.size() == 0){
      return true;
    }
    //checks if any of the black pieces are in the final row, hence black wins the game
    for (auto x = std::end(black_terminals); x != std::begin(black_terminals);){
      found = std::find(this->blacks.begin(), this->blacks.end(), *--x) != this->blacks.end();
      if (found)
        return true;
      }
  return false;
}
// returns true if it is whites turn, false if not
bool State::getTurn() {
  return whitesTurn;
}
// changes turn to the opponent's turn
void State::changeTurn() {
  this->whitesTurn = !(this->whitesTurn);
}

// takes a 4 figit integer, the first two digits are the postion yx
// of the moving piece, the second two are the position of the target square
// illegal moves are not geneterade by the move generator, hence there is
State State::makeMove(int move) {
  // make a copy of the current state
  State new_state   = *this;
  // by dividing by 100, we get the first two digits
  // of the four digit move, which is the original square
  // the moving piece was on
  int moving_square = move / 100;
  // by taking the modulo by 100,
  // we get the last two digits of the
  int target_square = move % 100;
  int capture_index;
  int moving_index;
  std::vector<int>::iterator is_capture;
  std::vector<int>::iterator moving_iterator;
  std::vector<int>::iterator target_index;
  if (this->whitesTurn){
    // if the target square has a black piece on it, remove it
    is_capture = std::find(new_state.blacks.begin(), new_state.blacks.end(), target_square);
    if (is_capture != new_state.blacks.end()){
      capture_index = std::distance(new_state.blacks.begin(), is_capture);
      new_state.blacks.erase(new_state.blacks.begin()+capture_index);
    }
    moving_iterator = std::find(new_state.whites.begin(), new_state.whites.end(), moving_square);
    //remove old position from whites positions
    moving_index = std::distance(new_state.whites.begin(), moving_iterator);
    new_state.whites.erase(new_state.whites.begin() + moving_index);
    //add new new position to black positions
    new_state.whites.push_back(target_square);
  }
  else {
      is_capture = std::find(new_state.whites.begin(), new_state.whites.end(), target_square);
      if (is_capture != new_state.whites.end()){
        capture_index = std::distance(new_state.whites.begin(), is_capture);
        new_state.whites.erase(new_state.whites.begin()+capture_index);
      }
      moving_iterator = std::find(new_state.blacks.begin(), new_state.blacks.end(), moving_square);
      moving_index = std::distance(new_state.blacks.begin(), moving_iterator);
      new_state.blacks.erase(new_state.blacks.begin() + moving_index);
      new_state.blacks.push_back(target_square);
    }
    new_state.changeTurn();
    return new_state;
}
// deallocates the vectors upon destructuon
State::~State(){
  std::vector<int>().swap(this->whites);
  std::vector<int>().swap(this->blacks);
}

std::vector<int> const & State::getBlacks() {
  return blacks;
}

std::vector<int> const & State::getWhites(){
  return whites;
}
bool State::isValidMove(int move){
  int moveSquare   = move / 100;
  int targetSquare = move % 100;
  int squareDiff = targetSquare - moveSquare;
  if (this->whitesTurn) {
    if (!(squareDiff == -9 || squareDiff == -10 || squareDiff == -11)){
      return false;
    }
    if (targetSquare >= moveSquare){
      return false;
    }
    if (!(std::find(whites.begin(), whites.end(), moveSquare) != whites.end()))
      return false;
    if (squareDiff == -10 && std::find(blacks.begin(), blacks.end(), targetSquare) != blacks.end())
      return false;
    if (targetSquare % 10 < 1 || targetSquare % 10 > columns)
      return false;
    if (std::find(whites.begin(), whites.end(), targetSquare) != whites.end())
      return false;
  }
  else {
    if (!(squareDiff == 9 || squareDiff == 10 || squareDiff == 11))
      return false;
    if (!(std::find(blacks.begin(), blacks.end(), moveSquare) != blacks.end()))
      return false;
    if (squareDiff == 10 && std::find(whites.begin(), whites.end(), targetSquare) != whites.end())
      return false;
    if (targetSquare % 10 < 1 || targetSquare % 10 > columns)
      return false;
    if (std::find(blacks.begin(), blacks.end(), targetSquare) != blacks.end())
      return false;
  }
  return true;
}

std::vector <State> State::moveGenerator() {
  std::vector <State> allMoves;
  if (this->whitesTurn){
    int num_possible_moves = whites.size() * 3;
    allMoves.reserve(num_possible_moves);
    for (auto x = std::end(whites); x != std::begin(whites);){
        int pos = *--x;
        int moves[3] = {pos-9, pos-10, pos-11};
        for (int i=0; i<3; i++){
          int target_square = moves[i];
          int move = pos * 100 + target_square;
          if (this->isValidMove(move)) {
            State new_state = makeMove(move);
            allMoves.push_back(new_state);
          }
        }
    }
  }
  else {
    int num_possible_moves = blacks.size() * 3;
    allMoves.reserve(num_possible_moves);
    for (auto x = std::end(blacks); x != std::begin(blacks);){
        int pos = *--x;
        int moves[3] = {pos+9, pos+10, pos+11};
        for (int i=0; i<3; i++){
          int target_square = moves[i];
          int move = pos * 100 + target_square;
          if (this->isValidMove(move)) {
            State new_state = makeMove(move);
            allMoves.push_back(new_state);
          }
        }
    }
  }
  return allMoves;
}
