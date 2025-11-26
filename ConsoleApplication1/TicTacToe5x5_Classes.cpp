#include "TicTacToe5x5_Classes.h"
#include <cstdlib>
#include <ctime>

//====================== TicTacToe5x5_Board Implementation ======================

TicTacToe5x5_Board::TicTacToe5x5_Board() : Board<char>(5, 5) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = blank_symbol;
    n_moves = 0;
}

bool TicTacToe5x5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;

    if (board[x][y] == blank_symbol && mark != 0) {
        board[x][y] = toupper(mark);
        ++n_moves;
        return true;
    }

    if (mark == 0 && board[x][y] != blank_symbol) {
        board[x][y] = blank_symbol;
        --n_moves;
        return true;
    }

    return false;
}

bool TicTacToe5x5_Board::is_win(Player<char>* player) {
    (void)player;
    return false;
}

bool TicTacToe5x5_Board::is_lose(Player<char>* player) {
    (void)player;
    return false;
}

bool TicTacToe5x5_Board::is_draw(Player<char>* player) {
    (void)player;
    return (n_moves >= rows * columns);
}

bool TicTacToe5x5_Board::game_is_over(Player<char>* player) {
    return is_draw(player);
}

void TicTacToe5x5_Board::print_scores_and_winner() {
    int x_score = count_three_in_row('X');
    int o_score = count_three_in_row('O');

    cout << "\n=== Final Scores ===\n";
    cout << "Player X: " << x_score << "\n";
    cout << "Player O: " << o_score << "\n";

    if (x_score > o_score)
        cout << "=> Player X wins!\n";
    else if (o_score > x_score)
        cout << "=> Player O wins!\n";
    else
        cout << "=> It's a tie!\n";
}

int TicTacToe5x5_Board::count_three_in_row(char sym) {
    int score = 0;

    // horizontal
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j <= columns - 3; ++j)
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym)
                ++score;

    // vertical
    for (int j = 0; j < columns; ++j)
        for (int i = 0; i <= rows - 3; ++i)
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym)
                ++score;

    // diagonal down-right
    for (int i = 0; i <= rows - 3; ++i)
        for (int j = 0; j <= columns - 3; ++j)
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym)
                ++score;

    // diagonal up-right
    for (int i = 2; i < rows; ++i)
        for (int j = 0; j <= columns - 3; ++j)
            if (board[i][j] == sym && board[i - 1][j + 1] == sym && board[i - 2][j + 2] == sym)
                ++score;

    return score;
}

//====================== TicTacToe5x5_UI Implementation ======================

TicTacToe5x5_UI::TicTacToe5x5_UI()
    : UI<char>("Welcome to 5x5 Tic-Tac-Toe (Course CS213)", 3) {}

TicTacToe5x5_UI::~TicTacToe5x5_UI() {}

Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe5x5_UI::get_move(Player<char>* player) {
    int x = -1, y = -1;
    Board<char>* b = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column (0-4): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else {
        int rows = b->get_rows();
        int cols = b->get_columns();
        int tries = 0;

        while (true) {
            x = rand() % rows;
            y = rand() % cols;
            vector<vector<char>> mat = b->get_board_matrix();

            if (mat[x][y] == '.') {
                return new Move<char>(x, y, player->get_symbol());
            }

            if (++tries > 1000) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (mat[i][j] == '.') {
                            return new Move<char>(i, j, player->get_symbol());
                        }
                    }
                }
            }
        }
    }
}
