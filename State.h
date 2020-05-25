class State {
  public:
    State();

    // All attribuets stays the same when an objects is copied, the positions will be updated later
    State(const State& obj);
    // prints the state of the board onto the terminal
    void showState();
    // checks if a given state is a terminal state, i.e. the game is over
    bool isTerminal();

    bool getTurn();

    void changeTurn();

    State makeMove(int move);
    // deallocates the vectors upon destructuon
   ~State();

    std::vector<int> const & getBlacks();
    std::vector<int> const & getWhites();
    bool isValidMove(int move);

    std::vector <State> moveGenerator();

  private:
    std::vector <int> whites;
    std::vector <int> blacks;
    std::vector <int> white_terminals;
    std::vector <int> black_terminals;
    bool whitesTurn = true;
};
