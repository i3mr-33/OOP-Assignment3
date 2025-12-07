#ifndef WORDTTT_CLASSES_H
#define WORDTTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;

/**
 * @brief 3x3 Word TicTacToe Board
 */
class WordTTT_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<string> dictionary;

    void load_dictionary(const string& filename);

    bool is_valid_word(const string& w) const;
    bool check_row(int r) const;
    bool check_col(int c) const;
    bool check_diagonals() const;

public:
    WordTTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
};

/**
 * @brief UI for Word TicTacToe
 */
class WordTTT_UI : public UI<char> {
public:
    WordTTT_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* p) override;
};

#endif
