/*#pragma once
#include "BoardGame_Classes.h"
#include <string>
#include <iostream>
#include <vector>


using namespace std;
class Connect_Four_Board :public Board<char> {
private :
    int rows; 
    int columns; 
    char Mark; 
    bool check_Four(char mark); 
public :
	Connect_Four_Board();

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    bool is_position_available(int number, bool is_player1);
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
*/

