#include "TicTacToe5x5_Classes.h"
#include <cstdlib>
#include <ctime>

// ---------------- TicTacToe5x5_Board  Implementation ----------------

TicTacToe5x5_Board::TicTacToe5x5_Board()
    : Board<char>(5, 5)
{
    // initialize board with blank symbol
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = blank_symbol;

    n_moves = 0;
}


bool TicTacToe5x5_Board::update_board(Move<char>* move) {
    if (!move) return false;
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position. Try again.\n";
        return false;
    }
    if (board[x][y] != blank_symbol) {
        cout << "Cell already occupied. Try again.\n";
        return false;
    }

    board[x][y] = s;
    ++n_moves;
    return true;
}


int TicTacToe5x5_Board::count_three_in_row(char sym) const {
    int count = 0;
    // rows
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            bool ok = true;
            for (int k = 0; k < 3; ++k)
                if (board[i][j + k] != sym) { ok = false; break; }
            if (ok) ++count;
        }
    }
    // columns
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i <= rows - 3; ++i) {
            bool ok = true;
            for (int k = 0; k < 3; ++k)
                if (board[i + k][j] != sym) { ok = false; break; }
            if (ok) ++count;
        }
    }
    // main diagonals (down-right)
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            bool ok = true;
            for (int k = 0; k < 3; ++k)
                if (board[i + k][j + k] != sym) { ok = false; break; }
            if (ok) ++count;
        }
    }
    // anti-diagonals (down-left)
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 2; j < columns; ++j) {
            bool ok = true;
            for (int k = 0; k < 3; ++k)
                if (board[i + k][j - k] != sym) { ok = false; break; }
            if (ok) ++count;
        }
    }
    return count;
}


bool TicTacToe5x5_Board::is_win(Player<char>* player) {
    if (!player) return false;
    if (n_moves < 24) return false; // game plays until 24 moves
    char sym = player->get_symbol();
    // opponent symbol:
    char other = (sym == 'X') ? 'O' : 'X';
    int a = count_three_in_row(sym);
    int b = count_three_in_row(other);
    return a > b;
}

bool TicTacToe5x5_Board::is_lose(Player<char>* player) {
    if (!player) return false;
    if (n_moves < 24) return false;
    char sym = player->get_symbol();
    char other = (sym == 'X') ? 'O' : 'X';
    int a = count_three_in_row(sym);
    int b = count_three_in_row(other);
    return a < b;
}

bool TicTacToe5x5_Board::is_draw(Player<char>* player) {
    (void)player;
    if (n_moves < 24) return false;
    int a = count_three_in_row('X');
    int b = count_three_in_row('O');
    return a == b;
}

bool TicTacToe5x5_Board::game_is_over(Player<char>* player) {
    (void)player;
    return n_moves >= 24;
}

// ---------------- TicTacToe5x5_UI  Implementation ----------------

TicTacToe5x5_UI::TicTacToe5x5_UI()
    : UI<char>("FCAI 5x5 Tic-Tac-Toe", 2) 
{
    // seed random for computer moves
    srand(static_cast<unsigned int>(time(nullptr)));
}

Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    // Use base Player class as in XO example
    Player<char>* p = new Player<char>(name, symbol, type);
    return p;
}


Move<char>* TicTacToe5x5_UI::get_move(Player<char>* player) {
    if (!player) return nullptr;

    if (player->get_type() == PlayerType::COMPUTER) {
        // generate random available cell
        Board<char>* b = player->get_board_ptr();
        if (!b) return nullptr;

        vector<pair<int, int>> empties;
        auto mat = b->get_board_matrix();
        for (int i = 0; i < (int)mat.size(); ++i)
            for (int j = 0; j < (int)mat[0].size(); ++j)
                if (mat[i][j] == '.') empties.emplace_back(i, j);

        if (empties.empty()) return new Move<char>(0, 0, player->get_symbol()); 

        int idx = std::rand() % empties.size();
        return new Move<char>(empties[idx].first, empties[idx].second, player->get_symbol());
    }
    else {
        int r, c;
        cout << player->get_name() << " (" << player->get_symbol() << ") enter row col: ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }
}
