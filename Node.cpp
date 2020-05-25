#include <iostream>
#include <vector>
#include <random>

#include "Node.h"


// A node represents each State
Node::Node(State state){
        m_state = state;
}

// the heuristic decides who much we like a state
float Node::heuristic(bool turn) {
  int heuristic_value;
  // if the state is terminal, the person winning wins,
  // winning is preferable to all other outcomes, and loosing is
  // worse than all other outcomes
  if (m_state.isTerminal()){
    if (turn == this->m_state.getTurn()) {
      return  NINFINITY;
    }
    else {
      return  INFINITY;
    }
  }
  else {
    // otherwise, the heuristic is how many more pieces you have
    // compared to your opponent
    std::vector<int> whites = this->m_state.getWhites();
    std::vector<int> blacks = this->m_state.getBlacks() ;
    if (turn) {
      heuristic_value =  whites.size() - blacks.size();
    }
    else {
      heuristic_value =  blacks.size() - whites.size();
    }
  }
  // add a random float 0-1 to break ties
  return (float)heuristic_value + getRandomFloat();
}

// makes this-childList, a vector of nodes consisting of all
// children state has
void Node::makeChildren() {
  std::vector <State> stateList = m_state.moveGenerator();
  for (int i=0; i<stateList.size(); i++){
    Node child = Node(stateList[i]);
    child.depth  = this->depth + 1;
    childList.push_back(child);
  }
}

// returns all children the current state has
 // if makeChildren has not been called before, it will be empty
std::vector<Node> const & Node::getChildren() {
   return childList;
 }

// shows the state
 void Node::showState() {
    m_state.showState();
  }
// finds the best child among all the children
Node Node::bestChild()  {
    return *std::max_element(childList.begin(), childList.end(), comp);
}
// finds the worst child among all the children
Node Node::worstChild() {
    return *std::min_element(childList.begin(), childList.end(), comp);
}

  Node Node::letHumanPlay(int move){
    Node newNode = this->makeMove(move);
    return newNode;
  }

  Node Node::letComputerPlay(int steps){
    std::cout << "Thinking..." << std::endl;
    this->_letComputerPlay(steps, m_state.getTurn());
    Node bestNode = this->bestChild();
    bestNode.depth = 0;
    bestNode.childList.clear();
    return bestNode;
  }

  bool Node::isTerminal(){
    return this->m_state.isTerminal();
  }
  Node Node::makeMove(int move){
    State newState = this->m_state.makeMove(move);
    return Node(newState);
  }
  State Node::getState(){
    return this->m_state;
  }

float Node::getRandomFloat(){
  std::random_device rd;
  std::mt19937 gen(rd());
  return std::generate_canonical<float, 10>(gen);
}

bool Node::comp(const Node &first, const Node &other) {
    return(first.value < other.value);
  }

void Node::_letComputerPlay(int target, bool whitesTurn){
  float value;
  if (depth < target){

    if (m_state.isTerminal()){
      this->value = this->heuristic(whitesTurn);
    }
    else {
      this->makeChildren();
      for(std::vector <Node>::iterator it = childList.begin(); it != childList.end(); ++it){
        it->_letComputerPlay(target, whitesTurn);
      }
      if (this->depth % 2 == 0) {
        this->value =  bestChild().value;
      }
      else {
        this->value = worstChild().value;
      }
    }
  }
  else {
    this->value = this->heuristic(whitesTurn);
  }
}
