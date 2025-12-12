#include "Obstacles_TTT_classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

// ==================== Obstacles_Board Implementation ====================

Obstacles_Board::Obstacles_Board() : Board(6, 6) {
    // Initialize board with blank symbols
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}

void Obstacles_Board::add_obstacles() {
    int added = 0;
    int max_attempts = 100; // Prevent infinite loop

    while (added < 2 && max_attempts > 0) {
        int x = rand() % rows;
        int y = rand() % columns;

        if (board[x][y] == blank_symbol) {
            board[x][y] = obstacle_symbol;
            obstacle_positions.push_back({ x, y });
            added++;
        }
        max_attempts--;
    }
}

bool Obstacles_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate coordinates
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << " Invalid position! Coordinates must be within board limits (0-5).\n";
        return false;
    }

    // Check if cell is empty
    if (board[x][y] != blank_symbol) {
        cout << " Cell is occupied!\n";
        return false;
    }

    // Apply move
    board[x][y] = toupper(mark);
    n_moves++;

    // Add obstacles after each full round (2 moves)
    int total_cells = rows * columns;
    int occupied_cells = n_moves + obstacle_positions.size();

    if (n_moves % 2 == 0 && occupied_cells < total_cells) {
        add_obstacles();
    }

    return true;
}

bool Obstacles_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    int rows = 6, cols = 6;

    // Check horizontal wins
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= cols - 4; ++j) {
            if (board[i][j] == sym &&
                board[i][j + 1] == sym &&
                board[i][j + 2] == sym &&
                board[i][j + 3] == sym) {
                return true;
            }
        }
    }

    // Check vertical wins
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == sym &&
                board[i + 1][j] == sym &&
                board[i + 2][j] == sym &&
                board[i + 3][j] == sym) {
                return true;
            }
        }
    }

    // Check diagonal (down-right)
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j <= cols - 4; ++j) {
            if (board[i][j] == sym &&
                board[i + 1][j + 1] == sym &&
                board[i + 2][j + 2] == sym &&
                board[i + 3][j + 3] == sym) {
                return true;
            }
        }
    }

    // Check diagonal (down-left)
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 3; j < cols; ++j) {
            if (board[i][j] == sym &&
                board[i + 1][j - 1] == sym &&
                board[i + 2][j - 2] == sym &&
                board[i + 3][j - 3] == sym) {
                return true;
            }
        }
    }

    return false;
}

bool Obstacles_Board::is_draw(Player<char>* player) {
    int total_cells = rows * columns;
    int occupied_cells = n_moves + obstacle_positions.size();

    if (occupied_cells >= total_cells) {
        return !is_win(player);
    }
    return false;
}

bool Obstacles_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ==================== Obstacles_UI Implementation ====================

Obstacles_UI::Obstacles_UI()
    : UI("Welcome to Obstacles Tic-Tac-Toe (6x6)\n"
        "   Get 4 in a row while avoiding obstacles", 3),
    obs_board(nullptr) {
}

Player<char>* Obstacles_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Obstacles_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n " << player->get_name() << " (" << player->get_symbol()
            << "), enter your move (row col, 0-5): ";

        while (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter two numbers (0-5): ";
        }
    }
    else {
        // Computer player - make random valid move
        const auto& matrix = player->get_board_ptr()->get_board_matrix();
        int attempts = 0;

        do {
            x = rand() % 6;
            y = rand() % 6;
            attempts++;

            // Fallback: find first empty cell if random takes too long
            if (attempts > 50) {
                for (int i = 0; i < 6; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        if (matrix[i][j] == '.') {
                            x = i;
                            y = j;
                            break;
                        }
                    }
                }
                break;
            }
        } while (matrix[x][y] != '.');

        cout << "\n Computer chooses: " << x << " " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}

void Obstacles_UI::display_board_with_obstacles() const {
    if (!obs_board) return;

    const auto& matrix = obs_board->get_board_matrix();
    int rows = matrix.size();
    int cols = matrix[0].size();

    cout << "\n     ";
    for (int j = 0; j < cols; ++j) {
        cout << setw(cell_width + 1) << j;
    }
    cout << "\n    " << string((cell_width + 2) * cols, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < cols; ++j) {
            cout << setw(cell_width) << matrix[i][j] << " |";
        }
        cout << "\n    " << string((cell_width + 2) * cols, '-') << "\n";
    }

    cout << "\nLegend: X = Player 1, O = Player 2, # = Obstacle, . = Empty\n\n";
}

void Obstacles_UI::set_board(Obstacles_Board* board) {
    obs_board = board;
}