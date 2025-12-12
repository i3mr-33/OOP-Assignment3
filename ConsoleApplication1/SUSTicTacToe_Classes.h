#pragma once
#include "BoardGame_Classes.h"
#include <string>

using namespace std;

/**
 * @class SUS_Board
 * @brief Logic for the "SUS" game board.
 * @details This class manages the board for the SUS game.
 * It keeps track of the SUS sequences, scores for S and U,
 * and determines the game status (win/lose/draw).
 */
class SUS_Board : public Board<char> {
private:
    string sus;            ///< Stores the current SUS sequence.
    int score_S;           ///< Score counter for 'S'.
    int score_U;           ///< Score counter for 'U'.
    int total_sus_count;   ///< Total number of SUS sequences found on the board.

public:
    /**
     * @brief Constructor initializes the SUS board and counters.
     */
    SUS_Board();

    /**
     * @brief Count all valid "SUS" sequences on the board.
     * @return Total number of SUS sequences.
     */
    int count_SUS_sequences();

    /**
     * @brief Minimax algorithm to find the best move for AI.
     * @param x Row index of the best move (output).
     * @param y Column index of the best move (output).
     * @param isMaximizing True if AI is trying to maximize score, false if minimizing.
     * @param firstStep True if this is the first step in recursion (to record move coordinates).
     * @return The score value of the board state.
     */
    int minimax(int& x, int& y, bool isMaximizing, bool firstStep);

    /**
     * @brief Checks the current game status.
     * @return Integer code representing the game state:
     *         win, lose, draw, or ongoing.
     */
    int check_status();

    /**
     * @brief Apply a move to the board.
     * @param move Pointer to the Move object.
     * @return True if the move is valid and successfully applied.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Check if a player has won the game.
     * @param player Pointer to the player.
     * @return True if the player has won.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Check if a player has lost the game.
     * @param player Pointer to the player.
     * @return True if the player has lost.
     */
    bool is_lose(Player<char>* player);

    /**
     * @brief Check if the game ended in a draw.
     * @param player Pointer to the player.
     * @return True if no moves left and no winner.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Check if the game is over (win, lose, or draw).
     * @param player Pointer to the player.
     * @return True if the game has ended.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class SUS_UI
 * @brief Handles all input/output for the SUS game.
 * @details Responsible for creating players, getting moves,
 * and showing board state to the user.
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructor for SUS UI.
     */
    SUS_UI();

    /**
     * @brief Create a player (human or AI) for the game.
     * @param name Name of the player.
     * @param symbol Symbol representing the player.
     * @param type Type of player (Human or Computer).
     * @return Pointer to the new Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Get a move from the player.
     * @param player Pointer to the player.
     * @return Pointer to the Move object chosen by the player.
     */
    Move<char>* get_move(Player<char>* player);

    /**
     * @brief Setup the two players for the game.
     * @return Array containing pointers to Player objects.
     */
    Player<char>** setup_players();
};

/**
 * @class AI_Player
 * @brief Represents an AI player that can choose the best move using minimax.
 */
class AI_Player : public Player<char> {
private:
    SUS_Board* board; ///< Reference to the game board for evaluation.

public:
    /**
     * @brief Constructor to initialize the AI player with a symbol and board reference.
     * @param symbol Symbol representing AI player.
     * @param b Pointer to the SUS board object.
     */
    AI_Player(char symbol, SUS_Board* b);

    /**
     * @brief Determine the best move for the AI.
     * @param y Reference to row index for the best move (output).
     * @param x Reference to column index for the best move (output).
     */
    void get_best_move(int& y, int& x);
};
