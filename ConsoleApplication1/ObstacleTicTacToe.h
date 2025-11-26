//#pragma once
//#include "BoardGame_Classes.h"
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//
//class ObstacleTicTacToe_Board : public Board<int> {
//private:
//    vector<int> available_odds;  ///< Available odd numbers for Player 1
//    vector<int> available_evens; ///< Available even numbers for Player 2
//
//public:
// 
//    ObstacleTicTacToe_Board();
//
//
//    bool update_board(Move<int>* move);
//
//    bool is_win(Player<int>* player);
//
//    bool is_lose(Player<int>* player) { return false; }
//
//    bool is_draw(Player<int>* player);
//
//    bool game_is_over(Player<int>* player);
//
//    bool is_number_available(int number, bool is_player1);
//
//    vector<int> get_available_numbers(bool is_player1) const;
//};
//
//
//class ObstacleTicTacToe_UI : public UI<int> {
//public:
//
//    ObstacleTicTacToe_UI();
//
//
//    Player<int>* create_player(string& name, int symbol, PlayerType type);
//
//    Move<int>* get_move(Player<int>* player);
//
//    Player<int>** setup_players();
//};
