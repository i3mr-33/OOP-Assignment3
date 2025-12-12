#include "SUSTicTacToe_Classes.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// ==================== SUS_Board Implementation ====================

/**
 * @brief Constructor initializes a 3x3 SUS board.
 * @details Sets all cells empty, initializes the SUS sequence string,
 * and sets scores and total sequence counter to 0.
 */
SUS_Board::SUS_Board() : Board(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' '; // empty cell

    sus = "SUS";
    score_S = 0;
    score_U = 0;
    total_sus_count = 0;
}

/**
 * @brief Counts all "SUS" sequences on the board.
 * @return Total number of SUS sequences found in rows, columns, and diagonals.
 */
int SUS_Board::count_SUS_sequences()
{
    int count = 0;

    // Check rows
    for (int i = 0; i < 3; i++)
    {
        string r = "";
        for (int j = 0; j < 3; j++) r += board[i][j];
        if (r == sus) count++;
    }

    // Check columns
    for (int j = 0; j < 3; j++)
    {
        string c = "";
        for (int i = 0; i < 3; i++) c += board[i][j];
        if (c == sus) count++;
    }

    // Check main diagonal
    string d1 = "";
    d1 += board[0][0]; d1 += board[1][1]; d1 += board[2][2];
    if (d1 == sus) count++;

    // Check anti-diagonal
    string d2 = "";
    d2 += board[0][2]; d2 += board[1][1]; d2 += board[2][0];
    if (d2 == sus) count++;

    return count;
}

/**
 * @brief Apply a move to the board.
 * @details Updates the cell if valid, increases move counter,
 * and updates scores if a new SUS sequence is formed.
 * @param move Pointer to Move object.
 * @return true if move is valid and applied.
 */
bool SUS_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3)
    {
        cout << "Invalid position! Coordinates must be 0-2.\n";
        return false;
    }

    if (board[x][y] != ' ')
    {
        cout << "Cell is occupied!\n";
        return false;
    }

    board[x][y] = symbol;
    n_moves++;

    int new_total_sus_count = count_SUS_sequences();
    int points_gained = new_total_sus_count - total_sus_count;

    if (points_gained > 0)
    {
        if (symbol == 'S') score_S += points_gained;
        else score_U += points_gained;
    }

    total_sus_count = new_total_sus_count;
    return true;
}

/**
 * @brief Check if a player has won.
 * @param player Pointer to the player.
 * @return true if player has more points than opponent after 9 moves.
 */
bool SUS_Board::is_win(Player<char>* player)
{
    if (n_moves == 9)
    {
        char symbol = player->get_symbol();
        if (symbol == 'S') return score_S > score_U;
        if (symbol == 'U') return score_U > score_S;
    }
    return false;
}

/**
 * @brief Check if a player has lost.
 * @param player Pointer to the player.
 * @return true if opponent has more points after 9 moves.
 */
bool SUS_Board::is_lose(Player<char>* player)
{
    if (n_moves == 9)
    {
        char symbol = player->get_symbol();
        if (symbol == 'S') return score_U > score_S;
        if (symbol == 'U') return score_S > score_U;
    }
    return false;
}

/**
 * @brief Check if the game ended in a draw.
 * @param player Pointer to the player.
 * @return true if both scores are equal after 9 moves.
 */
bool SUS_Board::is_draw(Player<char>* player)
{
    if (n_moves == 9)
        return score_S == score_U;
    return false;
}

/**
 * @brief Check if the game is over.
 * @param player Pointer to the player.
 * @return true if all moves are played (board full).
 */
bool SUS_Board::game_is_over(Player<char>* player)
{
    return n_moves == 9;
}

/**
 * @brief Returns current game status as integer.
 * @return 1 = ongoing, 2 = 'S' wins, -2 = 'U' wins, 0 = draw.
 */
int SUS_Board::check_status()
{
    if (n_moves < 9) return 1;
    if (score_S > score_U) return 2;
    if (score_S < score_U) return -2;
    return 0;
}

/**
 * @brief Minimax algorithm for AI to choose best move.
 * @param x Output row index for best move.
 * @param y Output column index for best move.
 * @param isMaximizing True if AI is maximizing its score.
 * @param firstStep True if this is the top recursion step (record move coordinates).
 * @return Score value of the board after simulation.
 */
