#ifndef TICTACTOE5x5_CLASSES_H
#define TICTACTOE5x5_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

//====================== TicTacToe5x5_Board Class ======================
class TicTacToe5x5_Board : public Board<char> {
private:
    char blank_symbol = '.'; 

public:
    TicTacToe5x5_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    void print_scores_and_winner();

private:
    int count_three_in_row(char sym);
};

//====================== TicTacToe5x5_UI Class ======================
class TicTacToe5x5_UI : public UI<char> {
public:
    TicTacToe5x5_UI();
    ~TicTacToe5x5_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // TICTACTOE5x5_CLASSES_H
