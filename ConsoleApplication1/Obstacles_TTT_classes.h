#ifndef OBSTACLES_TTT_CLASSES_H
#define OBSTACLES_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <utility>
#include <vector>
using namespace std;

// ==================== Obstacles_Board Class ====================
class Obstacles_Board : public Board<char> {
private:
    char blank_symbol = '.';
    char obstacle_symbol = '#';
    vector<pair<int, int>> obstacle_positions;

    void add_obstacles();

public:
    Obstacles_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    vector<pair<int, int>> get_obstacles() const { return obstacle_positions; }
    char get_obstacle_symbol() const { return obstacle_symbol; }
    char get_blank_symbol() const { return blank_symbol; }
};

// ==================== Obstacles_UI Class ====================
class Obstacles_UI : public UI<char> {
private:
    Obstacles_Board* obs_board;

public:
    Obstacles_UI();
    ~Obstacles_UI() override = default;

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

    void display_board_with_obstacles() const;
    void set_board(Obstacles_Board* board);
};

#endif // OBSTACLES_TTT_CLASSES_H