/**
 * @file WordTTT_Classes.cpp
 * @brief Implementation of Word-based Tic-Tac-Toe game
 *
 * This is a Tic-Tac-Toe variant where players place letters
 * and win by forming 3-letter words from a dictionary.
 */

#include "WordTTT_Classes.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// ---------------- Dictionary Loader ----------------
/**
 * @brief Loads 3-letter words from dictionary file
 * @param filename Path to dictionary text file
 *
 * Reads file, filters 3-letter words, converts to uppercase,
 * and stores them in the dictionary vector.
 */
void WordTTT_Board::load_dictionary(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "ERROR: Could not open dictionary file: " << filename << endl;
        return;
    }

    string w;
    while (file >> w)
    {
        if (w.size() == 3)
        {
            transform(w.begin(), w.end(), w.begin(), ::toupper);
            dictionary.push_back(w);
        }
    }
    file.close();
}

// ---------------- Constructor ----------------
/**
 * @brief Constructs WordTTT board
 *
 * Initializes 3x3 board with '.' (empty),
 * sets move counter to zero, loads dictionary.
 */
WordTTT_Board::WordTTT_Board()
    : Board<char>(3, 3)
{
    // Initialize empty board
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '.';

    n_moves = 0;
    load_dictionary("dic.txt"); // Default dictionary file
}

// ---------------- Game Logic ----------------
/**
 * @brief Places a letter on the board
 * @param move Contains position (x,y) and letter
 * @return true if move valid and placed, false otherwise
 */
bool WordTTT_Board::update_board(Move<char> *move)
{
    int x = move->get_x();         // Row
    int y = move->get_y();         // Column
    char sym = move->get_symbol(); // Letter
    // Validate position
    if (x < 0 || x >= 3 || y < 0 || y >= 3)
    {
        cout << "Invalid position!\n";
        return false;
    }
    // Check if cell is empty
    if (board[x][y] != '.')
    {
        cout << "Cell already taken.\n";
        return false;
    }

    board[x][y] = sym;
    n_moves++;
    return true;
}

/**
 * @brief Checks if a 3-letter word exists in dictionary
 * @param w Word to check
 * @return true if word found in dictionary
 */
bool WordTTT_Board::is_valid_word(const string &w) const
{
    return find(dictionary.begin(), dictionary.end(), w) != dictionary.end();
}

/**
 * @brief Checks if a row forms a valid word
 * @param r Row index (0-2)
 * @return true if row contains valid word
 */

bool WordTTT_Board::check_row(int r) const
{
    string w;
    for (int j = 0; j < 3; j++)
        w += board[r][j];
    return is_valid_word(w);
}

/**
 * @brief Checks if a column forms a valid word
 * @param c Column index (0-2)
 * @return true if column contains valid word
 */

bool WordTTT_Board::check_col(int c) const
{
    string w;
    for (int i = 0; i < 3; i++)
        w += board[i][c];
    return is_valid_word(w);
}

/**
 * @brief Checks both diagonals for valid words
 * @return true if any diagonal forms a valid word
 */
bool WordTTT_Board::check_diagonals() const
{
    string d1 = {board[0][0], board[1][1], board[2][2]};
    string d2 = {board[0][2], board[1][1], board[2][0]};
    return is_valid_word(d1) || is_valid_word(d2);
}

/**
 * @brief Checks if player has won by forming a word
 * @param p Player to check
 * @return true if player has formed any valid word
 *
 * Checks all rows, columns, and diagonals for valid words.
 */

bool WordTTT_Board::is_win(Player<char> *p)
{
    for (int i = 0; i < 3; i++)
        if (check_row(i) || check_col(i))
            return true;

    return check_diagonals();
}

/**
 * @brief Checks if player has lost
 * @param p Player to check
 * @return true if opponent has won (same as is_win in this game)
 *
 * In this symmetric game, losing = opponent winning.
 */

bool WordTTT_Board::is_lose(Player<char> *p)
{
    return is_win(p);
}

/**
 * @brief Checks for draw condition
 * @param p Player (unused)
 * @return true if board full and no winner
 */

bool WordTTT_Board::is_draw(Player<char> *p)
{
    return (n_moves == 9 && !is_win(p));
}

/**
 * @brief Checks if game is over
 * @param p Current player
 * @return true if game has winner or is draw
 */

bool WordTTT_Board::game_is_over(Player<char> *p)
{
    return is_win(p) || is_draw(p);
}

// ---------------- UI ----------------

/**
 * @brief Constructor for WordTTT UI
 *
 * Sets game title and number of players.
 */
WordTTT_UI::WordTTT_UI() : UI<char>("Word Tic-Tac-Toe", 2) {}
/**
 * @brief Creates a new player
 * @param name Player name
 * @param symbol Player symbol (unused in this variant)
 * @param type Player type (HUMAN/COMPUTER)
 * @return New Player object
 */
Player<char> *WordTTT_UI::create_player(string &name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets move from player
 * @param p Current player
 * @return Move object containing position and letter
 *
 * For computer: picks random empty cell and random letter A-Z
 * For human: prompts for row, column, and letter
 */

Move<char> *WordTTT_UI::get_move(Player<char> *p)
{
    Board<char> *board = p->get_board_ptr();
    auto matrix = board->get_board_matrix();
    // COMPUTER PLAYER
    if (p->get_type() == PlayerType::COMPUTER)
    {
        vector<pair<int, int>> empty;

        // Find all empty cells
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (matrix[i][j] == '.')
                    empty.push_back({i, j});
        // Pick random empty cell
        int idx = rand() % empty.size();

        // Generate random letter A-Z
        char random_letter = 'A' + (rand() % 26);

        cout << p->get_name() << " plays at ("
             << empty[idx].first << ", " << empty[idx].second
             << ") letter: " << random_letter << endl;

        return new Move<char>(empty[idx].first, empty[idx].second, random_letter);
    }

    // HUMAN PLAYER
    int r, c;
    char letter;
    cout << p->get_name() << " enter (row col letter): ";
    cin >> r >> c >> letter;

    letter = toupper(letter); // Convert to uppercase
    return new Move<char>(r, c, letter);
}
