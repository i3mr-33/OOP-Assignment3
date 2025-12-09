#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <limits>  // for input validation
#include "InverseTicTacToe.h"

using namespace std;

//====================== InverseTicTacToe_Board Implementation ======================

InverseTicTacToe_Board::InverseTicTacToe_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool InverseTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate coordinates
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Coordinates must be within board limits (0-2).\n";
        return false;
    }

    // Check if cell is empty
    if (mark != 0 && board[x][y] != blank_symbol) {
        cout << "Cell is occupied!\n";
        return false;
    }

    if (mark == 0) { // Undo move
        if (board[x][y] != blank_symbol) {
            n_moves--;
            board[x][y] = blank_symbol;
            return true;
        }
        cout << "Cannot undo - cell is already empty!\n";
        return false;
    }
    else {         // Apply move
        if (board[x][y] == blank_symbol) {
            n_moves++;
            board[x][y] = toupper(mark);
            return true;
        }
        cout << "Cell is occupied!\n";
        return false;
    }
}

bool InverseTicTacToe_Board::is_win(Player<char>* player) {
    char opponent_sym = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> opponent("", opponent_sym, PlayerType::HUMAN);
    opponent.set_board_ptr(this);
    return is_lose(&opponent);
}

bool InverseTicTacToe_Board::is_lose(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool InverseTicTacToe_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool InverseTicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

int InverseTicTacToe_Board::check_status() {
    Player<char> X_player("X", 'X', PlayerType::COMPUTER);
    Player<char> O_player("O", 'O', PlayerType::COMPUTER);
    if (is_lose(&O_player)) return 2;          // 2: X Wins (O loses)
    if (is_lose(&X_player)) return -2;         // -2: O Wins (X loses)
    if (n_moves == rows * columns) return 0;   // 0: Draw
    return 1;       // 1: Game continues
}
int InverseTicTacToe_Board::minimax(int& x, int& y, bool is_maximizing, bool first_time) {
    int max_score = INT_MIN, min_score = INT_MAX;
    int best_i =-1, best_j =-1;
    int result = check_status();
    if (result != 1)
    {
        return result;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (board[i][j] == '.')
            {
                if (is_maximizing)
                {
                    board[i][j] = 'X';
                    int score = minimax(x, y, false, false);
                    board[i][j] = '.';
                    if (score >= max_score)
                    {
                        max_score = score;
                        best_i = i;
                        best_j = j;
                    }
                }
                else
                {
                    board[i][j] = 'O';
                    int score = minimax(x, y, true, false);
                    board[i][j] = '.';
                    if (score <= min_score)
                    {
                        min_score = score;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }
    }
    if (first_time)
    {
        x = best_i;
        y = best_j;
    }
    return (is_maximizing ? max_score : min_score);
}

//====================== InverseTicTacToe_UI Implementation ======================

InverseTicTacToe_UI::InverseTicTacToe_UI() : UI<char>("Welcome to Inverse Tic - Tac - Toe Game!", 3) {}

Player<char>* InverseTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "AI")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* InverseTicTacToe_UI::get_move(Player<char>* player) {
    int x = -1, y = -1;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        InverseTicTacToe_Board* board_ptr = dynamic_cast<InverseTicTacToe_Board*>(player->get_board_ptr());
        bool is_maximizing = (player->get_symbol() == 'X');
        if (board_ptr) {
            board_ptr->minimax(x, y, is_maximizing, true);
            cout << "\n" << player->get_name() << " (Ai) " << "chooses move : (" << x << ", " << y << ")\n";
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}

Player<char>** InverseTicTacToe_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "AI" };
    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);
    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);
    return players;
}