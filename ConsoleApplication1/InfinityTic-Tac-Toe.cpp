#include <iostream>
#include <cctype>
#include "InfinityTic-Tac-Toe.h"

using namespace std;

//--------------------------------------- Infinity_Board Implementation

Infinity_Board::Infinity_Board() : Board(3, 3) {
 
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Infinity_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = toupper(move->get_symbol());

    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != blank_symbol) {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;


    if (symbol == 'X') {
        x_history.push({ x, y });
        if (x_history.size() > 3) {
            pair<int, int> oldest = x_history.front();
            x_history.pop();
            board[oldest.first][oldest.second] = blank_symbol;
            n_moves--; 
        }
    }
    else if (symbol == 'O') {
        o_history.push({ x, y });
        if (o_history.size() > 3) {
            pair<int, int> oldest = o_history.front();
            o_history.pop();
            board[oldest.first][oldest.second] = blank_symbol; 
            n_moves--;
        }
    }

    return true;
}

bool Infinity_Board::is_win(Player<char>* player) {
    char sym = toupper(player->get_symbol());


    for (int i = 0; i < 3; i++) {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym)
            return true;
    }

    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) return true;

    return false;
}

bool Infinity_Board::is_lose(Player<char>* player) {
    return false;
}

bool Infinity_Board::is_draw(Player<char>* player) {

    return false;
}

bool Infinity_Board::game_is_over(Player<char>* player) {
    return is_win(player);
}

//--------------------------------------- Infinity_UI Implementation

Infinity_UI::Infinity_UI() : UI<char>("Welcome to Infinity Tic-Tac-Toe!", 3) {}

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Infinity_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter your move (row and column): ";
        cin >> x >> y;
    }
    else {
        x = rand() % 3;
        y = rand() % 3;
    }
    return new Move<char>(x, y, player->get_symbol());
}