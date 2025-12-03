#include "DiamondTicTacToe.h"
#include <cstdlib>
#include <ctime>
#include <set>

//====================== DiamondTicTacToe_Board Implementation ======================

DiamondTicTacToe_Board::DiamondTicTacToe_Board() : Board<char>(7, 7) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = blank_symbol;
    board[0][0] = board[0][1] = board[0][2] = board[0][4] = board[0][5] = board[0][6] = '#';
    board[1][0] = board[1][1] = board[1][5] = board[1][6] = '#';
    board[2][0] = board[2][6] = '#';
    board[4][0] = board[4][6] = '#';
    board[5][0] = board[5][1] = board[5][5] = board[5][6] = '#';
    board[6][0] = board[6][1] = board[6][2] = board[6][4] = board[6][5] = board[6][6] = '#';
    n_moves = 0;
    last_move_x = -1; 
    last_move_y = -1;
}

bool DiamondTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!is_valid_cell(x, y)) return false;

    // Check if cell is empty
    if (board[x][y] != blank_symbol) {
        cout << "Cell is occupied!\n";
        return false;
    }
    if (board[x][y] == blank_symbol && mark != 0) {
        board[x][y] = toupper(mark);
        ++n_moves;
        last_move_x = x; 
        last_move_y = y;           
        last_move_symbol = toupper(mark);
        return true;
    }

    if (mark == 0 && board[x][y] != blank_symbol) {
        board[x][y] = blank_symbol;
        --n_moves;
        return true;
    }

    return false;
}

bool DiamondTicTacToe_Board::is_valid_cell(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
    return board[x][y] != '#';
}

bool DiamondTicTacToe_Board::check_line(int x, int y, char sym, int dx, int dy, int required_length) {
    int count1 = 0;
    for (int i = 1; i < required_length; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (is_valid_cell(nx, ny) && board[nx][ny] == sym) {
            count1++;
        }
        else {
            break;
        }
    }

    int count2 = 0;
    for (int i = 1; i < required_length; i++) {
        int nx = x - i * dx;
        int ny = y - i * dy;
        if (is_valid_cell(nx, ny) && board[nx][ny] == sym) {
            count2++;
        }
        else {
            break;
        }
    }
    return (count1 + count2 + 1) >= required_length;
}

bool DiamondTicTacToe_Board::check_double_win_for_last_move() {
    if (last_move_x == -1 || last_move_y == -1) return false;

    char sym = last_move_symbol;
    vector<pair<int, int>> directions = {
        {0, 1}, 
        {1, 0},   
        {1, 1},   
        {1, -1}    
    };

    bool has_three = false;
    bool has_four = false;
    set<int> three_directions;
    set<int> four_directions;

    for (int d = 0; d < directions.size(); d++) {
        int dx = directions[d].first;
        int dy = directions[d].second;
        if (check_line(last_move_x, last_move_y, sym, dx, dy, 4)) {
            has_four = true;
            four_directions.insert(d);
        }
        if (check_line(last_move_x, last_move_y, sym, dx, dy, 3)) {
            has_three = true;
            three_directions.insert(d);
        }
    }
    if (has_three && has_four) {

        for (int d3 : three_directions) {
            for (int d4 : four_directions) {
                if (d3 != d4) {
                    return true;
                }
            }
        }
        return false;
    }

    return false;
}

bool DiamondTicTacToe_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (is_valid_cell(i, j) && board[i][j] == sym) {
                int original_x = last_move_x;
                int original_y = last_move_y;
                char original_sym = last_move_symbol;

                last_move_x = i;
                last_move_y = j;
                last_move_symbol = sym;
                if (check_double_win_for_last_move()) {
                    last_move_x = original_x;
                    last_move_y = original_y;
                    last_move_symbol = original_sym;
                    return true;
                }
                last_move_x = original_x;
                last_move_y = original_y;
                last_move_symbol = original_sym;
            }
        }
    }
    return false;
}

bool DiamondTicTacToe_Board::is_lose(Player<char>* player) {
    char opponent_sym = (player->get_symbol() == 'X') ? 'O' : 'X';
    int temp_x = last_move_x;
    int temp_y = last_move_y;
    char temp_sym = last_move_symbol;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (is_valid_cell(i, j) && board[i][j] == opponent_sym) {
                last_move_x = i;
                last_move_y = j;
                last_move_symbol = opponent_sym;
                if (check_double_win_for_last_move()) {
                    last_move_x = temp_x;
                    last_move_y = temp_y;
                    last_move_symbol = temp_sym;
                    return true;
                }
            }
        }
    }
    last_move_x = temp_x;
    last_move_y = temp_y;
    last_move_symbol = temp_sym;
    return false;
}

bool DiamondTicTacToe_Board::is_draw(Player<char>* player) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (is_valid_cell(i, j) && board[i][j] == blank_symbol) {
                return false;
            }
        }
    }
    return true;
}

bool DiamondTicTacToe_Board::game_is_over(Player<char>* player) {
    if (is_win(player)) {
        return true;
    }
    char opponent_sym = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> opponent("", opponent_sym, PlayerType::HUMAN);
    opponent.set_board_ptr(this);
    if (is_win(&opponent)) {
        return true;
    }
    return is_draw(player);
}

//====================== DiamondTicTacToe_UI Implementation ======================

DiamondTicTacToe_UI::DiamondTicTacToe_UI()
    : UI<char>("Welcome to Diamond Tic-Tac-Toe", 2) {}

DiamondTicTacToe_UI::~DiamondTicTacToe_UI() {}

Player<char>* DiamondTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* DiamondTicTacToe_UI::get_move(Player<char>* player) {
    int x = -1, y = -1;
    Board<char>* b = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol()
            << "), enter your move ( row and column , 0-6 ): ";
        cin >> x >> y;
        while (cin.fail() || x < 0 || x > 6 || y < 0 || y > 6) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter numbers between 0 and 6: ";
            cin >> x >> y;
        }
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
void DiamondTicTacToe_UI::display_board_matrix(const vector<vector<char>>& matrix) const {

    cout << "\n  0   1   2   3   4   5   6\n";

    cout << "               -+-               \n";
    cout << "0             | " << matrix[0][3] << " | \n";
    cout << "           ---+---+---           \n";
    cout << "1         | " << matrix[1][2] << " | " << matrix[1][3] << " | " << matrix[1][4] << " |  \n";
    cout << "       ---+---+---+---+---      \n";
    cout << "2     | " << matrix[2][1] << " | " << matrix[2][2] << " | " << matrix[2][3] << " | " << matrix[2][4] << " | " << matrix[2][5] << " |    \n";
    cout << "  +---+---+---+---+---+---+---+\n";
    cout << "3 | " << matrix[3][0] << " | " << matrix[3][1] << " | " << matrix[3][2] << " | " << matrix[3][3] << " | " << matrix[3][4] << " | " << matrix[3][5] << " | " << matrix[3][6] << " |\n";
    cout << "  +---+---+---+---+---+---+---+ \n";
    cout << "4     | " << matrix[4][1] << " | " << matrix[4][2] << " | " << matrix[4][3] << " | " << matrix[4][4] << " | " << matrix[4][5] << " |    \n";
    cout << "       ---+---+---+---+---      \n";
    cout << "5         | " << matrix[5][2] << " | " << matrix[5][3] << " | " << matrix[5][4] << " |       \n";
    cout << "           ---+---+---           \n";
    cout << "6             | " << matrix[6][3] << " |    \n";
    cout << "               -+-               \n";
    cout << endl;
}