int SUS_Board::minimax(int& x, int& y, bool isMaximizing, bool firstStep)
{
    int max_score = INT_MIN;
    int min_score = INT_MAX;
    int Final_x, Final_y;

    int result = check_status();
    if (result != 1) // game over
        return score_S - score_U;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                // backup current state
                char backup_cell = board[i][j];
                int backup_moves = n_moves;
                int backup_scoreS = score_S;
                int backup_scoreU = score_U;
                int backup_total = total_sus_count;

                // apply move
                char symbol = (isMaximizing ? 'S' : 'U');
                board[i][j] = symbol;
                n_moves++;

                int prev_total = total_sus_count;
                int new_total = count_SUS_sequences();
                int gained = new_total - prev_total;
                if (gained > 0)
                    (symbol == 'S' ? score_S : score_U) += gained;
                total_sus_count = new_total;

                // recursive call
                int score = minimax(x, y, !isMaximizing, false);

                // undo move
                board[i][j] = backup_cell;
                n_moves = backup_moves;
                score_S = backup_scoreS;
                score_U = backup_scoreU;
                total_sus_count = backup_total;

                // choose best score
                if (isMaximizing)
                {
                    if (score >= max_score)
                    {
                        max_score = score;
                        Final_x = i;
                        Final_y = j;
                    }
                }
                else
                {
                    if (score <= min_score)
                    {
                        min_score = score;
                        Final_x = i;
                        Final_y = j;
                    }
                }
            }
        }
    }

    if (firstStep)
    {
        x = Final_x;
        y = Final_y;
    }

    return isMaximizing ? max_score : min_score;
}

// ==================== SUS_UI Implementation ====================

SUS_UI::SUS_UI() : UI<char>("Welcome to SUS Game!", 3) {}

/**
 * @brief Creates a player (human or AI).
 */
Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the next move from player (or AI).
 * @param player Pointer to player.
 * @return Pointer to the chosen Move.
 */
Move<char>* SUS_UI::get_move(Player<char>* player)
{
    char player_symbol = player->get_symbol();
    int x, y;

    // AI MOVE
    if (player->get_type() == PlayerType::COMPUTER)
    {
        SUS_Board* board = dynamic_cast<SUS_Board*>(player->get_board_ptr());

        cout << "\n" << player->get_name() << " (AI) is thinking..." << endl;

        AI_Player* ai_player = new AI_Player(player_symbol, board);
        ai_player->get_best_move(x, y);
        cout << "\n" << player->get_name() << " (AI) chooses (" << x << "," << y << ")\n";

        delete ai_player;
        return new Move<char>(x, y, player_symbol);
    }

    // HUMAN MOVE
    else
    {
        while (true)
        {
            cout << "\n" << player->get_name() << " enter coordinates (x y): ";
            if (cin >> x >> y) break;
            cout << "Invalid input! Please enter numbers 0-2.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        return new Move<char>(x, y, player_symbol);
    }
}

/**
 * @brief Sets up the two players for the game.
 */
Player<char>** SUS_UI::setup_players()
{
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Ai" };

    // Player 1
    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);

    cout << "\n" << name1 << ", choose your symbol:\n1) S\n2) U\n";
    int symbol_choice;
    while (true)
    {
        cout << "Enter choice (1 or 2): ";
        if (cin >> symbol_choice && (symbol_choice == 1 || symbol_choice == 2))
        {
            cin.ignore(10000, '\n');
            break;
        }
        cout << "Invalid input! Enter 1 or 2.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    char symbol1 = (symbol_choice == 1 ? 'S' : 'U');
    char symbol2 = (symbol1 == 'S' ? 'U' : 'S');

    players[0] = create_player(name1, symbol1, type1);

    // Player 2
    string name2 = get_player_name("Player 2 (uses " + string(1, symbol2) + ")");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, symbol2, type2);

    return players;
}

// ==================== AI_Player Implementation ====================

AI_Player::AI_Player(char symbol, SUS_Board* b) : Player<char>("AI_Player", symbol, PlayerType::COMPUTER)
{
    board = b;
}

/**
 * @brief Get the best move for AI using minimax.
 */
void AI_Player::get_best_move(int& x, int& y)
{
    board->minimax(x, y, true, true);
}
