#pragma once
#include "BoardGame_Classes.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Connect_Four_Board :public Board<char> {
private:
    int n_moves = 0;
public:

    Connect_Four_Board();

    int minimax4(int& best_col, bool isMaximizing, int depth,int alpha, int beta  , int original_depth);
    int Connnect_Four_check_status();
    int evaluate_board(char ai_symbol, char human_symbol);

    bool check_Four(char mark);
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    
    vector<int> get_available_position(bool is_player1);
};

class Connect_Four_UI : public UI<char> {
public:
    Connect_Four_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    Move<char>* get_move(Player<char>* player);

    Player<char>** setup_players();

    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

class Connect_Four_AI_Player : public Player<char> {
private:
    Connect_Four_Board* board;
public:
    Connect_Four_AI_Player(char symbol, Connect_Four_Board* b);
    void get_best_move4(int& best_col);
};