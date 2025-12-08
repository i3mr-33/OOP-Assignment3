#pragma once
#include "BoardGame_Classes.h"
#include <string>

using namespace std;

class SUS_Board : public Board<char> {
private:
    string sus;
    int score_S;
    int score_U;
    int total_sus_count;

public:
    
    SUS_Board();

    int count_SUS_sequences();
    int minimax(int& x, int& y, bool isMaximizing, bool firstStep );
    int check_status();

    bool update_board(Move<char>* move) ;
    bool is_win(Player<char>* player) ;
    bool is_lose(Player<char>* player) ;
    bool is_draw(Player<char>* player) ;
    bool game_is_over(Player<char>* player) ;
 
};



class SUS_UI : public UI<char> {
public:
    SUS_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) ;
    
    Move<char>* get_move(Player<char>* player) ;
   
    Player<char>** setup_players() ;
};


class AI_Player : public Player<char> {
private : 
    SUS_Board* board;
public : 
    AI_Player(char symbol, SUS_Board* b); 
    void get_best_move(int& y, int& x);
};