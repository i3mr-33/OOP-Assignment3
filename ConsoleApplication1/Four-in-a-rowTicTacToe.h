#pragma once
#include "BoardGame_Classes.h"
#include <string>


using namespace std;
class Four_in_a_row_Board :public Board<char> {
protected :

public :
	Four_in_a_row_Board();

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class Four_in_a_row_UI : public UI<char> {
public:
    Four_in_a_row_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    Move<char>* get_move(Player<char>* player);

    Player<char>** setup_players();
};
