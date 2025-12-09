/**
 * @file WordTTT_Classes.h
 * @brief Header file for Word-based Tic-Tac-Toe game classes
 *
 * This variant uses letters instead of X/O. Players form 3-letter words
 * from a dictionary to win.
 */

#ifndef WORDTTT_CLASSES_H
#define WORDTTT_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;

/**
 * @class WordTTT_Board
 * @brief 3x3 board for Word Tic-Tac-Toe game
 *
 * Players place letters (A-Z) on a 3x3 grid.
 * Win condition: form a 3-letter word in any row, column, or diagonal
 * that exists in the loaded dictionary.
 */
class WordTTT_Board : public Board<char>
{
private:
    char blank_symbol = '.';
    vector<string> dictionary; // List of valid 3-letter words

    /**
     * @brief Loads 3-letter words from a file into dictionary
     * @param filename Path to dictionary text file
     */
    void load_dictionary(const string &filename);

    bool is_valid_word(const string &w) const;
    bool check_row(int r) const;
    bool check_col(int c) const;
    bool check_diagonals() const;

public:
    WordTTT_Board();

    bool update_board(Move<char> *move) override;
    bool is_win(Player<char> *p) override;
    bool is_lose(Player<char> *p) override;
    bool is_draw(Player<char> *p) override;
    bool game_is_over(Player<char> *p) override;
};

/**
 * @class WordTTT_UI
 * @brief User interface for Word Tic-Tac-Toe
 *
 * Handles player creation and move input for both human and computer.
 * Computer randomly selects empty cells and random letters.
 */
class WordTTT_UI : public UI<char>
{
public:
    WordTTT_UI();

    Player<char> *create_player(string &name, char symbol, PlayerType type) override;
    Move<char> *get_move(Player<char> *p) override;
};

#endif
