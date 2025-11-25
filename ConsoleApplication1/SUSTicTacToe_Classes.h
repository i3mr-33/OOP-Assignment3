#pragma once
#include "BoardGame_Classes.h"
#include <string>

using namespace std;

class SUS_Board : public Board<char> {
private:
    string sus;

public:
    
    SUS_Board();

   
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool is_position_available(int number, bool is_player1) ;
    vector<int> get_available_position(bool is_player1) ;

    int count_SUS_sequences();
};



class SUS_UI : public UI<char> {
public:
    SUS_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    
    Move<char>* get_move(Player<char>* player) override;
   
    Player<char>** setup_players() override;
};