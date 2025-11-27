
#include "BoardGame_Classes.h"
using namespace std;

class TicTacToe4x4_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:

    TicTacToe4x4_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; };

    bool is_draw(Player<char>* player);

    bool game_is_over(Player<char>* player);
};



class TicTacToe4x4_UI : public UI<char> {
public:

    TicTacToe4x4_UI();

    ~TicTacToe4x4_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    virtual Move<char>* get_move(Player<char>* player);
private:
    vector<pair<int, int>> computer_pieces;
    bool is_initialized = false;
};