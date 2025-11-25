#pragma once
#include "BoardGame_Classes.h"
#include <string>
#include <queue> 
#include <utility> 

using namespace std;



class Infinity_Board : public Board<int> {
private:
    queue<pair<int, int>> move_history;

public:

    Infinity_Board();

  
    bool update_board(Move<int>* move) ;
    bool is_win(Player<int>* player) ;
    bool is_lose(Player<int>* player) ;
    bool is_draw(Player<int>* player) ;
    bool game_is_over(Player<int>* player);
    void display_board() ;
};

class Infinity_UI : public UI<int> {
public:
    Infinity_UI();
    Player<int>* create_player(string& name, int symbol, PlayerType type) ;
    Move<int>* get_move(Player<int>* player) ;
    Player<int>** setup_players() ;
};