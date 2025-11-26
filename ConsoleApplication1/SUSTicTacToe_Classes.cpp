#include "SUSTicTacToe_Classes.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// SUS_Board Implementation

SUS_Board::SUS_Board() : Board(3, 3)
{
    // Initialize empty board
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' ';

    sus = "SUS";
}

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
    return true;
}

int SUS_Board::count_SUS_sequences()
{
    int count = 0;

    // Rows
    for (int i = 0; i < 3; i++)
    {
        string r = "";
        for (int j = 0; j < 3; j++) r += board[i][j];
        if (r == sus) count++;
    }

    // Columns
    for (int j = 0; j < 3; j++)
    {
        string c = "";
        for (int i = 0; i < 3; i++) c += board[i][j];
        if (c == sus) count++;
    }

    // Diagonal 1 
    string d1 = "";
    d1 += board[0][0]; d1 += board[1][1]; d1 += board[2][2];
    if (d1 == sus) count++;

    //  Diagonal 2 
    string d2 = "";
    d2 += board[0][2]; d2 += board[1][1]; d2 += board[2][0];
    if (d2 == sus) count++;

    return count;
}

bool SUS_Board::is_win(Player<char>* player)
{
    if (n_moves == 9 && count_SUS_sequences() > 0) {
        return player->get_symbol() == 'S';
    }
    return false;
}

bool SUS_Board::is_lose(Player<char>* player)
{
    if (n_moves == 9 && count_SUS_sequences() > 0) {
        return player->get_symbol() == 'U';
    }
    return false;
}

bool SUS_Board::is_draw(Player<char>* player)
{
    return n_moves == 9 && count_SUS_sequences() == 0;
}

bool SUS_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_lose(player) || is_draw(player);
}

bool SUS_Board::is_position_available(int number, bool is_player1)
{
    if (number < 1 || number > 9) return false;

    int x = (number - 1) / 3;
    int y = (number - 1) % 3;

    return board[x][y] == ' ';
}

vector<int> SUS_Board::get_available_position(bool is_player1)
{
    vector<int> available;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                available.push_back(i * 3 + j + 1);
            }
        }
    }
    return available;
}

// SUS_UI Implementation

SUS_UI::SUS_UI() : UI<char>("Welcome to SUS Game!", 3) {}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}

Move<char>* SUS_UI::get_move(Player<char>* player)
{
    char player_symbol = player->get_symbol();

    // COMPUTER MOVE 
    if (player->get_type() == PlayerType::COMPUTER)
    {
        char computer_symbol = player_symbol;
        bool is_p1 = (computer_symbol == 'S');

        SUS_Board* game_board = dynamic_cast<SUS_Board*>(player->get_board_ptr());
        vector<int> available = game_board->get_available_position(is_p1);

        if (available.empty())
        {
            return new Move<char>(0, 0, computer_symbol);
        }

        int idx = rand() % available.size();
        int pos = available[idx];
        int x = (pos - 1) / 3;
        int y = (pos - 1) % 3;
        char letter = computer_symbol;

        cout << "\nComputer chose position " << pos
            << " -> (" << x << "," << y << ") with letter " << letter << endl;
        return new Move<char>(x, y, letter);
    }

    //HUMAN MOVE 
    int x, y;
    while (true)
    {
        cout << "\n" << player->get_name()
            << " (Your symbol is " << player_symbol << ") enter coordinates (x y): ";

        if (cin >> x >> y)
        {
            break;
        }
        else
        {
            cout << "Invalid input! Please enter two numbers separated by a space.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return new Move<char>(x, y, player_symbol);
}

Player<char>** SUS_UI::setup_players()
{
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // 1. Player 1
   
    // Name
    string name1 = get_player_name("Player 1");

    // Type
    PlayerType type1 = get_player_type_choice("Player 1", type_options);

    // Symbol 
    cout << "\n" << name1 << ", choose your symbol:\n"
        << "1) S\n"
        << "2) U\n";

    int symbol_choice;
    while (true)
    {
        cout << "Enter choice (1 or 2): ";
        if (cin >> symbol_choice && (symbol_choice == 1 || symbol_choice == 2))
        {
            cin.ignore(10000, '\n');
            break;
        }
        cout << "Invalid input! Please enter 1 or 2.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    char symbol1 = (symbol_choice == 1 ? 'S' : 'U');
    char symbol2 = (symbol1 == 'S' ? 'U' : 'S');

    players[0] = create_player(name1, symbol1, type1);

    // 2. Player 2

    // Name 
    string name2; 
    name2 = get_player_name("Player 2 (uses " + string(1, symbol2) + ")");

    // Type
    PlayerType type2 = get_player_type_choice("Player 2", type_options);

    players[1] = create_player(name2, symbol2, type2);

    return players;
}