#include "NumericalTicTacToe_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

//--------------------------------------- NumericalTicTacToe_Board Implementation

NumericalTicTacToe_Board::NumericalTicTacToe_Board() : Board(3, 3) {
    // Initialize board with zeros (empty cells)
    for (auto& row : board)
        for (auto& cell : row)
            cell = 0;

    // Initialize available numbers
    available_odds = { 1, 3, 5, 7, 9 };
    available_evens = { 2, 4, 6, 8 };
}

bool NumericalTicTacToe_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    // Validate coordinates
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid coordinates! Please use 0-2 for both x and y.\n";
        return false;
    }

    // Check if cell is empty
    if (board[x][y] != 0) {
        cout << "Cell (" << x << ", " << y << ") is already occupied!\n";
        return false;
    }

    // Check if number is valid and available
    bool is_player1 = (number % 2 == 1); // Odd numbers for player 1
    if (!is_number_available(number, is_player1)) {
        cout << "Number " << number << " is not available for this player!\n";
        return false;
    }

    // Apply the move
    board[x][y] = number;
    n_moves++;

    // Remove the used number from available numbers
    if (is_player1) {
        available_odds.erase(remove(available_odds.begin(), available_odds.end(), number), available_odds.end());
    }
    else {
        available_evens.erase(remove(available_evens.begin(), available_evens.end(), number), available_evens.end());
    }

    return true;
}

bool NumericalTicTacToe_Board::is_win(Player<int>* player) {
    // Check all rows, columns and diagonals for sum of 15
    const int target_sum = 15;

    // Check rows
    for (int i = 0; i < rows; ++i) {
        int sum = board[i][0] + board[i][1] + board[i][2];
        if (sum == target_sum && board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < columns; ++j) {
        int sum = board[0][j] + board[1][j] + board[2][j];
        if (sum == target_sum && board[0][j] != 0 && board[1][j] != 0 && board[2][j] != 0) {
            return true;
        }
    }

    // Check diagonals
    int diag1 = board[0][0] + board[1][1] + board[2][2];
    int diag2 = board[0][2] + board[1][1] + board[2][0];

    if ((diag1 == target_sum && board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) ||
        (diag2 == target_sum && board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0)) {
        return true;
    }

    return false;
}

bool NumericalTicTacToe_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool NumericalTicTacToe_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

bool NumericalTicTacToe_Board::is_number_available(int number, bool is_player1) {
    if (is_player1) {
        return find(available_odds.begin(), available_odds.end(), number) != available_odds.end();
    }
    else {
        return find(available_evens.begin(), available_evens.end(), number) != available_evens.end();
    }
}

vector<int> NumericalTicTacToe_Board::get_available_numbers(bool is_player1) const {
    return is_player1 ? available_odds : available_evens;
}

//--------------------------------------- NumericalTicTacToe_UI Implementation

NumericalTicTacToe_UI::NumericalTicTacToe_UI()
    : UI<int>("Welcome to Numerical Tic-Tac-Toe Game!", 3) {}

Player<int>* NumericalTicTacToe_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << "\n";
    return new Player<int>(name, symbol, type);
}

Move<int>* NumericalTicTacToe_UI::get_move(Player<int>* player) {
    int x, y, number;
    bool is_player1 = (player->get_symbol() == 1); // Player 1 uses odd numbers

    if (player->get_type() == PlayerType::HUMAN) {
        // Get coordinates
        cout << "\n" << player->get_name() << ", enter your move coordinates (x y, 0-2): ";
        cin >> x >> y;

        // Validate coordinates
        if (x < 0 || x > 2 || y < 0 || y > 2) {
            cout << "Invalid coordinates! Using (0,0) as default.\n";
            x = 0; y = 0;
        }

        // Get number
        NumericalTicTacToe_Board* game_board = dynamic_cast<NumericalTicTacToe_Board*>(player->get_board_ptr());
        vector<int> available_nums = game_board->get_available_numbers(is_player1);

        while (true) {
            cout << "Available numbers for you: ";
            for (int num : available_nums) cout << num << " ";
            cout << "\nEnter your number: ";
            cin >> number;

            // Check if the number is in the available list
            if (find(available_nums.begin(), available_nums.end(), number) != available_nums.end()) {
                break; // Number is valid, exit the loop
            }
            else {
                cout << "Invalid number! Please choose a number from your list.\n";
            }
        }
    }
    else { // COMPUTER player
        NumericalTicTacToe_Board* game_board = dynamic_cast<NumericalTicTacToe_Board*>(player->get_board_ptr());
        vector<int> available_nums = game_board->get_available_numbers(is_player1);

        // Choose random empty cell
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (game_board->get_board_matrix()[x][y] != 0);

        // Choose random available number
        number = available_nums[rand() % available_nums.size()];

        cout << "\nComputer " << player->get_name() << " chooses: (" << x << ", " << y << ") with number " << number << endl;
    }

    return new Move<int>(x, y, number);
}

Player<int>** NumericalTicTacToe_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1 (Odds: 1,3,5,7,9)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1); // Symbol 1 represents player 1 (odds)

    string name2 = get_player_name("Player 2 (Evens: 2,4,6,8)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2); // Symbol 2 represents player 2 (evens)

    return players;
}