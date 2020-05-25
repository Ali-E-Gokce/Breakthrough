#include "State.h"
#define rowOfPieces 2
#define rows 8
#define columns 8
#define NINFINITY -9999.0
class Node {
  public:
    //each node represents a state
    Node(State state);
    //the heuristic function decides how good a state is
    float heuristic(bool turn);
    //fills this->childList, which is a vector of all
    void makeChildren();
    std::vector<Node> const & getChildren();
    void  showState();
    Node  bestChild();
    Node worstChild();
    Node letHumanPlay(int move);
    Node letComputerPlay(int steps);
    bool isTerminal();
    Node makeMove(int move);
    State  getState();
  private:
    int depth = 0;
    std::vector <Node> childList;
    // the brancing factor of breakthrough is 20 on average
    // childList.reserve(20);
    State parent;
    State m_state;
    float value;
    float getRandomFloat();
    static bool comp(const Node &first, const Node &other);
    void _letComputerPlay(int target, bool whitesTurn);
};
