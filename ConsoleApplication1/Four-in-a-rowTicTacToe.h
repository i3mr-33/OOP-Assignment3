/*#pragma once
#include "BoardGame_Classes.h"
#include <string>


using namespace std;
class Connect_Four_Board :public Board<char> {
private :
    char Mark; 
    int count_Four(); 
public :
	Connect_Four_Board();

    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class Connect_Four_UI : public UI<char> {
public:
    Connect_Four_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    Move<char>* get_move(Player<char>* player);

    Player<char>** setup_players();
};
*/
