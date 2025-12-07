#ifndef TICTACTOE5X5_CLASSES_H
#define TICTACTOE5X5_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
class TicTacToe5x5_Board : public Board<char> {
private:
    char blank_symbol = '.'; 

    /** count how many 3-in-a-row segments player with `sym` has */
    int count_three_in_row(char sym) const;

public:
    TicTacToe5x5_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    int get_score(char sym) const  { return count_three_in_row(sym); };
};

class TicTacToe5x5_UI : public UI<char> {
public:
    TicTacToe5x5_UI();
    ~TicTacToe5x5_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // TICTACTOE5X5_CLASSES_H
