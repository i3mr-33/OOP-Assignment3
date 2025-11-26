#pragma once
#include "BoardGame_Classes.h"
#include <string>
#include <queue> 
#include <utility> 

using namespace std;


class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';
    queue<pair<int, int>> x_history;
    queue<pair<int, int>> o_history;

public:
    Infinity_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Infinity_UI : public UI<char> {
public:
    Infinity_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};